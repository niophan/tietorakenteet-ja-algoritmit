#ifndef LIFE_LIFE_H
#define LIFE_LIFE_H

#include <vector>
using namespace std;

class Life {
public:
   Life();
   ~Life();
   void set_dimensions();
   void initialize();
   void print();
   void update();
   void save_to_file();
   int get_maxrow() const { return maxrow; }
   int get_maxcol() const { return maxcol; }
private:
   int maxrow, maxcol;
   vector<vector<int>> grid;
   int neighbor_count(int row, int col);
};

#endif