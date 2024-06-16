#pragma once
#include <vector>
#include "Player.hpp"
#include "Tool.hpp"
#include "Board.hpp"
#include "Tile.hpp"

using namespace std;
namespace ariel{

    class Catan{
        private:
            vector<Player> players;
            Board board;
            bool isAlive;
            int longestPath;
            int playerLongestPath;  
            
        public:
            Catan() : isAlive(false),longestPath(0), playerLongestPath(-1){}
            bool addPlayer(Player player);
            void startGame();
            void setPlayersOrder();
            bool addSettlment(int player, Settlment settlment);
            bool addPath(int player ,Path p1);
            bool isAvaliableForPath(const int t1,const int t2) const;
            bool isAvaliableForSettlment(const int t1,const int t2,const int t3) const;
            bool isPathConnectToSettlment(Path path, Settlment Settlment) const;
            bool isPathConnectToPath(Path path1, Path path2) const;
            bool compareThreeTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;
            bool compareTwoTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;
            void playGame();
            int findLongestPath(size_t player) const;
            void setPlayerLongestPath();
            int rollMenu(size_t player) const;
            size_t actionMenu(size_t player);
            string getAllTools()const;
            void getResource(const int diceNumber);

    };
}