#include <iostream>
#include <string>
#include <vector>
#include "Tool.hpp"

using namespace std;
using namespace ariel;

// ------ getPoints function ------
/**
 * @brief This function returns the tool points.
 * @return The number of points the tool worth.
 */
const int Tool::getPoints(){
    return this->points;
}

// ------ getTiles function ------
/**
 * @brief This function returns the tiles of the tool.
 * @return list of tiles.
 */
vector<int> Tool::getTiles() const{
    return this->tiles;
}

// ------ toString function ------
/**
 * @brief This function returns a string representation of the tiles.
 * @return A string representing all the player's data.
 */
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

// ------ upgrateToCity function ------
/**
 * @brief This function change settlment into a city (flag is city true).
 */
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

// ------ getIsCity function ------
/**
 * @brief This function returns if a settlment is already a city.
 * @return return true if the settlment is a city.
 */
bool Settlment::getIsCity()const{
    return this->isCity;
}