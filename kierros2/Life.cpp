#include <iostream>
#include "Life.h"
#include <string>
#include <limits>
#include <fstream>

using namespace std;

Life::Life() : maxrow(20), maxcol(60)
/*
Pre:  None.
Post: Life object is constructed with default dimensions 20x60.
      Grid is initialized as empty vector.
*/
{
   // Initialize grid with default size
   grid.assign(maxrow + 2, vector<int>(maxcol + 2, 0));
}

Life::~Life()
/*
Pre:  Life object exists.
Post: Vector grid is automatically cleaned up (no manual delete needed).
*/
{
   grid.clear(); 
}

void Life::set_dimensions()
/*
Pre:  None.
Post: User inputs grid dimensions, grid is resized and cleared.
*/
{
   cout << "Enter the number of rows for the game area (1-20): ";
   cin >> maxrow;
   if (maxrow < 1 || maxrow > 20) {
      cout << "Invalid input. Using default 20 rows." << endl;
      maxrow = 20;
   }

   cout << "Enter the number of columns for the game area (1-60): ";
   cin >> maxcol;
   if (maxcol < 1 || maxcol > 60) {
      cout << "Invalid input. Using default 60 columns." << endl;
      maxcol = 60;
   }

   // Resize grid with new dimensions, allocating all to 0
   grid.assign(maxrow + 2, vector<int>(maxcol + 2, 0));
   cout << "Game area set to " << maxrow << " x " << maxcol << endl;
}

int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
   int i, j;
   int count = 0;
   for (i = row - 1; i <= row + 1; i++)
      for (j = col - 1; j <= col + 1; j++)
         count += grid[i][j];  //  Increase the count if neighbor is alive.
   count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
   return count;
}

void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
   int row, col;
    // Create temporary grid for next generation
   vector<vector<int>> new_grid(maxrow + 2, vector<int>(maxcol + 2, 0));

   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         switch (neighbor_count(row, col)) {
         case 2:
            new_grid[row][col] = grid[row][col];  //  Status stays the same.
            break;
         case 3:
            new_grid[row][col] = 1;                //  Cell is now alive.
            break;
         default:
            new_grid[row][col] = 0;                //  Cell is now dead.
         }

   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         grid[row][col] = new_grid[row][col];
}

void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
   int row, col;
   char option;
   bool virhe = true;

   auto file = [&](){
      string fileConfig;
      ifstream MyFile("configuration.txt");
      int row = 1;
      if (MyFile.is_open()) {
         while(getline(MyFile, fileConfig) && row <= maxrow) {
            if (fileConfig.length() >= 2 && fileConfig.substr(0, 2) == "//") {
               continue;
            }
            if (fileConfig == "p" || fileConfig == "P") {
               break;
            }
            for (int col = 1; col <= maxcol; col++) {
               if (col <= fileConfig.length()) {
                  char c = fileConfig[col - 1];
                  grid[row][col] = (c == 'x' || c == 'X') ? 1 : 0;
               } else {
                  grid[row][col] = 0;
               }
            }
            row++;
         } 
      } else {
         cout << "Error: File cannot be opened" << endl;
      }

      MyFile.close();
   };

   auto keyboard = [&]() {
      cout << "---------------" << endl;
      cout << "ATTENTION!" << endl;
      cout << "---------------" << endl;
      cout << "Use 'x' (or 'X') for occupied cells; blanks (or any other char) mean empty." << endl;
      cout << "Extra characters beyond " << maxcol << " column are ignored; missing characters are treated as blanks." << endl;
      cout << "Terminate the input with a single 'p' line to stop early; remaining rows become empty." << endl;
      // Drop any leftover newline before using getline
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      string input;
      for (int row = 1; row <= maxrow; row++) {
         getline(cin, input);
         if (!cin) {
               input.clear();
               cin.clear();
         }
         if (input == "p" || input == "P") {
            break;
         }
         for (int col = 1; col <= maxcol; col++) {
            if (col <= input.length()) {
               char c = input[col - 1];
               grid[row][col] = (c == 'x' || c == 'X') ? 1 : 0;
            } else {
               grid[row][col] = 0;
            }
         }
      }
   };


   for (row = 0; row <= maxrow+1; row++)
      for (col = 0; col <= maxcol+1; col++)
         grid[row][col] = 0;
   cout << "---------------" << endl;
   cout << "Please choose your option based on A or B:" << endl;
   cout << "---------------" << endl;
   cout << "(A) Reading game initial configuration from the keyboard?" << endl;
   cout << "(B) Or from the a file?" << endl;

   do {
    virhe = false;
    cout << "Valitse (A) tai (B):";
    cin >> option;

    switch (option)
    {
      case 'A' :  keyboard();
                  break;       
      case 'B' :  file();
                  break;                                
      default  :  cout << "Wrong input! Please type with a capital character again either A or B" << endl;   
                  virhe = true;
                  break; 
    }
  } while(virhe);

}
 


void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
   int row, col;
   cout << "\nThe current Life configuration is:" <<endl;
   for (row = 1; row <= maxrow; row++) {
      for (col = 1; col <= maxcol; col++)
         if (grid[row][col] == 1) cout << 'x';
         else cout << '-';
      cout << endl;
   }
   cout << endl;
}

void Life::save_to_file()
{
   int row, col;
   ofstream writeFile("configuration.txt");
   if (writeFile.is_open()) {
      for (row = 1; row <= maxrow; row++) {
         for (col = 1; col <= maxcol; col++)
            if (grid[row][col] == 1) writeFile.write("x", 1);
            else writeFile.write("-", 1);
         writeFile << endl;
      }
   writeFile.close();
   cout << "The pattern is written to the configuration.txt" << endl;
   } else {
    cout << "Error: cannot opened the file" << endl;
   }
}
