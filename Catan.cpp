#include <random>
#include <cstdlib>
#include "Catan.hpp"

using namespace std;
using namespace ariel;

bool Catan::addPlayer(Player player){
    
    if (this->isAlive)
    {
        try
        {
            throw std::invalid_argument("Game has started, can't add player\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;
    }
    
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
    
    this->players.push_back(player);
    cout << "player "+ player.getName() + " has joined to the game"<<endl;
    return true;
}



bool Catan::addPath(int player, Path path){
    vector<int> tiles = path.getTiles(); 
    if(!this->isAvaliableForPath(tiles[0], tiles[1])){
        return false;
    }
    this->players[static_cast<size_t>(player)].setPath(path);
    cout<<this->players[static_cast<size_t>(player)].getName() + " set path successfully !" <<endl;
    setPlayerLongestPath();
    return true;
}

bool Catan::addSettlment(int player, Settlment settlment){
    vector<int> tiles = settlment.getTiles(); 
    if(!this->isAvaliableForSettlment(tiles[0], tiles[1], tiles[2])){
        return false;
    }
    this->players[static_cast<size_t>(player)].setSettlment(settlment);
    cout<<this->players[static_cast<size_t>(player)].getName() + " set settlment successfully !" <<endl;
    return true;
}
void Catan::setPlayersOrder(){
    srand(time(nullptr));
    size_t size = this->players.size();
    vector<int>order(size,-1);
    vector<Player>playerOrder(size);
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

bool Catan::isPathConnectToSettlment(Path path, Settlment settlment) const{
    int t1 = settlment.getTiles()[0];
    int t2 = settlment.getTiles()[1];
    int t3 = settlment.getTiles()[2];
    int p1 = path.getTiles()[0];
    int p2 = path.getTiles()[1];
    return compareTwoTiles(t1,t2,t3,p1,p2,-1);
    
}
bool Catan::isPathConnectToPath(Path path1, Path path2) const{
    int t1 = path1.getTiles()[0];
    int t2 = path1.getTiles()[1];
    int p1 = path2.getTiles()[0];
    int p2 = path2.getTiles()[1];
    return compareTwoTiles(t1,t2,-1,p1,p2,-1);
    
}

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
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t1)].getType());
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t2)].getType());
        this->players[static_cast<size_t>(i)].addResource(this->board.getTiles()[static_cast<size_t>(t3)].getType());
        cout<<this->players[static_cast<size_t>(i)].toString();

        flag = false;
        isConnected = false;
    }
}
string Catan::getAllTools()const{
    string str = "Tools on the board:\n";
    for (size_t i = 0; i < this->players.size(); i++)
    {
        str+=this->players[i].getTools()+"\n";
    }
    return str;
}
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
void Catan::setPlayerLongestPath(){
    int max = this->longestPath;
    int index = this->playerLongestPath;
    for(size_t i=0; i<this->players.size(); i++){
        int longestPath = findLongestPath(i);
        if(longestPath > max && longestPath > 5){
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
            cout<<this->players[static_cast<size_t>(index)].getName() + " loose longest path !"<<endl;
        }
    }
    this->playerLongestPath = index;
}

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

size_t Catan::actionMenu(size_t player) {
    int choose = -1; 
    while(choose != 6){
        cout<<this->players[player].getName() + " turn: "<<endl;
        cout<< "Menu:" <<endl; 
        cout<<"View the board-press 1"<<endl;
        cout<<"View your game data-press 2"<<endl;
        cout<<"Build path-press 3"<<endl;
        cout<<"Build settlement-press 4"<<endl;
        cout<<"Build City-press 5"<<endl;
        cout<<"Buy Development card-press 6"<<endl;
        cout<<"Trade-press 7"<<endl;
        cout<<"Finish turn-press 8"<<endl;
        cin>>choose; 
        if(choose == 1){
            cout<<this->board.toString()<<endl;
            cout<<this->getAllTools();
        }
        else if(choose == 2){
            cout<<this->players[player].toString();
        }
        else if(choose== 3){
            cout<<"choose where to build the path:(choose 2 tiles)"<<endl;
            int p1, p2;
            cin>>p1>>p2;
            Path path(p1,p2);
            bool flag = false;
            for(size_t i = 0; i< this->players[player].getSettlments().size(); i++){
                if(isPathConnectToSettlment(path,this->players[player].getSettlments()[i])){
                    this->addPath(static_cast<int>(player),path);
                    flag = true;
                    break;
                }
            } 
            if(!flag){
                for(size_t i = 0; i< this->players[player].getPaths().size(); i++){
                    if(isPathConnectToPath(this->players[player].getPaths()[i],path)){
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

        }  
        else if(choose == 4){
            cout<<"choose where to build the settlement:(choose 3 tiles)"<<endl;
            int t1, t2,t3;
            cin>>t1 >>t2>>t3;
            Settlment settlment(t1,t2,t3);
            bool flag = false;
            for(size_t i = 0; i< this->players[player].getPaths().size(); i++){
                if(isPathConnectToSettlment(this->players[player].getPaths()[i],settlment)){
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
        }
        else if(choose == 5){
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
        else if(choose == 6){

        }
        else if(choose == 7){
            
        }
        else if(choose == 8){
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

void Catan::playGame(){
    size_t victory = 0;
    while(victory == 0){
        int rollDices;
        for (size_t i = 0; i < this->players.size(); i++)
        {
            rollDices = rollMenu(i);
            getResource(rollDices);
            victory = actionMenu(i);
            if(victory > 0) {
                break;
            }
            
        }
    }
    cout<<"Player "+this->players[victory-1].getName()+" has won !!!!!"<<endl;
}