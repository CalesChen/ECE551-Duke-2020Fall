#include <cstdio>
#include <exception>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K _key, V _value) : key(_key), value(_value), left(NULL), right(NULL) {}
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
    Node * root = new Node(rhs->key, rhs->value);
    root->left = copytree(rhs->left);
    root->right = copytree(rhs->right);
    return root;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(Node * _root) : root(_root) {}
  BstMap(const BstMap & rhs) { root = copytree(rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (&rhs != this) {
      BstMap temp(rhs);
      Node * temp_r = root;
      root = temp.root;
      temp.root = temp_r;
    }
    return *this;
  }
  ~BstMap() { decons(root); }

  Node ** nodeFinder(const K & key) const {
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
  virtual void add(const K & key, const V & value) {
    Node ** dest = nodeFinder(key);
    if (*dest == NULL) {
      *dest = new Node(key, value);
    }
    else {
      (*dest)->value = value;
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node ** dest = nodeFinder(key);
    if (*dest == NULL) {
      throw std::invalid_argument("The key is not Found.\n");
    }
    return (*dest)->value;
  }
  virtual void remove(const K & key) {
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
