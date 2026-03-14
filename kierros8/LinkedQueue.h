#ifndef QUEUE_H
#define QUEUE_H

enum Error_code { success, overflow, underflow };
typedef double Queue_entry;
typedef Queue_entry Node_entry;

class Queue {
  public:
    // standard Queue methods
    Queue() { front = rear = nullptr; }
    bool empty() const {
      return front == nullptr;
    }

    Error_code append(const Queue_entry &item)
    {
      Node *new_rear = new Node(item);
      if (new_rear == nullptr) return overflow;
      if (rear == nullptr) front = rear = new_rear;
      else {
        rear->next = new_rear;
        rear = new_rear;
      }
      return success;
    }


    Error_code serve() {
      if (front == nullptr) return underflow;
      Node *old_front = front;
      front = old_front->next;
      if (front == nullptr) rear = nullptr;
      delete old_front;
      return success;
    }


    Error_code retrieve(Queue_entry &item) const {
      if (front == nullptr) return underflow;
      item = front->entry;
      return success;
    }

    // safety features for linked structures
    ~Queue() {
      while(!empty())
        serve();
    }

    Queue(const Queue &original) {
      front = rear = nullptr;
      Node *temp = original.front;
      while (temp != nullptr) {
          append(temp->entry);
          temp = temp->next;
      }
    }

    void operator = (const Queue &original) {
      if(this == &original) return;
      while(!empty()) serve();
      Node *temp = original.front;
      while(temp!= nullptr) {
        append(temp->entry);
        temp = temp->next;
      }
    }
  
  protected:
   struct Node {
      Node_entry entry;
      Node *next;

      Node() : entry(0), next(nullptr) {}
      Node(Node_entry item, Node *add_on = nullptr) : entry(item), next(add_on) {}
    };
    Node *front, *rear;
};


class Extended_queue : public Queue {
public:
   bool full() const {
    Node *window = new Node;
    if (window == nullptr) {
      return true;
    }
    delete window;
    return false;
   }

   int size() const {
      Node *window = front;
      int count = 0;
      while (window != nullptr) {
        window = window->next;
        count++;
      }
      return count;
   }

   void clear();
   Error_code serve_and_retrieve(Queue_entry &item);
};



#endif