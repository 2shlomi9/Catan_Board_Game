#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace ariel{
    class Card {
        private:
            int type;
        public:
            Card() : color(0){} 
            Card(const int& color) : color(color){}
    };
}