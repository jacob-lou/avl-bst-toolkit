#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
static int height(Node* r){
  if(!r) return 0;
  int lh = height(r->left);
  int rh = height(r->right);
  return (lh > rh ? lh : rh) + 1;
}

bool equalPaths(Node * root)
{
    // Add your code below
  if (root == nullptr)return true;
  bool leaf = (root->left == nullptr && root->right == nullptr);
  if(leaf) return true;

  if(root->left == nullptr){
    return equalPaths(root->right);
  }

  if(root->right == nullptr){
    return equalPaths(root->left);
  }

  return equalPaths(root->left)&& equalPaths(root->right)&&(height(root->left)==height(root->right));
}

