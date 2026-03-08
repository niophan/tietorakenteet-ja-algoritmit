#include <iostream>

typedef double Node_entry;

struct Node {
  Node_entry entry;
  Node *next;

  Node() : entry(0), next(nullptr) {}
  Node(Node_entry item, Node *add_on = nullptr) : entry(item), next(add_on) {}
};

int main() {
  // A
  // Node first_node('0');
  // Node *p0 = &first_node;
  // Node *p1 = p0->next = new Node('1');
  // p1->next = nullptr;
  // delete p0;
  // delete p1;

  // B
  // Node second_node('1');
  // Node *p0 = new Node('0');
  // Node *p1 = new Node('1', p0);
  // Node *p2 = p1;
  // p0->next = nullptr; 
  // delete p0;
  // delete p1;
  // delete p2;

  // C  
  // Node first_node('0');
  // Node *p0 = &first_node;
  // Node *p1 = new Node('1');
  // p0->next = p1;
  // Node *p2 = new Node('2', p1);
  // p1->next = p2;
  // delete p0;
  // delete p1;
  // delete p2;


  return 0;

}