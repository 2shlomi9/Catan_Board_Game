#pragma once
#include <string>
#include <vector>
#include "Resource.hpp"

using namespace std;

namespace ariel{
    class Tile {
        private:

            int type; 
            int number;
            int isAvaliable; 
            vector<int> position;

        public:
            Tile(const int type,const int number, const vector<int> position) : type(type), number(number), isAvaliable(true), position(3){}
            Tile() : type(-1), number(-1), isAvaliable(true), position(3){}
            Tile(const int& x, const int& y, const int& z) : type(-1), number(-1), isAvaliable(true), position({x,y,z}){}
            

            void setPosition(const int& x, const int& y, const int& z);
            void setType(const int& type);
            void setNumber(const int& number);
            int getType() const;
            int getNumber() const;
            
            string getLandName() const;
            vector<int> getPosition() const;
            void turnOn();
            void turnOff();
            bool isContainsThief() const;
            Resource createResource() const;

            string toString() const;
    };
}

