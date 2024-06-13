#pragma once
#include <iostream>
#include <string>
#include "Card.hpp"

using namespace std;

namespace ariel{
    
    class Resource{

        private:
            int type;

        public:
            Resource(const int type) : type(type){}
            Resource() : type(-1){}

            int getType() const;

            void setType(const int& type);
            
            string getName() const;
    };
}
