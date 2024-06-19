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

            string name; // player name
            int points; // player points
            int armySize; // army size
            bool isLargestArmy; // true if the player hold the largest army
            bool isLongestPath; // true if the player hold the longest path
            vector<Path> paths; // list of player paths
            vector<Settlment> settlments; // list of player settlments
            vector<int> cards; // list of development cards
            vector<int> implementedCards; // list of used development cards (only knight and victory point)
            vector<int> resources; // lisr of player resources
        public:

        // ---------------- : Constructors : ----------------
            Player(string name) : name(name), points(0), armySize(0) , isLargestArmy(false),  isLongestPath(false), resources(5), cards(5), implementedCards(2){}
            Player() : name("Player"), points(0), armySize(0) ,isLargestArmy(false),  isLongestPath(false), resources(5), cards(5), implementedCards(2){}
        
        
        // ---------------- : Functions : ----------------
        
            // ------ Player functions ------
            int getPoints()const; // return player points
            int rollDice() const; // return the result of the dices
            int getArmySize() const; // return the army size
            string getName() const; // return player name  


            // ------ Settlement & Path & City functions ------
            void setPath(Path path); // add path to the paths list
            void setSettlment(Settlment settlment); // add settlment to settlments list

            vector<Path> getPaths() const; // return the paths list
            vector<Settlment> getSettlments() const; // return settlments list

            bool buyPath(); // buy path (false if there isn't enough resources)
            bool buySettlment(); // buy setllment (false if there isn't enough resources)
            bool buyCity(); // buy city (false if there isn't enough resources)

            bool upgrateToCity(int settlment); // upgrate settlment into a city  


            // ------ Resource functions ------
            void addResource(const int resource); // add resource to resources list
            bool removeResource(const int resource); // remove resource from resources list
            int getNumOfResource(const int resource); // return how many resouces have for this resource type


            // ------ Development Card functions ------
            vector<int> getCards() const; // return list of development cards
            void addDevelopmentCard(const int card); // add development card to the list
            bool implementCard(int card); // implement card from the list of development cards
            bool buyDevelopmentCard(); // buy development card(false if there isn't enogh resources)


            // ------ Longest path & Largest army functions ------
            void getLongestPath(); // change longestPath to true
            void getLargestArmy(); // change largestArmy to true

            void loseLongestPath(); // change longestPath to false
            void loseLargestArmy(); // change largestArmy to false
            
            
            // ------ toString functions ------
            string viewSettlment(); // return string of player settlment
            string viewDevelopmentCard(); // return string of player development cards
            string toString() const; // return string of all player data
            string getTools()const; // return string of all player tools
    };
}
