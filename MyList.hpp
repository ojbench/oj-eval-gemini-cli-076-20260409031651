#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <stdexcept>

template<typename ValueType>
class MyList
{
private:
    struct Node {
        ValueType data;
        Node* prev;
        Node* next;
        Node(const ValueType& val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
        Node(ValueType&& val, Node* p = nullptr, Node* n = nullptr) : data(std::move(val)), prev(p), next(n) {}
    };

    struct MemoryPool {
        struct Chunk {
            static const int CHUNK_SIZE = 8192;
            typename std::aligned_storage<sizeof(Node), alignof(Node)>::type data[CHUNK_SIZE];
            Chunk* next;
            int used;
            Chunk() : next(nullptr), used(0) {}
        };
        Chunk* chunkHead;
        Node* freeList;
        
        MemoryPool() : chunkHead(new Chunk()), freeList(nullptr) {}
        ~MemoryPool() {
            while (chunkHead) {
                Chunk* temp = chunkHead;
                chunkHead = chunkHead->next;
                delete temp;
            }
        }
        
        Node* allocate(const ValueType& val, Node* p, Node* n) {
            Node* res;
            if (freeList) {
                res = freeList;
                freeList = freeList->next;
            } else {
                if (chunkHead->used == Chunk::CHUNK_SIZE) {
                    Chunk* newChunk = new Chunk();
                    newChunk->next = chunkHead;
                    chunkHead = newChunk;
                }
                res = reinterpret_cast<Node*>(&chunkHead->data[chunkHead->used++]);
            }
            new (res) Node(val, p, n);
            return res;
        }
        
        void deallocate(Node* p) {
            p->~Node();
            p->next = freeList;
            freeList = p;
        }
    };

    static MemoryPool pool;

    Node* head;
    Node* tail;
    int sz;
    
    mutable Node* cacheNode;
    mutable int cacheIndex;

public:
    MyList() : head(nullptr), tail(nullptr), sz(0), cacheNode(nullptr), cacheIndex(-1) {}

    MyList(MyList &&obj) noexcept : head(obj.head), tail(obj.tail), sz(obj.sz), cacheNode(obj.cacheNode), cacheIndex(obj.cacheIndex) {
        obj.head = nullptr;
        obj.tail = nullptr;
        obj.sz = 0;
        obj.cacheNode = nullptr;
        obj.cacheIndex = -1;
    }

    MyList(const MyList &obj) : head(nullptr), tail(nullptr), sz(0), cacheNode(nullptr), cacheIndex(-1) {
        if (obj.empty()) return;
        Node* curr = obj.head;
        Node* myTail = nullptr;
        while (curr) {
            Node* newNode = pool.allocate(curr->data, myTail, nullptr);
            if (myTail) {
                myTail->next = newNode;
            } else {
                head = newNode;
            }
            myTail = newNode;
            curr = curr->next;
        }
        tail = myTail;
        sz = obj.sz;
    }

    ~MyList() {
        clear();
    }

    MyList& operator=(const MyList& obj) {
        if (this != &obj) {
            clear();
            if (obj.empty()) return *this;
            Node* curr = obj.head;
            Node* myTail = nullptr;
            while (curr) {
                Node* newNode = pool.allocate(curr->data, myTail, nullptr);
                if (myTail) {
                    myTail->next = newNode;
                } else {
                    head = newNode;
                }
                myTail = newNode;
                curr = curr->next;
            }
            tail = myTail;
            sz = obj.sz;
        }
        return *this;
    }

    MyList& operator=(MyList&& obj) noexcept {
        if (this != &obj) {
            clear();
            head = obj.head;
            tail = obj.tail;
            sz = obj.sz;
            cacheNode = obj.cacheNode;
            cacheIndex = obj.cacheIndex;
            obj.head = nullptr;
            obj.tail = nullptr;
            obj.sz = 0;
            obj.cacheNode = nullptr;
            obj.cacheIndex = -1;
        }
        return *this;
    }

    void invalidateCache() const {
        cacheNode = nullptr;
        cacheIndex = -1;
    }

    Node* getNode(int index) const {
        if (index == cacheIndex && cacheNode) return cacheNode;
        
        Node* curr = nullptr;
        int distFromHead = index;
        int distFromTail = sz - 1 - index;
        int distFromCache = cacheNode ? std::abs(index - cacheIndex) : sz + 1;
        
        if (distFromCache <= distFromHead && distFromCache <= distFromTail) {
            curr = cacheNode;
            if (index > cacheIndex) {
                for (int i = cacheIndex; i < index; ++i) curr = curr->next;
            } else {
                for (int i = cacheIndex; i > index; --i) curr = curr->prev;
            }
        } else if (distFromHead <= distFromTail) {
            curr = head;
            for (int i = 0; i < index; ++i) curr = curr->next;
        } else {
            curr = tail;
            for (int i = sz - 1; i > index; --i) curr = curr->prev;
        }
        
        cacheNode = curr;
        cacheIndex = index;
        return curr;
    }

    void push_back(const ValueType &value) {
        Node* newNode = pool.allocate(value, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        sz++;
        invalidateCache();
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        pool.deallocate(temp);
        sz--;
        invalidateCache();
    }

    void push_front(const ValueType &value) {
        Node* newNode = pool.allocate(value, nullptr, head);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        sz++;
        invalidateCache();
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        pool.deallocate(temp);
        sz--;
        invalidateCache();
    }

    ValueType &front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->data;
    }

    ValueType &back() const {
        if (!tail) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void insert(int index, const ValueType &value) {
        if (index < 0 || index > sz) throw std::out_of_range("Index out of bounds");
        if (index == 0) {
            push_front(value);
        } else if (index == sz) {
            push_back(value);
        } else {
            Node* curr = getNode(index);
            Node* newNode = pool.allocate(value, curr->prev, curr);
            curr->prev->next = newNode;
            curr->prev = newNode;
            sz++;
            invalidateCache();
        }
    }

    void erase(int index) {
        if (index < 0 || index >= sz) throw std::out_of_range("Index out of bounds");
        if (index == 0) {
            pop_front();
        } else if (index == sz - 1) {
            pop_back();
        } else {
            Node* curr = getNode(index);
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            pool.deallocate(curr);
            sz--;
            invalidateCache();
        }
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            pool.deallocate(temp);
        }
        tail = nullptr;
        sz = 0;
        invalidateCache();
    }

    void link(const MyList &obj) {
        if (obj.empty()) return;
        Node* curr = obj.head;
        int n = obj.sz;
        Node* myTail = tail;
        for (int i = 0; i < n; ++i) {
            Node* newNode = pool.allocate(curr->data, myTail, nullptr);
            if (myTail) {
                myTail->next = newNode;
            } else {
                head = newNode;
            }
            myTail = newNode;
            curr = curr->next;
        }
        tail = myTail;
        sz += n;
        invalidateCache();
    }

    MyList cut(int index) {
        if (index < 0 || index > sz) throw std::out_of_range("Index out of bounds");
        MyList result;
        if (index == sz) {
            return result;
        }
        if (index == 0) {
            result.head = head;
            result.tail = tail;
            result.sz = sz;
            head = nullptr;
            tail = nullptr;
            sz = 0;
            invalidateCache();
            return result;
        }
        
        Node* curr = getNode(index);
        
        result.head = curr;
        result.tail = tail;
        result.sz = sz - index;
        
        tail = curr->prev;
        tail->next = nullptr;
        curr->prev = nullptr;
        
        sz = index;
        invalidateCache();
        
        return result;
    }
};

template<typename ValueType>
typename MyList<ValueType>::MemoryPool MyList<ValueType>::pool;

#endif
