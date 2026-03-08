#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

enum Error_code { success, overflow, underflow };
typedef double Node_entry;


class LinkedStack {
public:
    LinkedStack() : top_node(nullptr) {}
    
    ~LinkedStack() {
        while (top_node != nullptr) {
            Node *temp = top_node;
            top_node = top_node->next;
            delete temp;
        }
    }
    
    bool isEmpty() const {
        return top_node == nullptr;
    }
    Error_code pop() {
      Node *old_top = top_node;
      if (top_node == nullptr) {
        return underflow;
      }
      top_node = old_top->next;
      delete old_top;
      return success;
    }

    Error_code push(const Node_entry &item) {
      Node *new_top = new Node(item, top_node);
      if (new_top == nullptr) {
        return overflow;
      }
      top_node = new_top;
      return success;
    }

    Error_code top(Node_entry &item) const {
      if (top_node == nullptr) {
        return underflow;
      }

      item = top_node->entry;
      return success;
    }

private:
    struct Node {
      Node_entry entry;
      Node *next;

      Node() : entry(0), next(nullptr) {}
      Node(Node_entry item, Node *add_on = nullptr) : entry(item), next(add_on) {}
    };
    Node* top_node;
};

#endif