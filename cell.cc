#include <string>
#include "cell.h"
#include "info.h"

using std::endl;
using std::cout;
using std::string;
using std::to_string;

Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

void Cell::setValue(int _value) {
    //cout << "setting " << this->getName() << " value to " << _value << endl;
    value = _value;
    if (value != 0) {
        set = true;
        options = {_value};
        notifyObservers();
    }
}

string Cell::getName() {
	string coords = "(";
	coords = coords + to_string(c) + "," + to_string(r) + ")";
	return coords;
}

void Cell::broadcastIfAlive() {
    if (set) { notifyObservers(); }
}

void Cell::remove(int rem) {
    for (int i = 0; i < options.size(); i++) {
        if (options[i] == rem) {
            options.erase(options.begin() + i);
        }
    }
}

void Cell::notify( Subject & whoNotified ) {
    Info a = whoNotified.getInfo();
    if (a.set) { remove(a.value); }
}

void Cell::displayOptions() {
    cout << this->getName() << ": ";
    for (auto a : options) { cout << a << " " ; }
    cout << endl;
}

void Cell::recalculate() {
    if (options.size() == 1) { setValue(options[0]); }

}

Info Cell::getInfo() const {
	Info a{r, c, value, set};
	return a;
}

int Cell::getValue() { return value; }

bool Cell::notSet() { return !set; }

vector<int> Cell::getOptions() {
    return options;
}

bool Cell::hasOption(int val) {
    for (auto a : options) {
        if (a == val) {
            return true;
        }
    }
    return false;
}

