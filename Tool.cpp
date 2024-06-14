#include <iostream>
#include <string>
#include <vector>
#include "Tool.hpp"

using namespace std;
using namespace ariel;

const int Tool::getPoints(){
    return this->points;
}

vector<int> Tool::getTiles() const{
    return this->tiles;
}