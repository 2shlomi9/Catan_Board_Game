#include <random>
#include <cstdlib>
#include "Player.hpp"

using namespace std;
using namespace ariel;

// ---------------- : Player functions : ----------------

// ------ getPoints function ------
/**
 * @brief This function returns the player's points.
 * @return The number of points the player has.
 */
int Player::getPoints()const{
    return this->points;
}
// ------ rollDice function ------
/**
 * @brief This function simulates rolling a dice and returns the result.
 * @return The result of the dice roll.
 */
int Player::rollDice() const{
    srand(time(nullptr));
    return rand() % 11 + 2;
}

// ------ getArmySize function ------
/**
 * @brief This function returns the player's army size.
 * @return The size of the player's army.
 */
int Player::getArmySize() const{
    return this->armySize;
}
// ------ getName function ------
/**
 * @brief This function returns the player's name.
 * @return The name of the player.
 */
string Player::getName() const {
    return this->name;
}


// ---------------- : Settlement & Path & City functions : ----------------

// ------ setPath function ------
/**
 * @brief This function adds a path to the player's list of paths.
 * @param path: The path to be added.
 */
void Player::setPath(Path path){
    this->paths.push_back(path);
}

// ------ setSettlment function ------
/**
 * @brief This function adds a settlement to the player's list of settlements.
 * @param settlment: The settlement to be added.
 */
void Player::setSettlment(Settlment settlment){
    this->settlments.push_back(settlment);
    this->points++; // add one point for settlment
}

// ------ getPaths function ------
/**
 * @brief This function returns the player's list of paths.
 * @return A vector containing the player's paths.
 */
vector<Path> Player::getPaths() const{
    return this->paths;
}

// ------ getSettlments function ------
/**
 * @brief This function returns the player's list of settlements.
 * @return A vector containing the player's settlements.
 */
vector<Settlment> Player::getSettlments() const{
    return this->settlments;
}


// ------ buyPath function ------
/**
 * @brief This function allows the player to buy a path.
 * @return true if the player has enough resources to buy the path, false otherwise.
 */
bool Player::buyPath(){
    // 1:Wood(type = 0) , 1:Brick(type = 1) needed
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

// ------ buySettlment function ------
/**
 * @brief This function allows the player to buy a settlement.
 * @return true if the player has enough resources to buy the settlement, false otherwise.
 */
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

// ------ buyCity function ------
/**
 * @brief This function allows the player to buy a city.
 * @return true if the player has enough resources to buy the city, false otherwise.
 */
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
// ------ upgrateToCity function ------
/**
 * @brief This function upgrades a settlement to a city.
 * @param settlment: The index of the settlement to upgrade.
 * @return true if the upgrade is successful, false otherwise.
 */
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

// ---------------- : Resource functions : ----------------

// ------ addResource function ------
/**
 * @brief This function adds a resource to the player's list of resources.
 * @param resource: The index of the resource to add.
 */
void Player::addResource(const int resource){

    if(resource >= 0 && resource < 5){
        this->resources[static_cast<size_t>(resource)]++;
    }
}

// ------ getNumOfResource function ------
/**
 * @brief This function returns the number of a specific resource the player has.
 * @param resource: The index of the resource to check.
 * @return The number of the specified resource the player has.
 */
int Player::getNumOfResource(const int resource){
    
    if(resource >= 0 && resource < 5){
        return this->resources[static_cast<size_t>(resource)];
    }
    return 0;
}

// ------ removeResource function ------
/**
 * @brief This function removes a resource from the player's list of resources.
 * @param resource: The index of the resource to remove.
 * @return true if the resource is removed successfully, false otherwise.
 */
bool Player::removeResource(const int resource){
    
    if(resource >= 0 && resource < 5){
        if(this->resources[static_cast<size_t>(resource)]){
            this->resources[static_cast<size_t>(resource)]--;
            return true;
        }
    }
    return false;
}

// ---------------- : Development Card functions : ----------------

// ------ buyDevelopmentCard function ------
/**
 * @brief This function allows the player to buy a development card.
 * @return true if the player has enough resources to buy the development card, false otherwise.
 */
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

// ------ implementCard function ------
/**
 * @brief This function implements a development card.
 * @param card: The index of the card to implement.
 * @return true if the card is implemented successfully, false otherwise.
 */
bool Player::implementCard(int card){
    if(this->cards.size()-1 < card || card < 0){
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

    if(this->cards[static_cast<size_t>(card)]>0){
        this->cards[static_cast<size_t>(card)] --;
        if(card == 0){
            this->implementedCards[static_cast<size_t>(card)]++;
            this->armySize++;
        }
        else if(card == 1){
            this->implementedCards[static_cast<size_t>(card)]++;
            this->points ++;
        }
        return true;
    }
    try
    {
        throw std::invalid_argument("You haven't any "+DevelopCard(card).getName()+"\n");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;

}

// ------ getCards function ------
/**
 * @brief This function returns the player's list of development cards.
 * @return A vector containing the player's development cards.
 */
vector<int> Player::getCards() const{
    return this->cards;
}

/**
 * @brief This function adds a development card to the player's list of development cards.
 * @param card: The index of the card to add.
 */
void Player::addDevelopmentCard(const int card){

    if(card >= 0 && card < 5){
        this->cards[static_cast<size_t>(card)]++;
    }
}

// ---------------- : Longest path & Largest army functions : ----------------

// ------ getLongestPath function ------
/**
 * @brief This function sets the longestPath flag to true and increases the player's points.
 */
void Player::getLongestPath(){
    if(!this->isLongestPath){
        this->isLongestPath = true;
        this->points += 2;
    }
}

// ------ getLargestArmy function ------
/**
 * @brief This function sets the largestArmy flag to true and increases the player's points.
 */
void Player::getLargestArmy(){
    if(!this->isLargestArmy){
        this->isLargestArmy = true;
        this->points += 2;
    }
}

// ------ loseLongestPath function ------
/**
 * @brief This function sets the longestPath flag to false and decreases the player's points.
 */
void Player::loseLongestPath(){
    if(this->isLongestPath){
        this->isLongestPath = false;
        this->points -= 2;
    }
}

// ------ loseLargestArmy function ------
/**
 * @brief This function sets the largestArmy flag to false and decreases the player's points.
 */
void Player::loseLargestArmy(){
    if(this->isLargestArmy){
        this->isLargestArmy = false;
        this->points -= 2;
    }
}


// ---------------- : toString functions : ----------------

// ------ viewSettlment function ------
/**
 * @brief This function returns a string representation of the player's settlements.
 * @return A string representing the player's settlements.
 */
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

// ------ viewDevelopmentCard function ------
/**
 * @brief This function returns a string representation of the player's development cards.
 * @return A string representing the player's development cards.
 */
string Player::viewDevelopmentCard(){
    string str = "Your Development cards:\n";
    for (size_t i = 0; i < this->cards.size(); i++)
    {   
        str += to_string(i+1) + ". " + DevelopCard(i).getName() + ":" + to_string(this->cards[i]) +"\n";     
    }
    return str;
}

// ------ getTools function ------
/**
 * @brief This function returns a string representation of all the player's tools.
 * @return A string representing all the player's tools.
 */
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
    if(this->isLargestArmy){
        str += this->name + " has the largest army\n";
    }
    return str;
}

// ------ toString function ------
/**
 * @brief This function returns a string representation of all the player's data.
 * @return A string representing all the player's data.
 */
string Player::toString() const{
    string str = this->getTools();
    str += "\nResources :\n";
    for (size_t i = 0; i < this->resources.size(); i++)
    {
        Resource resource(i);
        str += resource.getName() + " : " + to_string(this->resources[i]) + "\n";
    }
    str += "\nDevelopment cards :\n";
    for (size_t i = 0; i < this->cards.size(); i++)
    {
        if(this->cards[i] > 0){
            DevelopCard card(i);
            str += card.getName() + " : " + to_string(this->cards[i]) + "\n";
        }
    }
    str += "\nImplemented development cards :\n";
    for (size_t i = 0; i < this->cards.size(); i++)
    {
        if(this->implementedCards[i] > 0){
            DevelopCard card(i);
            str += card.getName() + " : " + to_string(this->implementedCards[i]) + "\n";
        }
    }
    str += "\nPlayer points : " + to_string(this->points) + "\n";
    
    return str;
}


