#pragma once
#include <string>
#include <unordered_map>
#include "../model/Driver.hpp"

using namespace std;


// Encapsulation
class DriverService {
private:
    unordered_map<string, Driver> drivers;

public:
    Driver* registerDriver(const string& id, const string& name) {
        auto it = drivers.emplace(id, Driver(id, name)).first;
        return &it->second;
    }
};