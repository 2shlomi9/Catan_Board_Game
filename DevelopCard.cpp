#include <iostream>
#include <string>
#include <list>
#include "DevelopCard.hpp"

using namespace std;
using namespace ariel;

// ------ getType function ------
/**
 * @brief This function returns the type of the development card.
 * @return The type of the development card.
 */
int DevelopCard :: getType() const{
    return this->type;
}

// ------ setType function ------
/**
 * @brief This function sets the type of the development card.
 * @param type: The type to set for the development card.
 */
void DevelopCard :: setType(const int& type){
    if(type < 1 || type > 5){
        return;
    }
    this->type = type;
}

// ------ getName function ------
/**
 * @brief This function returns the name of the development card as a string.
 * @return The name of the development card.
 */
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
