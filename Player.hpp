#pragma once
#include <vector>
#include "Tool.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "DevelopCard.hpp"

using namespace std;
namespace ariel{

    class Player{
        private:

            string name;
            int points;
            int armySize;
            bool isLargestArmy;
            bool isLongestPath;
            vector<Path> paths;
            vector<Settlment> settlments;
            vector<Settlment> cities;
            vector<int> cards;
            vector<int> implementedCards;
            vector<int> resources;
            vector<Tile> tiles;
        public:
            Player(string name) : name(name), points(0), armySize(0) , isLargestArmy(false),  isLongestPath(false), resources(5), cards(5), implementedCards(2){}
            Player() : name("Player"), points(0), armySize(0) ,isLargestArmy(false),  isLongestPath(false), resources(5), cards(5), implementedCards(2){}
            void changeName(const string name);
            string getName() const;
            int rollDice() const;
            string toString() const;
            string getTools()const;
            int getArmySize() const;
            string viewSettlment();
            string viewDevelopmentCard();
            vector<int> getCards() const;
            int getPoints()const;
            void addResource(const int resource);
            void addDevelopmentCard(const int card);
            void setPath(Path path);
            void setSettlment(Settlment settlment);
            bool buyPath();
            bool buySettlment();
            bool buyCity();
            bool upgrateToCity(int settlment);    
            bool implementCard(int card);
            bool removeResource(const int resource);
            int getNumOfResource(const int resource);
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
