#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int maxstack = 10;

typedef double Stack_entry;
enum Error_code { success, overflow, underflow };

class Stack {
  public:
      Stack() : count(0), top_node(nullptr) {}

      Stack(const Stack &other) = delete;
      Stack &operator=(const Stack &other) = delete;

      ~Stack() {
        clear();
      }

      Error_code pop() {
        Node *old_top = top_node;
        if (count == 0 || top_node == nullptr) {
          return underflow;
        }
        top_node = old_top->next;
        delete old_top;
        --count;
        return success;
      }

      Error_code push(const Stack_entry &item) {
        if (count >= maxstack) {
          return overflow;
        }

        Node *new_top = new Node(item, top_node);
        top_node = new_top;
        ++count;
        return success;
      }

      Error_code top(Stack_entry &item) const {
        if (count == 0) {
          return underflow;
        }

        item = top_node->entry;
        return success;
      }

      bool empty() const { return count == 0; }

      void clear() {
        while (!empty()) {
          pop();
        }
      }

      bool full() const {
        return false;
      }

      int size() const { return count; }

    private:
      struct Node {
        Stack_entry entry;
        Node *next;

        Node(const Stack_entry &value, Node *link) : entry(value), next(link) {}
      };

      int count;
      Node *top_node;
};

#endif