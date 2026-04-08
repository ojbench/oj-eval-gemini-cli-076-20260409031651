#include <iostream>
#include "MyList.hpp"

int main() {
    MyList<int> a;
    a.push_back(1);
    a.link(a);
    std::cout << a.size() << std::endl;
    return 0;
}
