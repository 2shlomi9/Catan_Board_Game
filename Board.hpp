#pragma once
#include <vector>
#include "Tile.hpp"

using namespace std;

namespace ariel{

    class Board {
        private:
            vector<Tile> tiles;

        public:
            Board(){}

            const std::vector<Tile>& getTiles() const;
            void initializeBoard();
            void clearBoard();
            void randomTypes();
            void randomNumbers();
            string toString() const;
            int getThiefPosition() const;
            void moveThief(const int position);
            bool isTwoTilesNeighbors(const int t1,const int t2) const;
            bool isThreeTilesNeighbors(const int t1,const int t2,const int t3) const;

    };
}


