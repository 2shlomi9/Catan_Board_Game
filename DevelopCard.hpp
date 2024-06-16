#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace ariel{
    class DevelopCard {
        private:
            int type;
        public:
            DevelopCard() : type(-1){} 
            DevelopCard(const int& type) : type(type){}
            int getType() const;

            void setType(const int& type);
            
            virtual string getName() const;
    };
}