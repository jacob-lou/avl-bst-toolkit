#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    int height(Node<Key,Value>* node) const;
    void recomputeAllBalances(Node<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    void rebalanceUpward(AVLNode<Key,Value>* start);

};



/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
  if(this->root_ == nullptr){
    this->root_ = new AVLNode<Key,Value>(new_item.first,new_item.second,nullptr);
    static_cast<AVLNode<Key,Value>*>(this->root_)->setBalance(0);
    return;
  }

  Node<Key,Value>* cur = this->root_;
  Node<Key,Value>* parent = nullptr;

  while(cur != nullptr){
    parent = cur;
    if(new_item.first<cur->getKey()){
      cur = cur->getLeft();
    }else if(cur->getKey()<new_item.first){
      cur = cur->getRight();
    }else{
      cur->setValue(new_item.second);
      return;
    }
  }

  AVLNode<Key,Value>* avlParent = static_cast<AVLNode<Key,Value>*>(parent);
  AVLNode<Key,Value>* node = new AVLNode<Key,Value>(new_item.first,new_item.second,avlParent);

  if(new_item.first<parent->getKey()){
    parent->setLeft(node);
  }else{
    parent->setRight(node);
  }

  rebalanceUpward(avlParent);
  recomputeAllBalances(this->root_);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
  Node<Key,Value>* z= this->internalFind(key);
  if(z==nullptr) return;

  if(z->getLeft()!= nullptr && z->getRight()!=nullptr){
    Node<Key,Value>* pred = BinarySearchTree<Key,Value>::predecessor(z);
    nodeSwap(static_cast<AVLNode<Key,Value>*>(z),static_cast<AVLNode<Key,Value>*>(pred));
  }

  Node<Key,Value>* child = (z->getLeft() != nullptr)? z->getLeft():z->getRight();
  AVLNode<Key,Value>* parent = static_cast<AVLNode<Key,Value>*>(z->getParent());

  if (child != nullptr){
    child->setParent(parent); 
  }
  if (parent == nullptr){
    this->root_ = child;
  }else if(z == parent->getLeft()){
    parent->setLeft(child);
  }else{
    parent->setRight(child);
  }
  delete z;

  if(parent!= nullptr){
    rebalanceUpward(parent);
  }else if(this->root_ != nullptr){
    rebalanceUpward(static_cast<AVLNode<Key,Value>*>(this->root_));
  }

  recomputeAllBalances(this->root_);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
int AVLTree<Key, Value>::height(Node<Key,Value>* node) const{
  if(node==nullptr) return 0;
  int hl = height(node->getLeft());
    int hr = height(node->getRight());
    return 1 + (hl > hr ? hl : hr);
}

template<class Key, class Value>
void AVLTree<Key, Value>::recomputeAllBalances(Node<Key,Value>* node){
  if(node == nullptr) return;
  recomputeAllBalances(node->getLeft());
  recomputeAllBalances(node->getRight());

  int bal=height(node->getRight())-height(node->getLeft());
  AVLNode<Key,Value>* avlNode = static_cast<AVLNode<Key,Value>*>(node);
  avlNode->setBalance(static_cast<int8_t>(bal));
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* node){
  if(node==nullptr)return;
  AVLNode<Key,Value>* rightChild = node->getRight();
  if(rightChild == nullptr) return;

  AVLNode<Key,Value>* parent = node->getParent();
  AVLNode<Key,Value>* rightLeft = rightChild->getLeft();

  rightChild->setParent(parent);
  if(parent == nullptr){
    this->root_ = rightChild;
  }else if(node == parent->getLeft()){
    parent->setLeft(rightChild);
  }else{
    parent->setRight(rightChild);
  }

  rightChild->setLeft(node);
  node->setParent(rightChild);

  node->setRight(rightLeft);
  if(rightLeft != nullptr){
    rightLeft->setParent(node);
  }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* node){
  if(node==nullptr)return;
  AVLNode<Key,Value>* leftChild = node->getLeft();
  if(leftChild == nullptr) return;

  AVLNode<Key,Value>* parent = node->getParent();
  AVLNode<Key,Value>* leftRight = leftChild->getRight();

  leftChild->setParent(parent);
  if(parent == nullptr){
    this->root_ = leftChild;
  }else if(node == parent->getLeft()){
    parent->setLeft(leftChild);
  }else{
    parent->setRight(leftChild);
  }

  leftChild->setRight(node);
  node->setParent(leftChild);

  node->setLeft(leftRight);
  if(leftRight != nullptr){
    leftRight->setParent(node);
  }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rebalanceUpward(AVLNode<Key,Value>* start){
  AVLNode<Key,Value>* cur = start;
  while(cur != nullptr){
    int diff = height(cur->getRight())- height(cur->getLeft());
    if(diff <-1){
      AVLNode<Key,Value>* left = cur->getLeft();
      if(height(left->getLeft())>=height(left->getRight())){
        rotateRight(cur);
      }else{
        rotateLeft(left);
        rotateRight(cur);
      }
    }
    else if(diff>1){
      AVLNode<Key,Value>* right = cur->getRight();
      if(height(right->getRight())>=height(right->getLeft())){
        rotateLeft(cur);
      }else{
        rotateRight(right);
        rotateLeft(cur);
      }
    }
    cur = cur->getParent();
  }
}


#endif
