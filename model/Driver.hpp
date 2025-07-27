#pragma once
#include <string>

using namespace std;


// Encapsulation: Hides data members and exposes them through public methods.
class Driver {
private:
    string id;
    string name;

public:
    Driver(const string& id = "", const string& name = "") : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
};