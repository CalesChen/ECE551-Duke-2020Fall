#include "node.h"
#define N 257
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;

  for (int i = 0; i < N; ++i) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  while (pq.size() > 1) {
    Node * l = pq.top();
    pq.pop();
    Node * r = pq.top();
    pq.pop();
    pq.push(new Node(l, r));
  }
  return pq.top();
}
