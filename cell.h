#ifndef CELL_H
#define CELL_H
#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream>
#include <vector>
#include "subject.h"
#include "observer.h"
#include "info.h"

using std::vector;

class Cell : public Subject, public Observer {
    const size_t r, c;      // coordinates of cell
    int value = 0;
    vector<int> district;
    vector<int> options = {1,2,3,4,5,6,7,8,9};
    
    //State state;            // dead/alive

  public:
    bool set = false;
    Cell(size_t r, size_t c); // Cell is at row r and column c of the grid
    // Return a string consisting of "(r,c)" where r and c are the data fields.
    virtual std::string getName() override;
    void broadcastIfAlive();
    void notify( Subject & whoNotified ) override;
    void recalculate(); 
    // Observer calls this to get information about cell.
    virtual Info getInfo() const override;
    void setValue(int value);
    int getValue();
    void remove(int rem);
    void displayOptions();
    bool notSet();
    bool hasOption(int val);
    vector<int> getOptions();
};

#endif
