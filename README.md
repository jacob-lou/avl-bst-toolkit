# C++ Trees Toolkit: BST/AVL + Equal-Paths Checker

This repository contains two small C++ modules focused on recursive tree reasoning and self-balancing search trees:

- **BST/AVL** implementation (in `bst.h`, `avlbst.h`) + a small interactive/print demo (`bst-test.cpp`)
- **Equal Paths** checker (`equal-paths.cpp/.h`) that determines whether all root-to-leaf paths have the same length

## What’s inside

### 1) BST / AVL (Self-balancing Tree)
- Implements a Binary Search Tree interface and an AVL variant
- Demonstrates insertions and structure printing in `bst-test.cpp`
- Focus areas: rotations, re-balancing, maintaining BST invariants

### 2) `equalPaths()` (Recursive Tree Property Check)
- `equalPaths(Node* root)` returns `true` if **all root-to-leaf paths** have **equal length**
- Uses recursion (tree height reasoning)

## Quick Start (Makefile)

Build:
```bash
make
```

Run demos:
```bash
./bst-test
./equal-paths-test
```

Clean:
```bash
make clean
```

## Build with CMake (optional, more “project-style”)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```
If you add unit tests later, you can run:
```bash
ctest --test-dir build --output-on-failure
```
