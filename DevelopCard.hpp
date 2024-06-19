#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace ariel{
    class DevelopCard {
        private:
            int type; // type of the card
        public:
        // ---------------- : Constructors : ----------------
            DevelopCard() : type(-1){} 
            DevelopCard(const int& type) : type(type){}
        // ---------------- : Functions : ----------------
            
            int getType() const; // get type of the card

            void setType(const int& type); // set type for the card
            
            virtual string getName() const; // return the name of the card(string)
    };
}