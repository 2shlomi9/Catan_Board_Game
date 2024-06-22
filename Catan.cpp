#include <random>
#include <cstdlib>
#include "Catan.hpp"

using namespace std;
using namespace ariel;


// ------------------- : Player functions : -------------------

// ------ addPlayer function ------
/**
 * @brief This function adds a player to the game.
 * @param player: The player object to be added.
 * @return true if the player is added successfully, false otherwise.
*/

bool Catan::addPlayer(Player player){
    
    // Check if the game running
    if (this->isAlive) 
    {
        try
        {
            // If the game running throw exception (can't add a player when the game is already running)
            throw std::invalid_argument("Game has started, can't add player\n"); 
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;
    }
    
    // Check if the game is full (maximum 4 players in the game) 
    if (this->players.size() >= 4)
    {
        
        try
        {

            throw std::invalid_argument("Game is full, can't add player\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;
    }
    
    // Check if the player name avaliable
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if(this->players[i].getName() == player.getName()){
            try
            {
                throw std::invalid_argument("Player name already exist\n");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            return false;
        }
        
    }
    
    // Add player to players list
    this->players.push_back(player);
    cout << "player "+ player.getName() + " has joined to the game"<<endl;
    return true;
}

// ------ setPlayersOrder function ------
/**
 * @brief This function sets the order of the players in the game randomly.
*/
void Catan::setPlayersOrder(){
    srand(time(nullptr));
    size_t size = this->players.size();

    vector<int>order(size,-1); // Order list

    vector<Player>playerOrder(size); // New players list
    int rnd;
    for(size_t i = 0; i < size; i++){
        rnd = rand() % static_cast<int>(size); 
        while(order[static_cast<size_t>(rnd)] != -1){ 
            rnd = rand() % static_cast<int>(size);
        }
        order[static_cast<size_t>(rnd)] = i;
        playerOrder[static_cast<size_t>(rnd)] = this->players[i];
    }
    this->players = playerOrder;
    
}

// ------------------- : Settlement & Path & City functions : -------------------

// ------ addPath function ------
/**
 * @brief This function adds a path to the game board for a specific player.
 * @param player: The index of the player who wants to add the path.
 * @param path: The path object to be added.
 * @return true if the path is added successfully, false otherwise.
 */
bool Catan::addPath(int player, Path path){
    vector<int> tiles = path.getTiles(); 
    if(!this->isAvaliableForPath(tiles[0], tiles[1])){
        return false;
    }
    this->players[static_cast<size_t>(player)].setPath(path);
    cout<<this->players[static_cast<size_t>(player)].getName() + " set path successfully !" <<endl;
    setLongestPath();
    return true;
}

// ------ addSettlment function ------
/**
 * @brief This function adds a settlement to the game board for a specific player.
 * @param player: The index of the player who wants to add the settlement.
 * @param settlment: The settlement object to be added.
 * @return true if the settlement is added successfully, false otherwise.
 */
bool Catan::addSettlment(int player, Settlment settlment){
    vector<int> tiles = settlment.getTiles(); 
    if(!this->isAvaliableForSettlment(tiles[0], tiles[1], tiles[2])){
        return false;
    }
    this->players[static_cast<size_t>(player)].setSettlment(settlment);
    cout<<this->players[static_cast<size_t>(player)].getName() + " set settlment successfully !" <<endl;
    return true;
}

// ------ isAvaliableForPath function ------
/**
 * @brief This function checks if a path can be added at the specified position.
 * @param t1: The first tile.
 * @param t2: The second tile.
 * @return true if the path can be added, false otherwise.
 */
bool Catan::isAvaliableForPath(const int t1,const int t2) const{
    if(this->board.getTiles()[static_cast<size_t>(t1)].getType() == -2 && this->board.getTiles()[static_cast<size_t>(t2)].getType() == -2){
        try {
            throw std::invalid_argument("Cant add paths inside the sea\n");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return false;
    }
    if (!this->board.isTwoTilesNeighbors(t1,t2)) {
        try {
            throw std::invalid_argument("Tiles doesn't connected\n");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return false;
    }
    for(size_t i = 0; i<this->players.size(); i++){
        vector<Path> playerPaths = this->players[i].getPaths();
        for (size_t j = 0; j < playerPaths.size(); j++)
        {
            int tile1 = playerPaths[j].getTiles()[0];
            int tile2 = playerPaths[j].getTiles()[1];
            if(compareThreeTiles(-1 ,tile1 ,tile2, -1, t1, t2)){
                try {
                    throw std::invalid_argument("There is a path of player : "+this->players[i].getName()+" in this position \n");
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                return false;
            }
        }
    }
    
    return true;
}

// ------ isAvaliableForSettlment function ------
/**
 * @brief This function checks if a settlement can be added at the specified position.
 * @param t1: The first tile.
 * @param t2: The second tile.
 * @param t3: The third tile.
 * @return true if the settlement can be added, false otherwise.
 */
bool Catan::isAvaliableForSettlment(const int t1,const int t2,const int t3) const{
    if (!this->board.isThreeTilesNeighbors(t1,t2,t3)) {
        try {
            throw std::invalid_argument("Tiles doesn't connected\n");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return false;
    }
    for(size_t i = 0; i<this->players.size(); i++){
        vector<Settlment> playerSettlmens = this->players[i].getSettlments();
        for (size_t j = 0; j < playerSettlmens.size(); j++)
        {
            int tile1 = playerSettlmens[j].getTiles()[0];
            int tile2 = playerSettlmens[j].getTiles()[1];
            int tile3 = playerSettlmens[j].getTiles()[2];
            if(compareThreeTiles(tile1 ,tile2 ,tile3, t1, t2, t3)){
                try {
                    throw std::invalid_argument("There is a settlment of player : "+this->players[i].getName()+" in this position \n");
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                return false;
            }
            if(compareTwoTiles(tile1 ,tile2 ,tile3, t1, t2, t3)){
                try {
                    throw std::invalid_argument("There is a settlment of player : "+this->players[i].getName()+" close to this position by 1 path\n");
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                return false;
            }
        }

    }
    return true;
}
// ------ isPathConnectToPath function ------
/**
 * @brief This function checks if two paths are connected.
 * @param path1: The first path.
 * @param path2: The second path.
 * @return true if the paths are connected, false otherwise.
 */
bool Catan::isPathConnectToPath(Path path1, Path path2) const{
    int t1 = path1.getTiles()[0];
    int t2 = path1.getTiles()[1];
    int p1 = path2.getTiles()[0];
    int p2 = path2.getTiles()[1];
    return compareTwoTiles(t1,t2,-1,p1,p2,-1);
    
}
// ------ isPathConnectToSettlment function ------
/**
 * @brief This function checks if a path is connected to a settlement.
 * @param path: The path.
 * @param settlment: The settlement.
 * @return true if the path is connected to the settlement, false otherwise.
 */
bool Catan::isPathConnectToSettlment(Path path, Settlment settlment) const{
    int t1 = settlment.getTiles()[0];
    int t2 = settlment.getTiles()[1];
    int t3 = settlment.getTiles()[2];
    int p1 = path.getTiles()[0];
    int p2 = path.getTiles()[1];
    return compareTwoTiles(t1,t2,t3,p1,p2,-1);
    
}
// ------ compareTwoTiles function ------
/**
 * @brief This function checks if at least two tiles are connected to other two tiles.
 * @param x1: The first tile of the first set.
 * @param x2: The second tile of the first set.
 * @param x3: The third tile of the first set.
 * @param y1: The first tile of the second set.
 * @param y2: The second tile of the second set.
 * @param y3: The third tile of the second set.
 * @return true if at least two tiles are connected, false otherwise.
 */
bool Catan::compareTwoTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const{
    //comapre x1,x2
    if((x1 == y1 && x2 == y2) || (x2 == y1 && x1 == y2)){
        return true;
    }
    
    if((x1 == y1 && x2 == y3) || (x2 == y1 && x1 == y3)){
        return true;
    }
    
    if((x1 == y2 && x2 == y3) || (x2 == y2 && x1 == y3)){
        return true;
    }


    //comapre x1,x3

    if((x1 == y1 && x3 == y2) || (x3 == y1 && x1 == y2)){
        return true;
    }
    
    if((x1 == y1 && x3 == y3) || (x3 == y1 && x1 == y3)){
        return true;
    }
    
    if((x1 == y2  && x3 == y3) || (x3 == y2 && x1 == y3)){
        return true;
    }

    //comapre x2,x3

    if((x2 == y2 && x3 == y3) || (x2 == y3 && x3 == y2)){
        return true;
    }
    
    if((x2 == y1 && x3 == y3) || (x2 == y3 && x3 == y1)){
        return true;
    }
    
    if((x2 == y1 && x3 == y2) || (x2 == y2 && x3 == y1)){
        return true;
    }
    
    return false;
}


// ------ compareThreeTiles function ------
/**
 * @brief This function checks if all three tiles are connected to other three tiles.
 * @param x1: The first tile of the first set.
 * @param x2: The second tile of the first set.
 * @param x3: The third tile of the first set.
 * @param y1: The first tile of the second set.
 * @param y2: The second tile of the second set.
 * @param y3: The third tile of the second set.
 * @return true if all three tiles are connected, false otherwise.
 */
bool Catan::compareThreeTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const{
    if(x1 == y1){
        if((x2 == y2 && x3 == y3) || (x2 == y3 && x3 == y2)){
            return true;
        }
    }
    if(x1 == y2){
        if((x2 == y1 && x3 == y3) || (x2 == y3 && x3 == y1)){
            return true;
        }
    }
    if(x1 == y3){
        if((x2 == y1 && x3 == y2) || (x2 == y2 && x3 == y1)){
            return true;
        }
    }
    return false;
}

// ------ buildPath function ------
/**
 * @brief This function allows a player to build a path on the board.
 * @param player: The index of the player who wants to build the path.
 * @return true if the path is built successfully, false otherwise.
*/
bool Catan::buildPath(size_t player){
    cout<<"choose where to build the path:(choose 2 tiles)"<<endl;
    int p1, p2;
    cin>>p1>>p2;
    Path path(p1,p2);
    bool flag = false;
    for(size_t i = 0; i< this->players[player].getSettlments().size(); i++){
        if(isPathConnectToSettlment(path,this->players[player].getSettlments()[i]) && this->players[player].buyPath()){
            this->addPath(static_cast<int>(player),path);
            flag = true;
            break;
        }
    } 
    if(!flag){
        for(size_t i = 0; i< this->players[player].getPaths().size(); i++){
            if(isPathConnectToPath(this->players[player].getPaths()[i],path) && this->players[player].buyPath()){
                this->addPath(static_cast<int>(player),path);
                flag = true;
                break;
            }
        }
    }

    if(!flag){
        try
        {
            throw std::invalid_argument("There isn't a settlment or path to connect to this path\n");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }            
    }
    return flag;
}

// ------ buildSettlment function ------
/**
 * @brief This function allows a player to build a settlement on the board.
 * @param player: The index of the player who wants to build the settlement.
 * @return true if the settlement is built successfully, false otherwise.
 */
bool Catan::buildSettlment(size_t player){
    cout<<"choose where to build the settlement:(choose 3 tiles)"<<endl;
    int t1, t2,t3;
    cin>>t1 >>t2>>t3;
    Settlment settlment(t1,t2,t3);
    bool flag = false;
    for(size_t i = 0; i< this->players[player].getPaths().size(); i++){
        if(isPathConnectToSettlment(this->players[player].getPaths()[i],settlment) && this->players[player].buySettlment()){
            this->addSettlment(static_cast<int>(player),settlment);
            flag = true;
            break;
        }
    } 
    if(!flag){
        try
        {
            throw std::invalid_argument("There isn't a settlment or path to connect to this path\n");
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }  
    }
    return flag;
}

// ------ buildCity function ------
/**
 * @brief This function allows a player to build a city on the board.
 * @param player: The index of the player who wants to build the city.
 * @return true if the city is built successfully, false otherwise.
 */

void Catan::buildCity(size_t player){
    cout<<"Choose settlment you want upgrate to city (by index)"<<endl;
    cout<<this->players[player].viewSettlment()<<endl;
    int choose;
    int settlmentIndex = 0;
    cin>>choose;
    for (size_t i = 0; i < this->players[player].getSettlments().size(); i++)
    {
        settlmentIndex++;
        if(!this->players[player].getSettlments()[i].getIsCity()){
            if(--choose == 0){
                break;
            }
        }
    }
    
    this->players[player].upgrateToCity(settlmentIndex-1);
}


// ------------------- : Resource functions : -------------------

// ------ getResourceFromPlayers function ------
/**
 * @brief This function gets all the resource cards of a specific type from all players (Monopoly development card).
 * @param player: The index of the player who uses the Monopoly card.
 * @param resource: The type of resource to be taken from all players.
 */
void Catan::getResourceFromPlayers(int player,int resource){
    int sum = 0;
    int count = 0;
    
    for (size_t i = 0; i < players.size(); i++)
    {
        count = 0;
        if(i != static_cast<size_t>(player)){
            sum += this->players[static_cast<size_t>(i)].getNumOfResource(resource);
            count = this->players[static_cast<size_t>(i)].getNumOfResource(resource);
            while(count){
                this->players[static_cast<size_t>(i)].removeResource(resource);
                count--;
            }
            
        }
    }
    for(int i=0; i<sum; i++){
        this->players[static_cast<size_t>(player)].addResource(resource);
    }
    Resource r(resource);
    cout<<"You got " + to_string(sum)+ " "+r.getName()<<endl;
    
}

// ------ removeHalfOfResources function ------
/**
 * @brief This function removes half of the resources from all players with more than 7 resources (when the dice roll is 7).
 */
void Catan::removeHalfOfResources(){
    int sum = 0;
    int half = 0;
    for (size_t i = 0; i < this->players.size(); i++)
    {
        sum = 0;
        for(int j=0; j<5; j++){
            sum+=this->players[i].getNumOfResource(j);
        }
        if(sum>7){
            int choose;
            half = sum/2;
            
            choose = -1;
            while(half){   
                cout<<this->players[i].getName() +", choose "+to_string(half) +" resources to remove (by index):"<<endl;
                for(size_t j = 0; j < 5; j++){
                    cout<<to_string(j+1) +". "+Resource(static_cast<int>(j)).getName() +" ("+to_string(this->players[i].getNumOfResource(j))+")"<<endl;
                } 
                while(choose < 1 || choose > 5){
                    cin>>choose;
                }
                if(this->players[i].removeResource(choose-1)){
                    half--;
                    cout<<this->players[i].getName() +", remove "+Resource(choose-1).getName()<<endl;
                }
                choose = -1;
            }
            cout<<this->players[i].getName() +", Finish !! "<<endl;

        }
        
    }

}

// ------ getResource function ------
/**
 * @brief This function distributes resources to all players based on the dice number.
 * @param diceNumber: The number rolled on the dice.
 */
void Catan::getResource(const int diceNumber){

    for (size_t i = 0; i < this->players.size(); i++){
        for (size_t j = 0; j < this->players[i].getSettlments().size(); j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                size_t tileNumber = static_cast<size_t>(this->players[i].getSettlments()[j].getTiles()[k]);

                if(this->board.getTiles()[tileNumber].getNumber() == diceNumber){
                    this->players[i].addResource(this->board.getTiles()[tileNumber].createResource().getType());
                    if(this->players[i].getSettlments()[j].getIsCity()){
                        this->players[i].addResource(this->board.getTiles()[tileNumber].createResource().getType());
                    }
                }
            }
                
        }
                
    }
}


// ------------------- : Development Card functions : -------------------

// ------ addDevelopmentCard function ------
/**
 * @brief This function allows a player to buy a development card.
 * @param player: The index of the player who wants to buy the card.
 * @return The type of the development card purchased, or -1 if there are no more cards or the player cannot afford it.
 */
int Catan::addDevelopmentCard(int player){
    srand(time(nullptr));
    if(!this->players[static_cast<size_t>(player)].buyDevelopmentCard()){
        return -1;
    }
    int sum = 0;
    int rnd;
    for (size_t i = 0; i < this->cards.size(); i++)
    {
        sum+=this->cards[i];
    }
    if(sum == 0){
        cout<<"No more Develpoment cards"<<endl;
        return -1;
    }
    rnd = rand() % sum;
    int choose = -1;
    for (size_t i = 0; i < this->cards.size(); i++)
    {
        for (size_t j = 0; j <static_cast<size_t>(this->cards[i]); j++){
           
            if(rnd-- == 0){
                choose = i;
                break;
            }
        }
    }
    if(choose < this->cards.size() && choose>=0){
        this->cards[static_cast<size_t>(choose)]--;
        this->players[static_cast<size_t>(player)].addDevelopmentCard(choose);
        cout<<this->players[static_cast<size_t>(player)].getName() + " got a " + DevelopCard(choose).getName() <<endl;
    }
    return choose;

}

// ------ useDevelopmentCard function ------
/**
 * @brief This function allows a player to use a development card.
 * @param player: The index of the player who wants to use the card.
 * @param card: The index of the card to be used.
 */
void Catan::useDevelopmentCard(int player, int card){
    int choose;
    if(this->players[static_cast<size_t>(player)].implementCard(card)){
        switch (card)
        {
        case 0:
            cout<<"You got 1 more knight !!\n";
            this->thiefAction();
            this->setLargestArmy();
            break;
        case 1:
            cout<<"You got 1 victory point !!\n";
            break;
        case 2:
            cout<<"Monopoly card !! \n";
            cout<<"Choose resource (by index) :\n";
            for(size_t i = 0; i < 5; i++){
                cout<<to_string(i+1) +". "+Resource(i).getName()<<endl;
            }
            choose = -1;
                
            while(choose < 1 || choose > 5){
                cin>>choose;
            }
            getResourceFromPlayers(player,choose-1);

            break;
        case 3:
            
            cout<<"Build two paths: \n";
            while(!this->buildPath(static_cast<size_t>(player))){}
            cout<<"Build the second path: !!\n";
            while(!this->buildPath(static_cast<size_t>(player))){}
            break;
        case 4:
            cout<<"year of plenty card :\n";
            cout<<"Choose two resources (by index) :\n";
            for(size_t i = 0; i < 5; i++){
                cout<<to_string(i+1) +". "+Resource(i).getName()<<endl;
            }
            
            for (size_t i = 0; i < 2; i++)
            {
                choose = -1;
                if(i == 0){            // monopoly

                    cout<<"Choose the first resource" << endl;
                }
                else{
                    cout<<"Choose the second resource" << endl;
                }
                while(choose < 1 || choose > 5){
                    cin>>choose;
            
                }
                this->players[static_cast<size_t>(player)].addResource(choose-1);
                Resource(choose-1).getName();
                cout<<"You got 1 "+Resource(choose-1).getName()<< endl;
            }
            
            break;
        
        default:
            break;
        }
    }
}


// ------------------- : Longest path & Largest army functions : -------------------

// ------ findLongestPath function ------
/**
 * @brief This function finds the size of the longest path for a player.
 * @param player: The index of the player.
 * @return The size of the longest path.
 */
int Catan::findLongestPath(size_t player) const{

    if (this->players[player].getPaths().empty()) {
        return 0;
    }

    size_t n = this->players[player].getPaths().size();
    std::vector<int> dp(n, 1);  

    int maxLength = 1;

    // Build the dp array
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (isPathConnectToPath(this->players[player].getPaths()[j], this->players[player].getPaths()[i])) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLength = max(maxLength, dp[i]);
    }

    return maxLength;
}

// ------ setLongestPath function ------
/**
 * @brief This function sets the longest path and the player with the longest path.
 */
void Catan::setLongestPath(){
    int max = this->longestPath;
    int index = this->playerLongestPath;
    for(size_t i=0; i<this->players.size(); i++){
        int longestPath = findLongestPath(i);
        if(longestPath > max && longestPath > 4){
            max = longestPath;
            index = i;
        }
    }
    if(index != this->playerLongestPath && index != -1){
        if(this->playerLongestPath == -1){
            this->players[static_cast<size_t>(index)].getLongestPath();
            cout<<this->players[static_cast<size_t>(index)].getName() + " got longest path !"<<endl;
        }
        else{
            this->players[static_cast<size_t>(index)].getLongestPath();
            cout<<this->players[static_cast<size_t>(index)].getName() + " got longest path !"<<endl;
            this->players[static_cast<size_t>(this->playerLongestPath)].loseLongestPath();
            cout<<this->players[static_cast<size_t>(this->playerLongestPath)].getName() + " loose longest path !"<<endl;
        }
    }
    this->playerLongestPath = index;
    this->longestPath = max;
}

// ------ setLargestArmy function ------
/**
 * @brief This function sets the largest army and the player with the largest army.
 */
void Catan::setLargestArmy(){

    int max = this->largestArmy;
    int index = this->playerLargestArmy;
    for(size_t i=0; i<this->players.size(); i++){
        int largestArmy = this->players[i].getArmySize();
        if(largestArmy > max && largestArmy > 2){
            max = largestArmy;
            index = i;
        }
    }
    if(index != this->playerLargestArmy && index != -1){
        if(this->playerLargestArmy == -1){
            this->players[static_cast<size_t>(index)].getLargestArmy();
            cout<<this->players[static_cast<size_t>(index)].getName() + " got the largest army !"<<endl;
        }
        else{
            this->players[static_cast<size_t>(index)].getLargestArmy();
            cout<<this->players[static_cast<size_t>(index)].getName() + " got the largest army !"<<endl;
            this->players[static_cast<size_t>(this->playerLongestPath)].loseLargestArmy();
            cout<<this->players[static_cast<size_t>(this->playerLargestArmy)].getName() + " loose largest army  !"<<endl;
        }
    }
    this->playerLargestArmy = index;
    this->largestArmy = max;

}


// ------------------- : Trade functions : -------------------

// ------ trade function ------
/**
 * @brief This function allows two players to trade resources.
 * @param give: The resource to be given.
 * @param take: The resource to be taken.
 * @param player1: The index of the first player.
 * @param player2: The index of the second player.
 * @return true if the trade is successful, false otherwise.
 */
bool Catan::trade(int give, int take, size_t player1, size_t player2){
    if(!this->players[player1].getNumOfResource(give)){
        cout<<this->players[player1].getName()+" doesnt has "+Resource(give).getName()<<endl;
        return false;
    }
    if(!this->players[player2].getNumOfResource(take)){
        cout<<this->players[player2].getName()+" doesnt has "+Resource(take).getName()<<endl;
        return false;
    }
    this->players[player1].addResource(take);
    this->players[player2].addResource(give);
    this->players[player1].removeResource(give);
    this->players[player2].removeResource(take);
    cout<<"Trade succeed !"<<endl;
    return true;
}

// ------ sendTrade function ------
/**
 * @brief This function sends a trade request from one player to all other players.
 * @param player: The index of the player who wants to trade.
 */
void Catan::sendTrade(size_t player){
    int choose1 = -1;
    int choose2 = -1;

    cout<<this->players[player].getName() +", for this resources :"<<endl;
    for(size_t j = 0; j < 5; j++){
        cout<<to_string(j+1) +". "+Resource(static_cast<int>(j)).getName() +" ("+to_string(this->players[player].getNumOfResource(j))+")"<<endl;
    } 
    cout<<"Choose the resource you want to give :" << endl;
    while(choose1 < 1 || choose1 > 5){
        cin>>choose1;
        if(!this->players[player].getNumOfResource(choose1-1)){
            cout<<this->players[player].getName()+" doesnt has "+Resource(choose1-1).getName()<<endl;
            return;
        }
    }
    

    cout<<"Choose the resource you want to take :" << endl;
    while(choose2 < 1 || choose2 > 5){
    cin>>choose2;
    }
    bool flag = false;
    
    for (size_t i = 0; i < this->players.size(); i++)
    {
        char choose = 'N';
        if(i!=player){
            cout<<this->players[i].getName()+", "+this->players[player].getName()+" want to trade :";
            cout<<" give - "+Resource(static_cast<int>(choose2-1)).getName() +", take - "+Resource(static_cast<int>(choose1-1)).getName()<<endl;
            cout<<"Accept ? press Y\nIgonre ? any input"<<endl;
            cin>>choose;
            if (choose == 'Y')
            {
                cout<<this->players[i].getName() +", for this resources :"<<endl;
                for(size_t j = 0; j < 5; j++){
                    cout<<to_string(j+1) +". "+Resource(static_cast<int>(j)).getName() +" ("+to_string(this->players[i].getNumOfResource(j))+")"<<endl;
                } 
                if(this->trade(choose1-1, choose2-1, player, i)){
                    flag = true;
                    break;
                }
            }
            
        } 
    }
    if(!flag){
        cout<<"Trade unaccepted"<<endl;
    }
}

// ------------------- : Thief functions : -------------------

// ------ thiefAction function ------
/**
 * @brief This function moves the thief to another tile and makes the tile unavailable.
 */
void Catan::thiefAction(){
    cout<<"Choose tile (by index) for moving the thief"<<endl;
    int choose = -1; 
    while(choose < 0||choose  > 36){
        cin>>choose;
        if(choose < 0||choose  > 36){
            cout<<"Choose tile (by index) for moving the thief"<<endl;
        }
        else if(this->board.moveThief(choose)){
            break;
        }
        choose = -1;
    }
    
}


// ------------------- : Game & Board functions : -------------------

// ------ getAllTools function ------
/**
 * @brief This function returns all the tools on the board.
 * @return A string representing all the tools on the board.
 */
string Catan::getAllTools()const{
    string str = "Tools on the board:\n";
    for (size_t i = 0; i < this->players.size(); i++)
    {
        str+=this->players[i].getTools()+"\n";
    }
    return str;
}

// ------ rollMenu function ------
/**
 * @brief This function displays the menu before rolling the dice.
 * @param player: The index of the player.
 * @return The result of the dice roll.
 */
int Catan::rollMenu(size_t player) const{
    
    int choose = -1;
    int dice;
    
    
    while(1){
        cout<<this->players[player].getName() + " turn: "<<endl;
        cout<< "Menu:" <<endl; 
        cout<<"View the board-press 1"<<endl;
        cout<<"View your game data-press 2"<<endl;
        cout<<"Roll Dices-press 3"<<endl;
        cin>>choose;
        switch (choose)
        {

        case 1:
            cout<<this->board.toString()<<endl;
            cout<<this->getAllTools();
            break;
        case 2 :
            cout<<this->players[player].toString();
            break;
        case 3:
            dice = this->players[player].rollDice();
            cout<<"Dices result: "+to_string(dice)<<endl;
            return dice;         
        default:
            cout<<"press number between 1 to 3"<<endl;
            break;
        }
    }
    return -1;

}

// ------ actionMenu function ------
/**
 * @brief This function displays the menu after rolling the dice for player actions.
 * @param player: The index of the player.
 * @return 0 if the turn ends, or the player's index if they win.
 */
size_t Catan::actionMenu(size_t player) {
    int choose = -1; 
    while(choose != 9){
        cout<<this->players[player].getName() + " turn: "<<endl;
        cout<< "Menu:" <<endl; 
        cout<<"View the board-press 1"<<endl;
        cout<<"View your game data-press 2"<<endl;
        cout<<"Build path-press 3"<<endl;
        cout<<"Build settlement-press 4"<<endl;
        cout<<"Build City-press 5"<<endl;
        cout<<"Buy Development card-press 6"<<endl;
        cout<<"Use Development card-press 7"<<endl;
        cout<<"Trade-press 8"<<endl;
        cout<<"Finish turn-press 9"<<endl;
        cin>>choose; 
        if(choose == 1){
            cout<<this->board.toString()<<endl;
            cout<<this->getAllTools();
        }
        else if(choose == 2){
            cout<<this->players[player].toString();
        }
        else if(choose== 3){
            this->buildPath(player);

        }  
        else if(choose == 4){
            this->buildSettlment(player);
        }
        else if(choose == 5){
            this->buildCity(player);
        }
        else if(choose == 6){
            this->addDevelopmentCard(player);
        }
        else if(choose == 7){
            cout<<"Choose development card you want to use (by index)"<<endl;
            cout<<this->players[player].viewDevelopmentCard()<<endl;
            int choose;
            cin>>choose;
            this->useDevelopmentCard(player, choose-1);
    
        }
        else if(choose == 8){
            this->sendTrade(player);
        }
        else if(choose == 9){
            return 0;
        }
        else{
            cout<<"Choose number between 1 to 6 !"<<endl;
        }
        //player victory
        if(this->players[player].getPoints()>=10){
            return player+1; 
        }
    }
    return 0;

}
// ------ setBoard function ------
/**
 * @brief This function set initializing the board(Use for test).
 */
void Catan::setBoard(Board board){
    this->board = board;
}

// ------ startGame function ------
/**
 * @brief This function starts the game by initializing the board and allowing each player to place two settlements and two paths.
 */
void Catan::startGame(){
    cout<<"Game has started !"<<endl;
    this->isAlive = true;

    setPlayersOrder();
    cout<<"\nGame players order :"<<endl;
    for(size_t i =0; i<this->players.size();i++){
        cout<<this->players[i].getName()<<endl;
    }
    char accpetBoard = 'N';
    cout<<"\nRandoming the board game"<< endl;
    this->board.initializeBoard();
    cout<<this->board.toString();


    cout<<"\nAccept the board ? (Y/N)"<< endl;
    cin >> accpetBoard ;

    while(accpetBoard != 'Y'){
        cout<<"\nRandoming the board game"<<endl;
        this->board.initializeBoard();
        cout<<this->board.toString();
        cout<<"\nAccept the board ? (Y/N)"<<endl;
        cin >> accpetBoard ;
    }

    int t1, t2, t3;
    int p1, p2;
    bool flag = false;
    bool isConnected = false;
    
    for(int i = 0; i<this->players.size(); i++){
        while(!flag){
            cout<<"Player "+this->players[static_cast<size_t>(i)].getName() + ": locate the first settlment (choose 3 tiles by id)"<<endl;
            cin>>t1>>t2>>t3;
            Settlment settlment(t1,t2,t3);
            flag = this->addSettlment(i,settlment);
        }
        flag = false;
        while(!flag || !isConnected){
            cout<<"Player "+this->players[static_cast<size_t>(i)].getName() + ": locate the first path (choose 2 tiles by id)"<<endl;
            cin>>p1>>p2;
            Path path(p1,p2);
            Settlment settlment(t1,t2,t3);
            isConnected = this->isPathConnectToSettlment(path,settlment);
            if(isConnected){
                flag = this->addPath(i,path);
            }
            else{
                try
                {
                    throw std::invalid_argument("There isn't a settlment to connect to this path\n");
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        }
        flag = false;
        isConnected = false;
    }
    for(int i = this->players.size()-1; i >= 0; i--){
        while(!flag){
            cout<<"Player "+this->players[static_cast<size_t>(i)].getName() + ": locate the second settlment (choose 3 tiles by id)"<<endl;
            cin>>t1>>t2>>t3;
            Settlment settlment(t1,t2,t3);
            flag = this->addSettlment(i,settlment);
        }
        while(!flag || !isConnected){
            cout<<"Player "+this->players[static_cast<size_t>(i)].getName() + ": locate the second path (choose 2 tiles by id)"<<endl;
            cin>>p1>>p2;
            Path path(p1,p2);
            Settlment settlment(t1,t2,t3);
            isConnected = this->isPathConnectToSettlment(path,settlment);
            if(isConnected){
                flag = this->addPath(i,path);
            }
            else{
                try
                {
                    throw std::invalid_argument("There isn't a settlment to connect to this path\n");
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        }
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t1)].getType());
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t2)].getType());
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t3)].getType());
        cout<<this->players[static_cast<size_t>(i)].toString();

        flag = false;
        isConnected = false;
    }
}


// ------ playGame function ------
/**
 * @brief This function runs the gameplay after the game has started.
 */
void Catan::playGame(){
    size_t victory = 0;
    while(victory == 0){
        int rollDices;
        for (size_t i = 0; i < this->players.size(); i++)
        {
            rollDices = rollMenu(i);
            
            if(rollDices == 7){
                this->thiefAction();
                this->removeHalfOfResources();
            }
            this->getResource(rollDices);
            victory = this->actionMenu(i);
            if(victory > 0) {
                break;
            }
            
        }
    }
    cout<<"Player "+this->players[victory-1].getName()+" has won !!!!!"<<endl;
}

// ------ runGame function ------
/**
 * @brief This function runs the game by calling the startGame function and then the playGame function.
 */
void Catan::runGame(){

    this->startGame();
    this->playGame();
}