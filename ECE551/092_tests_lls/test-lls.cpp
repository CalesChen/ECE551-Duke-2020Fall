#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.h"

void testList() {
  IntList t1 = IntList();
  assert(t1.getSize() == 0 && t1.size == 0);
  assert(t1.head == NULL && t1.tail == NULL);
  t1.addBack(1);
  assert(t1.getSize() == 1 && t1.size == 1);
  assert(t1.head == t1.tail);
  assert(t1.head->data == 1);
  t1.addFront(2);
  assert(t1.getSize() == 2 && t1.size == 2);
  assert(t1.head->data == 2 && t1[0] == 2);
  assert(t1.head = t1.head->next->prev);
  assert(t1.tail->data == 1 && t1[1] == 1);
  assert(t1.head->next->next == NULL && t1.head->next == t1.tail);
  //check assiment "=" testcase10
  IntList t2;
  t2 = t1;
  assert(t2.getSize() == 2 && t2.size == 2);
  assert(t2[0] == 2 && t2[1] == 1);
  assert(t2.head->next->next == NULL && t2.head->next == t2.tail);
  assert(t2.head->next->prev == t2.head);
  //check copy constructor testcase11
  IntList t3 = IntList(t2);
  assert(t3.getSize() == 2 && t3.size == 2);
  assert(t3[0] == 2 && t3[1] == 1);
  assert(t3.head->next->next == NULL && t3.head->next == t3.tail);
  assert(t3.head->next->prev == t3.head);
  // Check addFront and addBack
  t1.addFront(3);
  t1.addBack(2);
  t1.addBack(3);
  assert(t1[0] == 3 && t1[1] == 2 && t1[2] == 1 && t1[3] == 2 && t1[4] == 3);
  // Check remove
  t2 = t1;
  assert(t2[0] == 3);
  bool b1 = t2.remove(3);
  bool b2 = t2.remove(4);
  assert(b1 == true && b2 == false);
  assert(t2[0] == 2 && t2[2] == 2);
  assert(t2.getSize() == 4 && t2.size == 4);
  // Check Find
  int f1 = t1.find(3);
  int f2 = t1.find(4);
  assert(f1 == 0 && f2 == -1);
  // Check Remove corner case
  t3.remove(2);
  assert(t3.getSize() == 1 && t3.size == 1 && t3[0] == 1);
  assert(t3.head->prev == NULL);
  t3.remove(1);
  assert(t3.getSize() == 0 && t3.size == 0);
  assert(t3.head == NULL && t3.tail == NULL);
  // testcase 20
  t1.remove(1);
  assert(t1[0] == 3 && t1[1] == 2 && t1[2] == 2 && t1[3] == 3);
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
