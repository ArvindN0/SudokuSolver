#include <string>
#include "grid.h"

using std::to_string;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

void Grid::printCellNeighbours() {
	for (auto a : theGrid) {
		for (auto b : a) {
			cout << b.getName() << ": " << b.getObserverNames() << endl;
		}
	}
}

void Grid::init() {
    int n = 9;
	theGrid.clear();
	for (int i = 0; i < n; i++) {
		vector<Cell> c1;
		for (int j = 0; j < n; j++) {
			c1.emplace_back(i, j);
		}
		theGrid.push_back(c1);
	}
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c < n; c++) {
                if (c!=b) { theGrid[a][b].attach(&theGrid[a][c]); }
                if (c!=a) { theGrid[a][b].attach(&theGrid[c][b]); }
            }
            int blockc = a/3;
            blockc *= 3;
            int blockr = b/3;
            blockr *= 3;
            int cbound = blockc + 3;
            int rbound = blockr + 3;
            for (int i = blockc; i < cbound; i++) {
                for (int j = blockr; j < rbound; j++) {
                    if (i != a && j != b) {
                        theGrid[i][j].attach(&theGrid[a][b]);
                    }
                }
            }
        }
    }
}

void Grid::turnOn( int r, int c, int value ) {
		int n = theGrid.size() - 1;
                if (r < 0 || r > n || c < 0 || c > n) {
			string error = "ERROR: coordinates (";
			error += to_string(r);
			error += ",";
			error += to_string(c);
			error += ") are not in the range 0 to ";
			error += to_string(n);
			throw std::invalid_argument(error);
		} else {
			theGrid[r][c].setValue(value);
            if (value != 0) { numSet++; }
		}
}

bool Grid::hasRowOption(int col, int row, int val) {
    bool print = false;
    //if ((col == 0) && (row == 0)) { print = true; }
    for (int i = 0; i < theGrid.size(); i++) {
        if (i != col) {
            if (theGrid[row][i].hasOption(val)) {
                if (print) {
                    cout << theGrid[row][i].getName() << " has value: " << val << endl;
                }
                return false;
            }
        }
    }
    return true;
}

bool Grid::hasColOption(int col, int row, int val) {
    bool print = false;
    //if ((col == 0) && (row == 0)) { print = true; }
    for (int i = 0; i < theGrid.size(); i++) {
        if (i != row) {
            if (theGrid[i][col].hasOption(val)) {
                if (print) {
                    cout << theGrid[i][col].getName() << " has value: " << val << endl;
                }
                return false;
            }
        }
    }
    return true;
}

bool Grid::hasSectionOption(int col, int row, int val) {
    bool print = false;
    //if ((col == 0) && (row == 0)) { print = true; }
    int blockc = col/3;
    blockc *= 3;
    int blockr = row/3;
    blockr *= 3;
    int cbound = blockc + 3;
    int rbound = blockr + 3;
    for (int i = blockc; i < cbound; i++) {
        for (int j = blockr; j < rbound; j++) {
            if (i != col || j != row) {
                if (theGrid[j][i].hasOption(val)) {
                    if (print) {
                    cout << theGrid[i][col].getName() << " has value: " << val << endl;
                }
                return false;
                }
            }
        }
    }
    return true;
}

int Grid::hasUniqueOption(Cell cell) {
    auto info = cell.getInfo();
    int a = info.col;
    int b = info.row;
    bool print = false;
    //if ((a == 0) && (b == 0)) { print = true; }
    if (print) cell.displayOptions();
    auto options = cell.getOptions();

    for (auto val : options) {
        if (options.size() == 1) {
            cout << cell.getName() << " has unique option: " << val << endl;
            return options[0];
        }
        if (hasColOption(a, b, val)) {
            cout << cell.getName() << " has unique column option: " << val << endl;
            return val;
        }
        if (hasRowOption(a, b, val)) {
            cout << cell.getName() << " has unique row option: " << val << endl;
            return val;
        }
        if (hasSectionOption(a, b, val)) {
            cout << cell.getName() << " has unique section option: " << val << endl;
            return val;
        }
    }
    return -1;
}

void Grid::tick() {
    int n = theGrid.size();
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
            //if (theGrid[i][j].notSet()) {
            if (theGrid[i][j].set) {
                //cout << "set: "<< theGrid[i][j].getName() << endl;
            } else {
                //cout << "unset: " << theGrid[i][j].getName() << endl;
                int val;
                val = hasUniqueOption(theGrid[i][j]);
                if (val != -1) {
                    theGrid[i][j].setValue(val);
                    numSet++;
                }
            }
		}
	}
}

std::ostream & operator<<( std::ostream & out, Grid & g ) {
    cout << "-------------------------" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            if (g.theGrid[i][j].getValue() == 0) {
                cout << "  ";
            } else {
                cout << g.theGrid[i][j].getValue() << " ";
            }
            if (j == 2 || j == 5 || j == 8) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i+1)%3 == 0) {
            cout << "-------------------------" << endl;
        }
    }
    return out; 
}
