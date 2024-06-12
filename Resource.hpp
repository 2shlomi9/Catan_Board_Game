#pragma once
#include <iostream>
#include <string>
#include "Card.hpp"

using namespace std;

namespace ariel{
    
    class Resource : public Card{

        private:
            int type;

        public:
            Resource(const int type) : Card(), type(type){}
            Resource() : Card(), type(-1){}

            int getType() const;

            void setType(const int& type);
            
            string getName() const;
    };
}
