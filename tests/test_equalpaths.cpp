#include <gtest/gtest.h>
#include "equal-paths.h"

TEST(EqualPaths, TrivialCases) {
  EXPECT_TRUE(equalPaths(nullptr));
  Node* one = new Node(1);
  EXPECT_TRUE(equalPaths(one));
  delete one;
}

TEST(EqualPaths, EqualAndNotEqual) {
  // Equal: both sides depth 2
  Node* t1 = new Node(1,
              new Node(2, new Node(4), nullptr),
              new Node(3, nullptr, new Node(5)));
  EXPECT_TRUE(equalPaths(t1));

  // Not equal: left depth 3, right depth 2
  Node* t2 = new Node(1,
              new Node(2, new Node(4, new Node(6), nullptr), nullptr),
              new Node(3, new Node(5), nullptr));
  EXPECT_FALSE(equalPaths(t2));

  // cleanup (simple manual delete)
  // t1
  delete t1->left->left;
  delete t1->left;
  delete t1->right->right;
  delete t1->right;
  delete t1;

  // t2
  delete t2->left->left->left;
  delete t2->left->left;
  delete t2->left;
  delete t2->right->left;
  delete t2->right;
  delete t2;
}
