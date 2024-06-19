#pragma once
#include <vector>
#include "Tile.hpp"

using namespace std;

namespace ariel{

    class Board {
        private:
            vector<Tile> tiles; // Tiles list

        public:
        // ---------------- : Constructors : ----------------
            Board(){}


        // ---------------- : Functions : ----------------


            // ------ Tiles functions ------
            const std::vector<Tile>& getTiles() const; // Get the tiles list
            
            bool isTwoTilesNeighbors(const int t1,const int t2) const; // get two indexs of tiles from tiles list and check if there connected 
            bool isThreeTilesNeighbors(const int t1,const int t2,const int t3) const; // get three indexs of tiles from tiles list and check if there connected
            
            void randomTypes(); // random ordering the tiles types in the board 
            void randomNumbers(); // random ordering the tiles numbers in the board 
            
            // ------ Thief functions ------
            int getThiefPosition() const; // return when the thief in the board(the index of the tile)
            bool moveThief(const int position); // move thief from one tile to another tile

            // ------ Board functions ------
            void initializeBoard(); // initialize the board with tiles
            void clearBoard(); // clear the board

            // ------ toString functions ------
            string toString() const; // return string of the board (print the tiles by order)

    };
}


