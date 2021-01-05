#ifndef _INFO_H
#define _INFO_H
#include <cstddef> // defines size_t i.e. an unsigned int

struct Info {
    size_t row, col;  
    int value;
    bool set;
};

#endif