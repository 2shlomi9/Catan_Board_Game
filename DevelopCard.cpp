#include <iostream>
#include <string>
#include <list>
#include "DevelopCard.hpp"

using namespace std;
using namespace ariel;


int DevelopCard :: getType() const{
    return this->type;
}


void DevelopCard :: setType(const int& type){
    if(type < 1 || type > 5){
        return;
    }
    this->type = type;
}
string DevelopCard :: getName() const{

    switch(this->type){

        case 0 :
            return "knight";
        case 1:
            return "victory point";
        case 2:
            return "monopoly card";
        case 3:
            return "build path";
        case 4:
            return "year of plenty";
        default:
            return "undefind";
    }
}
