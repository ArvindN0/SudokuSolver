#include <iostream>
#include <string>
#include "grid.h"
#include "info.h"
using namespace std;

using std::cout;
using std::endl;

int main() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;
    g.init();
    try {
        while ( std::cin >> cmd ) {
            try {
                if ( cmd == "neighbours" ) {
                    g.printCellNeighbours();
                } else if ( cmd == "init" ) {
                    
                    int val;
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            std::cin >> val;
                            //cout << i << " " << j << endl;
                            g.turnOn(i,j,val);
                        }
                    }
                    //manual init strat at bottom
                } else if ( cmd == "step" ) {
                    g.tick();
                } else if ( cmd == "solve" ) {
                    while (g.numSet != 81) { g.tick(); }
                    std::cout << g;
                } else if ( cmd == "steps" ) {
                    int n;
                    std::cin >> n;
                    for ( int i = 0; i < n; ++i ) g.tick();
                } else if ( cmd == "print" ) {
                    std::cout << g;
                } // if
            } catch (std::invalid_argument & e) {
                std::cerr << e.what() << std::endl;
            }  // catch
        } // while
    } catch (ios::failure &) {}  // Any I/O failure quits
} // main

/*
try {
    int r, c, val;
    for ( std::cin >> c >> r >> val; ; std::cin >> c >> r >> val ) {
        if ( r == -1 && c == -1 ) break;
        g.turnOn(r,c,val);
        } // for
} catch (std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
} // catch
*/
