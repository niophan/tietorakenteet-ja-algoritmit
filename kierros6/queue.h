#ifndef QUEUE_H
#define QUEUE_H

#include <cctype>
#include <iostream>
#include <string>

using namespace std;
using Queue_entry = char;

const int maxqueue = 10;
enum Error_code { success, overflow, underflow };

class Queue {
public:
   Queue();
   bool empty() const;
   Error_code serve();
   Error_code append(const Queue_entry &item);
   Error_code retrieve(Queue_entry &item) const;

protected:
   int count;
   int front, rear;
   Queue_entry entry[maxqueue];
};

Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
   count = 0;
   rear = maxqueue - 1;
   front = 0;
}


bool Queue::empty() const
/*
Post: Return true if the Queue is empty, otherwise return false.
*/
{
   return count == 0;
}


Error_code Queue::append(const Queue_entry &item)
/*
Post: item is added to the rear of the Queue. If the Queue is full
return an Error_code of overflow and leave the Queue unchanged.
*/

{
   if (count >= maxqueue) return overflow;
   count++;
   rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
   entry[rear] = item;
   return success;
}


Error_code Queue::serve()
/*
Post: The front of the Queue is removed. If the Queue
is empty return an Error_code of underflow.
*/

{
   if (count <= 0) return underflow;
   count--;
   front = ((front + 1) == maxqueue) ? 0 : (front + 1);
   return success;
}


Error_code Queue::retrieve(Queue_entry &item) const
/*
Post: The front of the Queue retrieved to the output
      parameter item. If the Queue is empty return an Error_code of underflow.
*/

{
   if (count <= 0) return underflow;
   item = entry[front];
   return success;
}


class Extended_queue : public Queue {
public:
   bool full() const;
   int size() const;
   void clear();
   Error_code serve_and_retrieve(Queue_entry &item);
};


bool Extended_queue::full() const
/*
Post: Return true if the Queue is full, otherwise return false.
*/
{
   return count >= maxqueue;
}


int Extended_queue::size() const
/*
Post: Return the number of entries in the Queue.
*/
{
   return count;
}


void Extended_queue::clear()
/*
Post: All entries in the Queue are removed; it is now empty.
*/
{
   count = 0;
   rear = maxqueue - 1;
   front = 0;
}


Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
/*
Post: The front of the Queue is retrieved to item and removed.
      If the Queue is empty return an Error_code of underflow.
*/
{
   if (retrieve(item) == underflow) return underflow;
   return serve();
}

#endif