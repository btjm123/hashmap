<h1 align=center>✨ Yet Another HashMap Implementation ✨</h1>

<div align=center>
  <img src="https://github.com/btjm123/hashmap/actions/workflows/test-macos.yaml/badge.svg"/>
  <img src="https://github.com/btjm123/hashmap/actions/workflows/test-ubuntu.yaml/badge.svg"/>
</div>


During university, I had the opportunity to study [2040S - Data Structures & Algorithms](https://www.comp.nus.edu.sg/~stevenha/cs2040s.html), which sparked my curiosity in how different hashmaps implementations resolve hash collisions (i.e linear probing, chaining using linked lists). 

Each approach has its own tradeoffs, but we were taught generally these approaches boasted the same asymptotic time complexity - theoretically at least. I wanted to put such claims to the test - to test if these approaches do translate to similar real-world performance


## Example

```cpp
#include "ChainingHashMap.hpp"
#include <iostream>
int main () {
  benn::ChainingHashMap<int, int> x;
  //...
}
```

## Features
- Insertion
```cpp
x[1] = 10;
x.insert({1, 10});
```
- Deletion
```cpp
x.remove(1);
```
- Existence of key
```cpp
x.count(1);
```
- Size
```cpp
x.size();
x.getBucketCount();
```
- Generic Types
```cpp
benn::ChainingHashMap<double, bool> x;
benn::OpenAddressingHashMap<std::string, int> y;
```

## Build
This project uses [CMake](https://cmake.org/)
```sh
mkdir build && cd build && cmake .. && make
```

## Test
This project uses [Google Test](https://github.com/google/googletest)
```sh
cd build && ./tests/open_addressing_hashmap
cd build && ./tests/chaining_hashmap
```

## Benchmark
My CPU stats:
```sh
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 1.78, 2.28, 2.49
```

![Figure_1](https://github.com/user-attachments/assets/c2243376-98a3-464f-b8bc-0f68a677c9aa)

To be very honest, I'm not very sure how to explain this graph. 

My initial hypothesis:  While resizing the table introduces a temporary performance drop due to a complete rehashing, the cost of resizing is amortized across many find operations invoked later (hence the performance increase). 

I'll be happy to be proven wrong though/offered alternative ideas (and how to prove them).

## Future
- Quadratic Probing
- Double Hashing
- Implement `.start()` and `.end()`
- Create my own `LinkedList` instead of using `std::list` for **ChainingHashMap**
