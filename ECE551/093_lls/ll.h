#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * previous;
    Node() : data(NULL), next(NULL), previous(NULL) {}
    explicit Node(T d) : data(d), next(NULL), previous(NULL) {}
    //Node(T d, Node * next):data(d), next(NULL){}
  };
  class IndexException : public std ::exception {
    const char * what() { return "Index is not valid"; }
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.size; i++) {
      addBack(rhs[i]);
    }
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }
  LinkedList & operator=(LinkedList & rhs) {
    if (this != &rhs) {
      while (this->head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;
      Node * temp = rhs.head;
      while (temp != NULL) {
        this->addBack(temp->data);
        temp = temp->next;
      }
    }
    return *this;
  }

  int getSize() const { return size; }
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & indexFind(int index);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
};

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * cur = new Node(item);
  size += 1;
  if (head == NULL) {
    head = cur;
    tail = cur;
    return;
  }
  cur->next = head;
  head->previous = cur;
  head = cur;
  return;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * cur = new Node(item);
  size += 1;
  if (tail == NULL) {
    tail = cur;
    head = cur;
    return;
  }
  cur->previous = tail;
  tail->next = cur;
  tail = cur;
  return;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * temp = head;
  while (temp != NULL && !(temp->data == item)) {
    temp = temp->next;
  }
  if (temp == NULL) {
    return false;
  }

  if (size == 1) {
    delete head;
    head = NULL;
    tail = NULL;
    size -= 1;
    return true;
  }
  if (head == temp) {
    head = temp->next;
    temp->next->previous = NULL;
    delete temp;
    size -= 1;
    return true;
  }
  if (tail == temp) {
    tail = temp->previous;
    temp->previous->next = NULL;
    delete temp;
    size -= 1;
    return true;
  }

  temp->previous->next = temp->next;
  temp->next->previous = temp->previous;
  delete temp;
  size -= 1;
  return true;
}
template<typename T>
T & LinkedList<T>::operator[](int index) {
  if (index < 0 || index >= size) {
    throw IndexException();
  }
  Node * temp = head;
  while (index > 0 && temp != NULL) {
    temp = temp->next;
    index -= 1;
  }
  return temp->data;
}
template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  if (index < 0 || index >= size) {
    throw IndexException();
  }
  Node * temp = head;
  while (index > 0 && temp != NULL) {
    temp = temp->next;
    index -= 1;
  }
  return temp->data;
}
template<typename T>
int LinkedList<T>::find(const T & item) {
  int ans = 0;
  Node * temp = head;
  while (temp != NULL && !(temp->data == item)) {
    temp = temp->next;
    ans += 1;
  }
  if (temp == NULL) {
    return -1;
  }
  return ans;
}

#endif
