# Problem 076 - Linklist without name

**ACMOJ Problem ID**: 1363

## Table of Contents

- [Problem 076 - Linklist without name](#problem-076-linklist-without-name)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1363. Linklist without name** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/076/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

在一个风和日丽的下午，Tseruof 同学闲来无事在玩蜘蛛纸牌（其实就是宅着划水），突然一道闪光，那四种花色、十三种数值全部变成了乱码，这使得肉眼识别他的顺序变得极为困难。请你帮忙完成一个程序，来帮他描述在经历一定的操作后牌堆的样子吧！



在这个较大的小作业中，你需要完善以下已经给定接口的链表类。

你需要完成的是，与 `std::list` 中相同的部分，以及以下两个特殊函数：

- `link`：将 `obj` 的内容接到该链表的后面，同时不消去前者的元素。
- `cut`：将该链表以索引值为 $index$ 的节点的前面为界分割成两个部分（举例，$index=10$，那么将会把链表分割为 $0-9$ 与 $10-n$ 的两个部分），前面的部分保持在该链表内不变，原来链表的后半部分作为函数的返回值返回。

对于 `std::list` 中的 `insert` 与 `erase`，我们将输入参数改为位置`index`，规则与上面相同。

`Template`：（并不只需要填充 `todo:` 后面的内容）

```c++
template<typename ValueType>
class MyList
{

public:
    MyList()
    {
        //todo:
    }
    MyList(MyList &&obj) noexcept
    {
        //todo:
    }
    MyList(const MyList &obj)
    {
        //todo:
    }
    ~MyList()
    {
        //todo:
    }

    void push_back(const ValueType &value)
    {
        //todo:
    }
    void pop_back()
    {
        //todo:
    }
    void push_front(const ValueType &value)
    {
        //todo:
    }
    void pop_front()
    {
        //todo:
    }
    ValueType &front() const
    {
        //todo:
    }
    ValueType &back() const
    {
        //todo:
    }
    void insert(int index,const ValueType &value)
    {
        //todo:
    }
    void erase(int index)
    {
        //todo:
    }
    int size() const
    {
        //todo:
    }
    bool empty() const
    {
        //todo:
    }
    void clear()
    {
        //todo:
    }

    void link(const MyList &obj)
    {
        //todo:
    }
    MyList cut(int index)
    {
        //todo:
    }
};
```

### Input Format



### Output Format



### Samples

No sample data provided for this problem.

### Data Constraints

需要注意的是，所有的索引值在此题中都是 0-base的。

由于此题主要考察同学们的一部分OOP能力，因此对于时空复杂度要求相对较松，不必过于担心。

本题不对鲁棒性进行测试。

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/076/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
