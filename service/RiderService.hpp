#pragma once
#include <string>
#include <unordered_map>
#include "../model/Rider.hpp"

using namespace std;


// Encapsulation
class RiderService {
private:
    unordered_map<string, Rider> riders;

public:
    Rider* registerRider(const string& id, const string& name) {
        auto it = riders.emplace(id, Rider(id, name)).first;
        return &it->second;
    }
};