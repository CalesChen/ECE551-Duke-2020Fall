#include "set.h"
#include <cstdio>
#include <exception>

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(T _key) : key(_key), left(NULL), right(NULL) {}
  };
  Node * root;
  void decons(Node * root) {
    if (root == NULL) {
      return;
    }
    decons(root->left);
    decons(root->right);
    delete root;
    return;
  }
  Node * copytree(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * root = new Node(rhs->key);
    root->left = copytree(rhs->left);
    root->right = copytree(rhs->right);
    return root;
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(Node * _root) : root(_root) {}
  BstSet(const BstSet & rhs) { root = copytree(rhs.root); }

  BstSet & operator=(const BstSet & rhs) {
    if (&rhs != this) {
      BstSet temp(rhs);
      Node * temp_r = root;
      root = temp.root;
      temp.root = temp_r;
    }
    return *this;
  }
  ~BstSet() { decons(root); }

  Node ** nodeFinder(const T & key) const {
    Node ** res = const_cast<Node **>(&root);
    while (*res != NULL) {
      if ((*res)->key > key) {
        res = &(*res)->left;
      }
      else if ((*res)->key < key) {
        res = &(*res)->right;
      }
      else {
        return res;
      }
    }
    return res;
  }
  virtual void add(const T & key) {
    Node ** dest = nodeFinder(key);
    if (*dest == NULL) {
      *dest = new Node(key);
    }
    else {
      (*dest)->key = key;
    }
  }

  virtual bool contains(const T & key) const {
    Node ** dest = nodeFinder(key);
    if (*dest == NULL) {
        return false;
    }
    return true;
  }

  virtual void remove(const T & key) {
    Node ** dest = nodeFinder(key);
    if (*dest == NULL) {
      return;
    }
    Node * temp = *dest;
    if (temp->left == NULL) {
      Node * rep = temp->right;
      delete temp;
      *dest = rep;
      return;
    }
    else if (temp->right == NULL) {
      Node * rep = temp->left;
      delete temp;
      *dest = rep;
      return;
    }
    else {
      Node ** rep = &temp->right;
      while ((*rep)->left != NULL) {
        rep = &(*rep)->left;
      }
      *dest = *rep;
      *rep = (*rep)->right;
      (*dest)->left = temp->left;
      (*dest)->right = temp->right;
      delete temp;
    }
  }
};

