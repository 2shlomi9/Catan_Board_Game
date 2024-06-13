#include <iostream>
#include <string>
#include <list>
#include "Resource.hpp"

using namespace std;
using namespace ariel;


int Resource :: getType() const{
    return this->type;
}

string Resource :: getName() const{

    switch(this->type){

        case 0 :
            return "wood";
        case 1:
            return "brick";
        case 2:
            return "wool";
        case 3:
            return "oats";
        case 4:
            return "iron";
        case 5 :
            return "no resource";
        default:
            return "undefind";
    }
}

void Resource :: setType(const int& type){
    if(type < 1 || type > 5){
        return;
    }
    this->type = type;
}
