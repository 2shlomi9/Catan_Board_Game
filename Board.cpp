#include <random>
#include <cstdlib>
#include "Board.hpp"

#define NUMBER_OF_TILES 37
#define NUMBER_OF_DESERTS 1
#define NUMBER_OF_FORESTS 4
#define NUMBER_OF_HILLS 3
#define NUMBER_OF_PASTURES 4
#define NUMBER_OF_AGRICULTURALS 4
#define NUMBER_OF_MOUNTAINS 3



using namespace std;
using namespace ariel;

// ---------------- : Tiles functions : ----------------

// ------ getTiles function ------
/**
 * @brief This function gets the list of tiles on the board.
 * @return A constant reference to the vector of tiles.
 */
const vector<Tile>& Board::getTiles() const {
    return tiles;
}

// ------ isTwoTilesNeighbors function ------
/**
 * @brief This function checks if two tiles are neighbors.
 * @param t1: The index of the first tile.
 * @param t2: The index of the second tile.
 * @return true if the tiles are neighbors, false otherwise.
 */
bool Board::isTwoTilesNeighbors(const int t1,const int t2) const{
    int x1,y1,z1;
    int x2,y2,z2;
    x1 = this->tiles[static_cast<size_t>(t1)].getPosition()[0];
    y1 = this->tiles[static_cast<size_t>(t1)].getPosition()[1];
    z1 = this->tiles[static_cast<size_t>(t1)].getPosition()[2];
    x2 = this->tiles[static_cast<size_t>(t2)].getPosition()[0];
    y2 = this->tiles[static_cast<size_t>(t2)].getPosition()[1];
    z2 = this->tiles[static_cast<size_t>(t2)].getPosition()[2];

    if(x1==x2){
        if(abs(y1-y2) == 1 && abs(z1-z2) == 1) return true;
    }
    if(y1==y2){
        if(abs(x1-x2) == 1 && abs(z1-z2) == 1) return true;
    }
    if(z1==z2){
        if(abs(x1-x2) == 1 && abs(y1-y2) == 1) return true;
    }
    return false;
}

// ------ isThreeTilesNeighbors function ------
/**
 * @brief This function checks if three tiles are neighbors.
 * @param t1: The index of the first tile.
 * @param t2: The index of the second tile.
 * @param t3: The index of the third tile.
 * @return true if the tiles are neighbors, false otherwise.
 */
bool Board::isThreeTilesNeighbors(const int t1,const int t2,const int t3) const{
    if(this->isTwoTilesNeighbors(t1,t2) && this->isTwoTilesNeighbors(t2,t3) && this->isTwoTilesNeighbors(t1,t3)){
        return true;
    }
    return false;
}
// ------ randomTypes function ------
/**
 * @brief This function randomly assigns types to the tiles on the board.
 */
void Board::randomTypes(){
    srand(time(nullptr));

    int rnd;
    int x, y, z;
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        x = this->tiles[static_cast<size_t>(i)].getPosition()[0];
        y = this->tiles[static_cast<size_t>(i)].getPosition()[1];
        z = this->tiles[static_cast<size_t>(i)].getPosition()[2];
        if (abs(x) == 3 || abs(y) == 3 || abs(z) == 3)
        {
            this->tiles[static_cast<size_t>(i)].setType(-2);
            this->tiles[static_cast<size_t>(i)].setNumber(-2);
        }
        
    }
    

    for(int i=0; i<NUMBER_OF_DESERTS; i++){
        rnd = rand()%NUMBER_OF_TILES; 

        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(5);
        this->tiles[static_cast<size_t>(rnd)].setNumber(0);
        this->tiles[static_cast<size_t>(rnd)].turnOff();
    }
    for(int i=0; i<NUMBER_OF_FORESTS; i++){
        rnd = rand()%NUMBER_OF_TILES; 
        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(0);
    }
    for(int i=0; i<NUMBER_OF_HILLS; i++){
        rnd = rand()%NUMBER_OF_TILES; 
        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(1);
    }
    for(int i=0; i<NUMBER_OF_PASTURES; i++){
        rnd = rand()%NUMBER_OF_TILES; 
        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(2);
    }
    for(int i=0; i<NUMBER_OF_AGRICULTURALS; i++){
        rnd = rand()%NUMBER_OF_TILES; 
        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(3);
    }
    for(int i=0; i<NUMBER_OF_MOUNTAINS; i++){
        rnd = rand()%NUMBER_OF_TILES; 
        while(this->tiles[static_cast<size_t>(rnd)].getType() != -1 || this->tiles[static_cast<size_t>(rnd)].getType() == -2){
            rnd = rand()%NUMBER_OF_TILES;
        }
        this->tiles[static_cast<size_t>(rnd)].setType(4);
    }
}

// ------ randomNumbers function ------
/**
 * @brief This function randomly assigns numbers to the tiles on the board.
 */
void Board::randomNumbers(){

    int rnd;
    srand(time(nullptr));
    for (int i = 2; i < 13; i++)
    {
        if(i != 7){
            rnd = rand()%NUMBER_OF_TILES; 
            while(this->tiles[static_cast<size_t>(rnd)].getNumber() != -1 || this->tiles[static_cast<size_t>(rnd)].getNumber() == -2){
                rnd = rand()%NUMBER_OF_TILES;
            }
            this->tiles[static_cast<size_t>(rnd)].setNumber(i);
        
            if(i != 2 && i != 12){
                rnd = rand()%NUMBER_OF_TILES; 
                while(this->tiles[static_cast<size_t>(rnd)].getNumber() != -1 || this->tiles[static_cast<size_t>(rnd)].getNumber() == -2){
                    rnd = rand()%NUMBER_OF_TILES;
                }
                this->tiles[static_cast<size_t>(rnd)].setNumber(i);
            }
        }
        
    }
}

// ---------------- : Thief functions : ----------------

// ------ getThiefPosition function ------
/**
 * @brief This function gets the position of the thief on the board.
 * @return The index of the tile containing the thief.
 */
int Board::getThiefPosition() const{
    for(size_t i=0; i<NUMBER_OF_TILES; i++){
        if(this-> tiles[i].isContainsThief()){
            return i;
        }
    }
    return NUMBER_OF_TILES;
}
// ------ moveThief function ------
/**
 * @brief This function moves the thief from one tile to another.
 * @param position: The index of the tile to move the thief to.
 * @return true if the thief is moved successfully, false otherwise.
 */
bool Board::moveThief(const int position){
    if (this->tiles[static_cast<size_t>(position)].getType() == -2) {
        try {
            throw std::invalid_argument("Can't move the thief to the sea!");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        return false; 
    }

    this->tiles[static_cast<size_t>(this->getThiefPosition())].turnOn();
    this->tiles[static_cast<size_t>(position)].turnOff();
    return true;
}

// ---------------- : Board functions : ----------------

// ------ initializeBoard function ------
/**
 * @brief This function initializes the board with tiles.
 */
void Board::initializeBoard() {
    this->clearBoard();
    for(int i=0; i<4; i++){
        this->tiles.push_back(Tile(i,-3,3-i)); 
    }  
    for(int i=-1; i<4; i++){
        this->tiles.push_back(Tile(i,-2,2-i));
    }  
    for(int i=-2; i<4; i++){
        this->tiles.push_back(Tile(i,-1,1-i));
    }  
    for(int i=-3; i<4; i++){
        this->tiles.push_back(Tile(i,0,-i));
    }  
    for(int i=-3; i<3; i++){
        this->tiles.push_back(Tile(i,1,-1-i));
    } 
    for(int i=-3; i<2; i++){
        this->tiles.push_back(Tile(i,2,-2-i));
    }  
    for(int i=-3; i<1; i++){
        this->tiles.push_back(Tile(i,3,-3-i));
    }  
    this->randomTypes();    
    this->randomNumbers();    

}

// ------ clearBoard function ------
/**
 * @brief This function clears the board.
 */
void Board::clearBoard(){
    this->tiles.clear();
}

// ------ toString function ------
/**
 * @brief This function returns a string representation of the board.
 * @return A string representing the board with tiles in order.
 */
string Board::toString()const{
    string str = "The board :\n";

    for(size_t i=0; i<NUMBER_OF_TILES; i++){
        str += "id: " + to_string(i) +" "+ this->tiles[i].toString() + " ";
        if(i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32){
            str += "\n";
        }
    }
    str += "\n";
    str += "thief location: "+ this->tiles[static_cast<size_t>(this->getThiefPosition())].toString()+"\n";
    return str;
    
}



       