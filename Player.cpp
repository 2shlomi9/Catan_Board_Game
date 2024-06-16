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
    this->points++;
    return true;
}
int Player::getPoints()const{
    return this->points;
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
    this->points++;
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
    return rand() % 11 + 2;
   
}

void Player::setPath(Path path){
    this->paths.push_back(path);
}
void Player::setSettlment(Settlment settlment){
    this->settlments.push_back(settlment);
    this->points++;
}

void Player::changeName(string name){
    this->name = name;
}
string Player::getName() const{
    return this->name;
}
void Player::addResource(const int resource){

    if(resource >= 0 && resource < 5){
        this->resources[static_cast<size_t>(resource)]++;
    }
}
bool Player::upgrateToCity(int settlment){
    if(this->settlments.size()-1 < settlment || settlment < 0){
        try
        {
            throw std::invalid_argument("Inviled argument\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;

    }
    if(this->settlments[static_cast<size_t>(settlment)].getIsCity()){
        try
        {
            throw std::invalid_argument("This settlment is already a city\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;
    }
    if(this->buyCity()){
        this->settlments[static_cast<size_t>(settlment)].upgrateToCity();
        return true;
    }
    return false;

}

void Player::getLargestArmy(){
    if(!this->isLargestArmy){
        this->isLargestArmy = true;
        this->points += 2;
    }
}
void Player::loseLargestArmy(){
    if(this->isLargestArmy){
        this->isLargestArmy = false;
        this->points -= 2;
    }
}
void Player::getLongestPath(){
    if(!this->isLongestPath){
        this->isLongestPath = true;
        this->points += 2;
    }
}
void Player::loseLongestPath(){
    if(this->isLongestPath){
        this->isLongestPath = false;
        this->points -= 2;
    }
}

vector<Path> Player::getPaths() const{
    return this->paths;
}
vector<Settlment> Player::getSettlments() const{
    return this->settlments;
}


string Player::toString() const{
    string str = this->getTools();
    str += "Resources :\n";
    for (size_t i = 0; i < this->resources.size(); i++)
    {
        Resource resource(i);
        str += resource.getName() + " : " + to_string(this->resources[i]) + "\n";
    }
    str += "\nPlayer points : " + to_string(this->points) + "\n";
    
    return str;
}
string Player::viewSettlment(){
    string str = "Your settelment:\n";
    int sum = 0;
    for (size_t i = 0; i < this->settlments.size(); i++)
    {   
        if(!this->settlments[i].getIsCity()){
            str += to_string(++sum) + ":" + this->settlments[i].toString() + "\n";
        }
    }
    return str;
}
string Player::getTools()const{
    string str = "Player " + this->name + " :\n";
    
    str += "\nSettlments :\n";
    int sum = 0;
    for (size_t i = 0; i < this->settlments.size(); i++)
    {   
        if(!this->settlments[i].getIsCity()){
            str += to_string(i+1) + ":" + this->settlments[i].toString() + "\n";
        }
    }
    str += "\nCities :\n";
    sum = 0;
    for (size_t i = 0; i < this->settlments.size(); i++)
    {
        if(this->settlments[i].getIsCity()){    
            str += to_string(++sum) + ":" + this->settlments[i].toString() + "\n";
        }
    }
    str += "\nPaths :\n";
    for (size_t i = 0; i < this->paths.size(); i++)
    {
        str += to_string(i+1) + ":" + this->paths[i].toString() + "\n";
    }
    if(this->isLongestPath){
        str += this->name + " has the longest path\n";
    }

    
    return str;
}