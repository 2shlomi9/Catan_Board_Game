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

        public:
            Catan() : isAlive(false){}
            bool addPlayer(Player player);
            void startGame();
            void setPlayersOrder();
            void addSettlment(int player, Settlment settlment);
            void addPath(int player ,Path p1);
            bool isAvaliableForPath(const int t1,const int t2) const;
            bool isAvaliableForSettlment(const int t1,const int t2,const int t3) const;
            bool compareThreeTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;
            bool compareTwoTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const;

    };
}