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

string Tool::toString() const{
    string str = "(";
    for (size_t i = 0; i < this->getTiles().size(); i++)
    {
        str += to_string(this->tiles[i]) + ", "; 
    }
    str.pop_back(); 
    str.pop_back(); 
    str += ")";
    return str;   
}

void Settlment::upgrateToCity(){
    if(this->isCity){
        try
        {
            throw std::invalid_argument("This settlment is already a city\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    this->isCity = true;
}
bool Settlment::getIsCity()const{
    return this->isCity;
}