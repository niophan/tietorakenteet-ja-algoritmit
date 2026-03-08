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
        count = 0;
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

    // Tehtävä 5a.
    // int size() const {
    //   int count = 0;
    //   const Node *current = top_node;
    //   while (current != nullptr) {
    //       ++count;
    //       current = current->next;
    //   }
    //   return count;
    // }

    // Tehtävä 5b
    int size() const {
      return count;
    }

private:
    struct Node {
      Node_entry entry;
      Node *next;

      Node() : entry(0), next(nullptr) {}
      Node(Node_entry item, Node *add_on = nullptr) : entry(item), next(add_on) {}
    };
    Node* top_node;
    int count;
};

#endif