typedef double Stack_entry;
#include "Stack.h"
#include <cmath>


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
          command == '%' || command == '^' || command == 'v' ||
          command == 'x' || command == 's' || command == 'a' || command == 'q' ) waiting = false;
      else {
         cout << "Please enter a valid command:"   << endl
              << "[?]push to stack   [=]print top" << endl
              << "[+] [-] [*] [/] [%] [^] [v]  are arithmetic operations" << endl
              << "[x]change position between two values" << endl
              << "[s]calculate the sum [a]compute average" << endl
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
   double p, q, r, m, sum, average, remainder;
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
   
   case '*':
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
            if (numbers.push(q * p) == overflow)
               cout << "Warning: Stack full, lost result" << endl;
         }
      }
      break;

   case '/':
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
            if (numbers.push(q / p) == overflow)
               cout << "Warning: Stack full, lost result" << endl;
         }
      }
      break;

   case '%':
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
            remainder = fmod(q, p);
            if (numbers.push(remainder) == overflow)
               cout << "Warning: Stack full, lost result" << endl;
         }
      }
      break;
   
   case '^':
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
            if (numbers.push(pow(q, p)) == overflow)
               cout << "Warning: Stack full, lost result" << endl;
         }
      }
      break;   
   
   case 'v':
      if (numbers.top(p) == underflow)
         cout << "Stack empty" << endl;
      else {
         numbers.pop();
         if (numbers.push(sqrt(p)) == overflow)
         cout << "Warning: Stack full, lost result" << endl;
      }
      break;   

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
            cout << "Position of the two topmost is changed" << endl;
         }
      }
      break;

   case 's':
      sum = 0;
      while(!numbers.empty()) {
         numbers.top(r);
         numbers.pop();
         sum += r;
      }
      numbers.push(sum);
      cout << "The sum of the stack is: " << sum << endl;
      break;
   
   case 'a':
      sum = 0;
      m = 0;
      average = 0;
      while(!numbers.empty()) {
         numbers.top(r);
         numbers.pop();
         sum += r;
         m++;
      }
      average = sum / m;
      numbers.push(average);
      cout << "Average of the stack is: " << average << endl;
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
   cout << "The program is divided into two different modes: DC & Prompt Mode "
        << ", based on how you run the program in terminal." << endl;
   cout << "- DC mode: ./calculator" << endl;
   cout << "- Prompt mode: ./calculator -p" << endl;
   cout << "Below  is available and valid commands:" << endl;
   cout << "[?] Push a new number onto the stack." << endl;
   cout << "[=] Print the value at the top of the stack." << endl;
   cout << "[+] Add the two topmost numbers." << endl;
   cout << "[-] Substract the two topmost numbers." << endl;
   cout << "[*] Multiply the two topmost numbers." << endl;
   cout << "[/] Divide the two topmost numbers." << endl;
   cout << "[%] Calculate remainder after dividing" << endl;
   cout << "[^] Power the second number by the first number." << endl;
   cout << "[v] Computer the square root of the topmost number." << endl;
   cout << "[x] Exchange the position of the two topmost numbers." << endl;
   cout << "[s] Sum all values currently in the stack." << endl;
   cout << "[s] Compute the average of all stack values." << endl;
   cout << "[q] Quit the program." << endl;
   cout << "Enter one command at a time. " 
        << "With DC mode, calculation is implemented as a sequence input separated by whitespace. " 
        << "With Prompt mode, calculation is waiting for each command provided by user." << endl;
}

int main(int argc, char* argv[])
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/

{
   Stack stored_numbers;
   string input;
   bool closing = true;
   introduction();
   instructions();
   cout << "------------------Calculator--------------------"<< endl;
   if (argc > 1 && string(argv[1]) == "-p") {
      cout << "The program is running under prompt mode" << endl;
      cout << "Example demontration by typing: ? (enter) 4 (enter) ? (enter) 1 (enter) ? (enter) 4 (enter) a (enter), result will be 3" << endl;
      while (do_command(get_command(), stored_numbers));
   }
   
   if(argc == 0) {
      while(closing) {
         cout << "The program is running under DC mode(default)" << endl;
         cout << "Example demontration by typing a sequence of text: 1 3 + 7.5 - =, result will be -3.5" << endl;
         while(cin >> input) {
            if (input.size() == 1 && string("?=+-*/%^vxsq").find(input[0]) != string::npos) {
               if (input[0] == 'q') {
                  cout << "Calculation finished." << endl;
                  closing = false;
                  break;
               }
               do_command(input[0], stored_numbers);
               continue;
            }

            try {
               double value = stod(input);
               stored_numbers.push(value);
            } catch (const invalid_argument&) {
               cout << "Invalid input: " << input << endl;
            } catch (const out_of_range&) {
               cout << "Number out of range: " << input << endl;
            }
         }
      }
   }
}