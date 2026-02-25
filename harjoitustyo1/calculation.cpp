typedef double Stack_entry;
#include "Stack.h"

char get_command()
{
   char command;
   bool waiting = true;
   cout << "Select command and press <Enter>:";

   while (waiting) {
      cin >> command;
      command = tolower(command);
      if (command == '?' || command == '=' || command == '+' ||
          command == '-' || command == '*' || command == '/' ||
          command == 'x' || command == 'q' ) waiting = false;
      else {
         cout << "Please enter a valid command:"   << endl
              << "[?]push to stack   [=]print top" << endl
              << "[+] [-] [*] [/]   are arithmetic operations" << endl
              << "[Q]uit." << endl;
      }
   }
   return command;
}


bool do_command(char command, Stack &numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/

{
   double p, q;
   switch (command) {
   case '?':
      cout << "Enter a real number: " << flush;
      cin >> p;
      if (numbers.push(p) == overflow)
         cout << "Warning: Stack full, lost number" << endl;
      break;

   case '=':
      if (numbers.top(p) == underflow)
         cout << "Stack empty" << endl;
      else
         cout << p << endl;
      break;

   case '+':
      if (numbers.top(p) == underflow)
         cout << "Stack empty" << endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            cout << "Stack has just one entry" << endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            if (numbers.push(q + p) == overflow)
               cout << "Warning: Stack full, lost result" << endl;
         }
      }
      break;

   //   Add options for further user commands.
   case 'x':
      if (numbers.top(p) == underflow)
         cout << "Stack empty" << endl;
      else {
         numbers.pop();
         if(numbers.top(q) == underflow) {
            cout << "Stack has just one entry" << endl;
            numbers.push(p);
         } else {
            numbers.pop();
            numbers.push(p);
            numbers.push(q);
         }
      }
      break;

   case '-':
      if (numbers.top(p) == underflow)
         cout << "Stack empty" << endl;
      else {
         numbers.pop();
         if(numbers.top(q) == underflow) {
            cout << "Stack has just one entry" << endl;
            numbers.push(p);
         } else {
            numbers.pop();
            if(numbers.push(q - p) == overflow) {
               cout << "Warning: Stack full, lost result" << endl;
            }
         }
      }
      break;
   
   case 'q':
      cout << "Calculation finished.\n";
      return false;
   }
   return true;
}


void introduction()
/*
Post: Print a brief introduction for the postfix calculator demo.
*/
{
   cout << "------------------Introduction--------------------"<< endl;
   cout << "Introduction: This program is a postfix calculator that uses stack to perfom artihmetic operations. "
        << "The user gives command to the calculator, which work on the data in the stack "
        << "and prints results based on postfit notation. "
        << "Operatiors always use values stored on the stack, and results will be pushed back onto the stack at the end." << endl;
}

void instructions()
/*
Post: Print a brief instruction for the postfix calculator demo.
*/
{
   cout << "------------------Instructions--------------------"<< endl;
   cout << "Available and valid commands:" << endl;
   cout << "[?] Push a new number onto the stack." << endl;
   cout << "[=] Print the value at the top of the stack." << endl;
   cout << "[+] Add the two topmost numbers." << endl;
   cout << "[-] Substract the two topmost numbers." << endl;
   cout << "[*] Multiply the two topmost numbers." << endl;
   cout << "[/] Divide the two topmost numbers." << endl;
   cout << "[x] Exchange the position of the two topmost numbers." << endl;
   cout << "[s] Sum all values currently in the stack." << endl;
   cout << "[s] Compute the average of all stack values." << endl;
   cout << "[q] Quit the prohram." << endl;
   cout << "Enter one command at a time." << endl;
}

int main()
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/

{
   Stack stored_numbers;
   introduction();
   instructions();
   while (do_command(get_command(), stored_numbers));
}