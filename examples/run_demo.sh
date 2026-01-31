#!/usr/bin/env bash
set -e

echo "== BST/AVL demo =="
g++ -std=c++17 -O2 bst-test.cpp -o demo_bst
./demo_bst
echo

echo "== equalPaths demo =="
g++ -std=c++17 -O2 equal-paths.cpp equal-paths-test.cpp -o demo_equalpaths
./demo_equalpaths
