#include <iostream>
#include <string>
#include <list>
#include "Resource.hpp"

using namespace std;
using namespace ariel;

// ------ getType function ------
/**
 * @brief This function returns the type of the resource.
 * @return The type of the resource.
 */
int Resource :: getType() const{
    return this->type;
}

// ------ getName function ------
/**
 * @brief This function returns the name of the resource as a string.
 * @return The name of the resource.
 */
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

// ------ setType function ------
/**
 * @brief This function sets the type of the resource.
 * @param type: The type to set for the resource.
 */
void Resource :: setType(const int& type){
    if(type < 0 || type > 5){
        return;
    }
    this->type = type;
}
