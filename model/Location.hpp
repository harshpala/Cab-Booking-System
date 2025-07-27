#pragma once
#include <iostream>
#include <cmath>
#include <string>

using namespace std;


// Encapsulation: Bundles data (x, y) with methods that operate on it.
class Location {
private:
    double x;
    double y;

public:
    Location(double x = 0, double y = 0) : x(x), y(y) {}

    double distanceTo(const Location& other) const {
        double dx = this->x - other.x;
        double dy = this->y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    string toString() const {
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }
};

inline ostream& operator<<(ostream& os, const Location& loc) {
    os << loc.toString();
    return os;
}