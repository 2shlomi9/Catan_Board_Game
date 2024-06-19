#pragma once
#include <string>
#include <vector>
#include "Resource.hpp"

using namespace std;

namespace ariel{
    class Tile {
        private:

            int type; // tile type(land)
            int number; // tiles number(on the board)
            int isAvaliable; // true if the thief is in the tile
            vector<int> position; // tile position (three coordinates x,y,z)

        public:
        // ---------------- : Constructors : ----------------
            Tile(const int type,const int number, const vector<int> position) : type(type), number(number), isAvaliable(true), position(3){}
            Tile() : type(-1), number(-1), isAvaliable(true), position(3){}
            Tile(const int& x, const int& y, const int& z) : type(-1), number(-1), isAvaliable(true), position({x,y,z}){}
            
        // ---------------- : Functions : ----------------
            void setPosition(const int& x, const int& y, const int& z); // set tiles coordinates
            void setType(const int& type); // set tile type
            void setNumber(const int& number); // set tile number

            int getType() const; // return tile type
            int getNumber() const; // return tile number
            
            string getLandName() const; // return string of tile land name 
            vector<int> getPosition() const; // return tile coordinate
            void turnOn(); // switch isAvaliable to true if thief move to this tile
            void turnOff(); // switch isAvaliable to false if thief move from this tile
            bool isContainsThief() const; // return true if the thief is in this tile
            Resource createResource() const; // return resource of this type

            string toString() const; // return string of the tile (id (tile index on the board),land name,land number)
    };
}

