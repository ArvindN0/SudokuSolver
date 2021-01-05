#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept> // defines std::invalid_argument
#include "cell.h"

class Observer;

class Grid {
    std::vector<std::vector<Cell>> theGrid;  // The actual grid.
    int hasUniqueOption(Cell cell);
    bool hasColOption(int col, int row, int val);
    bool hasRowOption(int col, int row, int val);
    bool hasSectionOption(int col, int row, int val);
  public:
    int numSet = 0;
    void printCellNeighbours();
    void init();       
    void turnOn( int r, int c, int value );  
    void tick();    
    friend std::ostream & operator<<( std::ostream & out, Grid & g );
    
};

// Uses the TextDisplay to output the grid information.
std::ostream & operator<<( std::ostream & out, Grid & g );

#endif
