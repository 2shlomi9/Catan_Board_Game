#include <random>
#include <cstdlib>
#include "Player.hpp"

using namespace std;
using namespace ariel;

bool Player::buildPath(){
    

}

int Player::rollDice() const{
    srand(time(nullptr));

    int diceA;
    int diceB;
    diceA = rand() % 6 + 1;
    diceB = rand() % 6 + 1;
    return(diceA+diceB);
}

void Player::changeName(string name){
    this->name = name;
}

void Player::addResource(const Resource resource){
    this->resources[resource.getType()]++;
}

