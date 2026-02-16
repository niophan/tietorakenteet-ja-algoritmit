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

void introduction();
char get_command();
bool do_command(char c, Queue &test_queue);
void help();

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


void introduction()
/*
Post: Print a brief introduction for the queue demo.
*/
{
   cout << "Queue demonstration. Enter H for help." << endl;
}


char get_command()
/*
Post: Read a command character from standard input.
*/
{
   char c;
   cout << "Enter command: " << flush;
   cin >> c;
   c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
   if (c == 'h') {
      help();
   }
   return c;
}



int main()
/*
Post: Accepts commands from user as a menu-driven demonstration program for
   the class Queue.
Uses: The class Queue and the functions introduction,
      get_command, and do_command.
*/

{
   Queue test_queue;
   introduction();
   while (do_command(get_command(), test_queue));
}


void help()
/*
Post: A help screen for the program is printed, giving the meaning of each
      command that the user may enter.
*/

{
   cout << endl
        << "This program allows the user to enter one command" << endl
        << "(but only one) on each input line." << endl
        << "For example, if the command S is entered, then" << endl
        << "the program will serve the front of the queue." << endl
        << endl

        << " The valid commands are:" << endl
        << "A - Append the next input character to the queue" << endl
        << "S - Serve the front of the queue" << endl
        << "R - Retrieve and print the front entry." << endl
        << "H - This help screen" << endl
        << "Q - Quit" << endl

        << "Press <Enter> to continue." << flush;

   char c;
   do {
      cin.get(c);
   } while (c != '\n');
}


bool do_command(char c, Queue &test_queue)
/*
Pre:  c represents a valid command.
Post: Performs the given command c on the Queue test_queue.
      Returns false if c == 'q', otherwise returns true.
Uses: The class Queue.
*/

{
   bool continue_input = true;
   Queue_entry x;

   switch (c) {
   case 'a':
      cout << "Enter a character to append: " << flush;
      cin >> x;
      if (test_queue.append(x) == overflow)
         cout << "Queue is full." << endl;
      else
         cout << endl
              << "Item is added to the rear of the queue"
              << endl;
      break;
   
   case 's':
      if (test_queue.serve() == underflow)
         cout << "Queue is empty." << endl;
      else
         cout << endl
              << "The front of the Queue is removed"
              << endl;
      break;

   case 'r':
      if (test_queue.retrieve(x) == underflow)
         cout << "Queue is empty." << endl;
      else
         cout << endl
              << "The first entry is: " << x
              << endl;
      break;
   
   case 'q':
      cout << "Queue demonstration finished." << endl;
      continue_input = false;
      break;
    //  Additional cases will cover other commands.
   }
   return continue_input;
}
