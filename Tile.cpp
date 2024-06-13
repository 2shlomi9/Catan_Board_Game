#include "Tile.hpp"

using namespace std;
using namespace ariel;

void Tile::setType(const int& type) {
    this->type = type;
}

void Tile::setNumber(const int& number) {
    this->number = number;
}

int Tile::getType() const {
    return type;
}

int Tile::getNumber() const {
    return number;
}

void Tile::turnOn() {
    this-> isAvaliable = true;
}

void Tile::turnOff() {
    this-> isAvaliable = false;
}
bool Tile::isContainsThief() const{
    return !this-> isAvaliable;
}

Resource Tile::createResource() const {

    if(!this->isAvaliable || this->type < 1 || this->type > 5) {
        return Resource();
    }
    return Resource(this->type);
}

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

vector<int> Tile::getPosition() const{
    return this->position;
}

void Tile::setPosition(const int& x, const int& y, const int& z){
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}
string Tile::toString()const{
    if(this->type==-2){
        return "(sea)";
    }
    return "(" + to_string(this->number) + ", " + this->getLandName() + ")"; 
}

