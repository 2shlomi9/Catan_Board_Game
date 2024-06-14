#include <random>
#include <cstdlib>
#include "Player.hpp"

using namespace std;
using namespace ariel;

bool Player::buyPath(){
    // Wood-0, Brick-1 needed
    if(this->resources[0] < 1 || this->resources[1] < 1){
        try {
            throw std::invalid_argument("user : "+this->name +" doesn't have enough resources to buld a path\n" );
        } catch (const std::invalid_argument& e) {
            // Handle the error here, e.g., print a message or log the error
            std::cerr << "Error: " << e.what() << std::endl;
            // Optionally, you can set a flag or take other recovery actions
        }
        return false;
    }
    this->resources[0]--;
    this->resources[1]--;
    return true;
}
bool Player::buySettlment(){
    // Wood-0, Brick-1 , Wool-2, Oats-3 needed
    if(this->resources[0] < 1 || this->resources[1] < 1 || this->resources[2] < 1 || this->resources[3] < 1){
        try {
            throw std::invalid_argument("user : "+this->name +" doesn't have enough resources to buld a settlment\n" );
        } catch (const std::invalid_argument& e) {
            // Handle the error here, e.g., print a message or log the error
            std::cerr << "Error: " << e.what() << std::endl;
            // Optionally, you can set a flag or take other recovery actions
        }
        return false;
    }
    this->resources[0]--;
    this->resources[1]--;
    this->resources[2]--;
    this->resources[3]--;
    return true;
}
bool Player::buyCity(){
    // 2:Oats-3, 3:Iron-4 needed
    if(this->resources[3] < 2 || this->resources[4] < 3){
        try {
            throw std::invalid_argument("user : "+this->name +" doesn't have enough resources to buld a city\n" );
        } catch (const std::invalid_argument& e) {
            // Handle the error here, e.g., print a message or log the error
            std::cerr << "Error: " << e.what() << std::endl;
            // Optionally, you can set a flag or take other recovery actions
        }
        return false;
    }
    this->resources[3]-=2;
    this->resources[4]-=3;
    return true;
}
bool Player::buyDevelopmentCard(){
    // Wool-2, Oats-3, Iron-4 needed
    if(this->resources[2] < 1 || this->resources[3] < 1 || this->resources[4] < 1){
        try {
            throw std::invalid_argument("user : "+this->name +" doesn't have enough resources to buld a development card\n" );
        } catch (const std::invalid_argument& e) {
            // Handle the error here, e.g., print a message or log the error
            std::cerr << "Error: " << e.what() << std::endl;
            // Optionally, you can set a flag or take other recovery actions
        }
        return false;
    }
    this->resources[2]--;
    this->resources[3]--;
    this->resources[4]--;
    return true;
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

void Player::addResource(const int resource){
    if(resource < 0 || resource > 4){
        try {
            throw std::invalid_argument("Inviled Argument for resource type");
        } catch (const std::invalid_argument& e) {
            // Handle the error here, e.g., print a message or log the error
            std::cerr << "Error: " << e.what() << std::endl;
            // Optionally, you can set a flag or take other recovery actions
        }
        return;
    }
    this->resources[resource]++;
}

void Player::getLargestArmy(){
    if(!this->isLargestArmy){
        this->isLargestArmy == true;
        this->points += 2;
    }
}
void Player::loseLargestArmy(){
    if(this->isLargestArmy){
        this->isLargestArmy == false;
        this->points -= 2;
    }
}
void Player::getLongestPath(){
    if(!this->isLongestPath){
        this->isLongestPath == true;
        this->points += 2;
    }
}
void Player::loseLongestPath(){
    if(this->isLongestPath){
        this->isLongestPath == false;
        this->points -= 2;
    }
}

