#include <iostream>
#include <string>
#include <list>
#include "Resource.hpp"

using namespace std;

namespace ariel{

    int Resource :: getType() const{
        return this->type;
    }

    string Resource :: getName() const{

        switch(this->type){
            case 0 :
                return "no resource";
            case 1 :
                return "wood";
            case 2:
                return "brick";
            case 3:
                return "wool";
            case 4:
                return "oats";
            case 5:
                return "iron";
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
}