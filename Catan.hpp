#pragma once
#include <vector>
#include "Player.hpp"
#include "Tool.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include "DevelopCard.hpp"

using namespace std;
namespace ariel{

    class Catan{
        private:
            vector<Player> players;
            Board board;
            bool isAlive;
            int longestPath;
            int playerLongestPath; 
            int playerLargestArmy;
            int largestArmy;
            vector<int> cards; 
            
        public:
            Catan() : isAlive(false),longestPath(0), playerLongestPath(-1), largestArmy(0), playerLargestArmy(-1), cards({14,5,2,2,2}){}
            bool addPlayer(Player player);
            void startGame();
            void thiefAction();
            void runGame();
            void removeHalfOfResources();
            bool trade(int give, int take, size_t player1, size_t player2);
            void sendTrade(size_t player);
            void setPlayersOrder();
            bool addSettlment(int player, Settlment settlment);
            bool addPath(int player ,Path p1);
            int addDevelopmentCard(int player);
            bool isAvaliableForPath(const int t1,const int t2) const;
            bool isAvaliableForSettlment(const int t1,const int t2,const int t3) const;
            bool isPathConnectToSettlment(Path path, Settlment Settlment) const;
            bool isPathConnectToPath(Path path1, Path path2) const;
            bool compareThreeTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;
            bool compareTwoTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;
            void playGame();
            bool buildPath(size_t player);
            void useDevelopmentCard(int player, int card);
            int findLongestPath(size_t player) const;
            void setLargestArmy();
            void getResourceFromPlayers(int player,int resource);
            void setPlayerLongestPath();
            int rollMenu(size_t player) const;
            size_t actionMenu(size_t player);
            string getAllTools()const;
            void getResource(const int diceNumber);

    };
}