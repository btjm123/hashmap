<h1 align=center>✨ Yet Another HashMap Implementation ✨</h1>

<div align=center>
  <img src="https://github.com/btjm123/hashmap/actions/workflows/test-macos.yaml/badge.svg"/>
  <img src="https://github.com/btjm123/hashmap/actions/workflows/test-ubuntu.yaml/badge.svg"/>
</div>

Whilst studying in university, I had the opportunity to study [2040S - Data Structures & Algorithms](https://www.comp.nus.edu.sg/~stevenha/cs2040s.html), which sparked my curiosity in how different hashmaps implementations resolve hash collisions (i.e linear probing, chaining using linked lists). Each approach has its own tradeoffs, but we were taught generally these approaches booasted the same asymptotic time complexity - theoretically at least. I wanted to put such claims to the test - to test if these approaches do translate to similiar real-world performance


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
x.remove({1, 10});
```
- Size
```cpp
x.size();
```
- Generic Types
```
benn::ChainingHashMap<double, bool> x;
benn::OpenAddressingHashMap<std::string, int> y;
```

## Build
This project uses [CMake](https://cmake.org/)
```sh
mkdir build && cd build && cmake .. && make
```

## Testing
This project uses [Google Test](https://github.com/google/googletest)
```sh
cd build && ./tests/open_addressing_hashmap.cpp
cd build && ./tests/chaining_hashmap.cpp
```
