#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "avlbst.h"

// 递归算高度 + 检查 AVL 平衡性
template <typename K, typename V>
int heightAndCheck(Node<K,V>* n, bool& ok) {
  if(!n) return 0;
  int lh = heightAndCheck(n->getLeft(), ok);
  int rh = heightAndCheck(n->getRight(), ok);
  if(std::abs(lh - rh) > 1) ok = false;
  return std::max(lh, rh) + 1;
}

// 中序遍历拿 key 序列（必须有序）
template <typename K, typename V>
void inorder(Node<K,V>* n, std::vector<K>& out) {
  if(!n) return;
  inorder(n->getLeft(), out);
  out.push_back(n->getKey());
  inorder(n->getRight(), out);
}

TEST(AVL, InsertKeepsBSTOrderAndBalance) {
  AVLTree<int,int> t;
  std::vector<int> keys = {10, 20, 30, 40, 50, 25, 5, 1, 8};
  for(int k: keys) t.insert({k, k});

  std::vector<int> got;
  inorder(t.getRoot(), got);   // 这里用 bst.h 里通常会有 getRoot(); 若没有，见下面注释

  auto sorted = keys;
  std::sort(sorted.begin(), sorted.end());
  sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
  EXPECT_EQ(got, sorted);

  bool ok = true;
  heightAndCheck(t.getRoot(), ok);
  EXPECT_TRUE(ok);
}
