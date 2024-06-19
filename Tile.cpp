#include "Tile.hpp"

using namespace std;
using namespace ariel;

// ------ setType function ------
/**
 * @brief This function sets the type of the tile.
 * @param type: The type to set for the tile.
 */
void Tile::setType(const int& type) {
    this->type = type;
}

// ------ setNumber function ------
/**
 * @brief This function sets the number of the tile.
 * @param number: The number to set for the tile.
 */
void Tile::setNumber(const int& number) {
    this->number = number;
}

// ------ getType function ------
/**
 * @brief This function returns the type of the tile.
 * @return The type of the tile.
 */
int Tile::getType() const {
    return type;
}

// ------ getNumber function ------
/**
 * @brief This function returns the number of the tile.
 * @return The number of the tile.
 */
int Tile::getNumber() const {
    return number;
}

// ------ turnOn function ------
/**
 * @brief This function sets isAvaliable to true, indicating the thief is not on this tile.
 */
void Tile::turnOn() {
    this-> isAvaliable = true;
}

// ------ turnOff function ------
/**
 * @brief This function sets isAvaliable to false, indicating the thief is on this tile.
 */
void Tile::turnOff() {
    this-> isAvaliable = false;
}

// ------ isContainsThief function ------
/**
 * @brief This function checks if the thief is on this tile.
 * @return true if the thief is on this tile, false otherwise.
 */
bool Tile::isContainsThief() const{
    return !this-> isAvaliable;
}

// ------ createResource function ------
/**
 * @brief This function creates a resource based on the tile type.
 * @return A resource of the tile's type.
 */
Resource Tile::createResource() const {

    if(!this->isAvaliable || this->type < 1 || this->type > 5) {
        return Resource();
    }
    return Resource(this->type);
}

// ------ getLandName function ------
/**
 * @brief This function returns the name of the land type of the tile.
 * @return The name of the land type as a string.
 */
string Tile::getLandName() const{
    switch(this->type){
    case -2:
        return "Sea";
    case 0 :
        return "Forest";
    case 1:
        return "Hills";
    case 2:
        return "Pasture Land";
    case 3:
        return "Agricultural Land";
    case 4:
        return "Mountains";
    case 5:
        return "Desert";
    default:
        return "undefined";
    }
}

// ------ getPosition function ------
/**
 * @brief This function returns the position of the tile.
 * @return A vector containing the coordinates of the tile.
 */
vector<int> Tile::getPosition() const{
    return this->position;
}

// ------ setPosition function ------
/**
 * @brief This function sets the position of the tile.
 * @param x: The x-coordinate of the tile.
 * @param y: The y-coordinate of the tile.
 * @param z: The z-coordinate of the tile.
 */
void Tile::setPosition(const int& x, const int& y, const int& z){
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

// ------ toString function ------
/**
 * @brief This function returns a string representation of the tile.
 * @return A string representing the tile.
 */
string Tile::toString()const{
    if(this->type==-2){
        return "(sea)";
    }
    return "(" + to_string(this->number) + ", " + this->getLandName() + ")"; 
}

