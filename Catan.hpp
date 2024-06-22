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
            vector<Player> players; // Players list
            Board board; // Board 
            bool isAlive; // Check if the game started
            int longestPath; // Size of the longest path
            int playerLongestPath; // The player with the longest path
            int playerLargestArmy; // Size of the largest army
            int largestArmy; // The player with the largest army
            vector<int> cards; // Development cards list
            
        public:

        // ---------------- : Constructors : ----------------
            Catan() : isAlive(false),longestPath(0), playerLongestPath(-1), largestArmy(0), playerLargestArmy(-1), cards({14,5,2,2,2}){}

        // ---------------- : Functions : ----------------


            // ------ Player functions ------
            bool addPlayer(Player player); // Add player to the game
            void setPlayersOrder(); // Create random order of player 


            // ------ Settlement & Path & City functions ------
            bool addPath(int player ,Path p1); // Player add path function
            bool addSettlment(int player, Settlment settlment); // Player add settlement function

            bool isAvaliableForPath(const int t1,const int t2) const; // Check if there is not path in this position
            bool isAvaliableForSettlment(const int t1,const int t2,const int t3) const; // // Check if there is not settlement in this position
            
            bool isPathConnectToPath(Path path1, Path path2) const; // Check if two paths connected
            bool isPathConnectToSettlment(Path path, Settlment Settlment) const; // Check if path connect to a settlement 

            bool compareTwoTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const; // Check if at least two tiles connected to other two tiles         
            bool compareThreeTiles(const int x1, const int x2, const int x3, const int y1, const int y2, const int y3) const; // Check if all the three tiles connected to other three tiles          

            bool buildPath(size_t player); // Player Build path on the board
            bool buildSettlment(size_t player); // Player Build settlment on the board
            void buildCity(size_t player); // Player buld city on the board


            // ------ Resource functions ------
            void getResourceFromPlayers(int player,int resource); // Get all the resource card from all players (Monopoly development card)
            void removeHalfOfResources(); // Get half of resources from all the players with more then 7 resources(Dices = 7)
            void getResource(const int diceNumber); // All players get resources from tiles they own with same number of the dices result

            // ------ Development Card functions ------
            int addDevelopmentCard(int player); // Add development card for player (player buy development card)
            void useDevelopmentCard(int player, int card); // Player use development card

            // ------ Longest path & Largest army functions ------
            int findLongestPath(size_t player) const; // Find the size of longest path of player  

            void setLongestPath(); // Set longest path, and set the player with the longest path 
            void setLargestArmy(); // Set largest army, and set the player with the largest army 


            // ------ Trade functions ------
            bool trade(int give, int take, size_t player1, size_t player2); // Player1 trade with player2
            void sendTrade(size_t player); // Send trade request


            // ------ Thief functions ------
            void thiefAction(); // Move thief to another tile and make tile unavalible


            // ----- Game & Board functions ------
            int rollMenu(size_t player) const; // Menu before rolling the dices for more options(view board, view player game data)
            size_t actionMenu(size_t player); // Menu after rolling the dices for player actions
            void setBoard(Board board);
            string getAllTools()const; // Return all the tools on the board

            void startGame(); // Start game (each player put two settlments and two paths);
            void playGame(); // After startGame function, run the game play
            void runGame(); // Run the game, call startGame function, after run gamePlay function
            
            

            
            


            
            
            
            

    };
}