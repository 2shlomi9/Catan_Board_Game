#pragma once
#include <vector>
#include "Tool.hpp"
#include "Resource.hpp"
#include "Tile.hpp"

using namespace std;
namespace ariel{

    class Player{
        private:

            string name;
            int points;
            bool isLargestArmy;
            bool isLongestPath;
            vector<Path> paths;
            vector<Settlment> settlments;
            vector<Settlment> cities;
            vector<Card> card;
            vector<int> resources;
            vector<Tile> tiles;
        public:
            Player(string name) : name(name), points(0), isLargestArmy(false),  isLongestPath(false), resources(5){}
            Player() : name("Player"), points(0), isLargestArmy(false),  isLongestPath(false){}
            void changeName(const string name);
            string getName() const;
            int rollDice() const;
            string toString() const;
            string getTools()const;
            string viewSettlment();
            int getPoints()const;
            void addResource(const int resource);
            void setPath(Path path);
            void setSettlment(Settlment settlment);
            bool buyPath();
            bool buySettlment();
            bool buyCity();
            bool upgrateToCity(int settlment);    
            
            bool buyDevelopmentCard();
            void getLargestArmy();
            void loseLargestArmy();
            void getLongestPath();
            void loseLongestPath();
            vector<Path> getPaths() const;
            vector<Settlment> getSettlments() const;
            // bool trade(vector<size_t> request, vector<size_t> receive);
                
    };
}
