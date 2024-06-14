#pragma once
#include <vector>
#include "Tool.hpp"
#include "Resource.hpp"
#include "Tile.hpp"

using namespace std;
using namespace ariel;
class Player{
    private:

        string name;
        int points;
        bool isLargestArmy;
        bool isLongestPath;
        vector<Tool> tools;
        vector<Card> card;
        vector<int> resources;
        vector<Tile> tiles;
    public:
        Player(string name) : name(name), points(0), isLargestArmy(false),  isLongestPath(false), resources(5){}
        Player() : name("Player"), points(0), isLargestArmy(false),  isLongestPath(false){}
        void changeName(const string name);
        int rollDice() const;
        void addResource(const int resource);
        bool buyPath();
        bool buySettlment();
        bool buyCity();
        bool buyDevelopmentCard();
        void getLargestArmy();
        void loseLargestArmy();
        void getLongestPath();
        void loseLongestPath();
        // bool trade(vector<size_t> request, vector<size_t> receive);
            
};
