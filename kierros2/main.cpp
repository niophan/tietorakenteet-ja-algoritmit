#include <iostream>
#include "Utility.h"
#include "Life.h"

using namespace std;

int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
   Life configuration;
   char mode;
   bool virhe = true;
   instructions(configuration.get_maxrow(), configuration.get_maxcol());
   configuration.set_dimensions();
   configuration.initialize();
   configuration.print();
   
   do {
    virhe = false;
    cout << "Choose mode to continue program:" << endl;
    cout << "(A) Manual stepping (ask for each generation)" << endl;
    cout << "(B) Animation (automatic with delay)" << endl;
    cout << "Enter choice (A or B): ";
    cin >> mode;

    switch (mode)
    {
      case 'A': 
      case 'a': while (user_says_yes()) {
                      configuration.update();
                      configuration.print();
                      cout << "Continue viewing new generations? " << endl;
                }
                break;       
      case 'B':
      case 'b': configuration.animate();
                break;                                
      default : cout << "Invalid choice. Using manual mode." << endl;
                while (user_says_yes()) {
                      configuration.update();
                      configuration.print();
                      cout << "Continue viewing new generations? " << endl;
                }
    }
  } while(virhe);
   configuration.save_to_file();
}