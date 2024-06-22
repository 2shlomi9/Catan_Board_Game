/*
Author: Shlomi Zecharia
ID: 315141242
Email: 2shlomiariel9@gmail.com
*/

#include "doctest.h"
#include "Catan.hpp"
#include "Player.hpp"
#include "Tool.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include "DevelopCard.hpp"

using namespace std;
using namespace ariel;



TEST_CASE("Test Player class")
{
    SUBCASE("Test setPath & getPath") {
        Player player1("Alice");
        Path path1(1,2);
        Path path2(4,5);

        player1.setPath(path1);
        player1.setPath(path2);

        vector<Path> paths = player1.getPaths();
        int x1 = paths[0].getTiles()[0];
        int y1 = paths[0].getTiles()[1];
        int x2 = paths[1].getTiles()[0];
        int y2 = paths[1].getTiles()[1];
        CHECK(x1 == 1);
        CHECK(y1 == 2);
        CHECK(x2 == 4);
        CHECK(y2 == 5);

    }
    SUBCASE("Test setSettlment & getSettlment") {
        Player player1("Alice");
        Settlment settlment1(1,2,3);
        Settlment settlment2(4,5,6);

        player1.setSettlment(settlment1);
        player1.setSettlment(settlment2);

        vector<Settlment> settlments = player1.getSettlments();
        int x1 = settlments[0].getTiles()[0];
        int y1 = settlments[0].getTiles()[1];
        int z1 = settlments[0].getTiles()[2];

        int x2 = settlments[1].getTiles()[0];
        int y2 = settlments[1].getTiles()[1];
        int z2 = settlments[1].getTiles()[2];
        CHECK(x1 == 1);
        CHECK(y1 == 2);
        CHECK(z1 == 3);

        CHECK(x2 == 4);
        CHECK(y2 == 5);
        CHECK(z2 == 6);

    }
    SUBCASE("Test buyPath & buySettlment & buyCity") {
        Player player1("Alice");
        // buyPath function :
        player1.addResource(0);
        player1.addResource(1);
        bool flag = player1.buyPath(); 
        CHECK(flag == true);
        flag = player1.buyPath(); // there is not enough resources
        CHECK(flag == false);
        

        // buySettlment function :
        player1.addResource(0);
        player1.addResource(1);
        player1.addResource(2);
        player1.addResource(3);
        flag = player1.buySettlment();
        CHECK(flag == true);
        flag = player1.buySettlment(); // there is not enough resources
        CHECK(flag == false);

        // buyCity function :
        player1.addResource(3);
        player1.addResource(3);
        player1.addResource(4);
        player1.addResource(4);
        player1.addResource(4);
        flag = player1.buyCity();
        CHECK(flag == true);
        flag = player1.buyCity(); // there is not enough resources
        CHECK(flag == false);
    }
    SUBCASE("Test UpgrateToCity") {
        Player player1("Alice");
        Settlment settlment1(1,2,3);
        Settlment settlment2(4,5,6);
        player1.setSettlment(settlment1);
        player1.setSettlment(settlment2);
        player1.addResource(3);
        player1.addResource(3);
        player1.addResource(4);
        player1.addResource(4);
        player1.addResource(4);
        
        bool flag = player1.upgrateToCity(0); // upgrate settlment 1 to city

        CHECK(flag == true);

        player1.addResource(3);
        player1.addResource(3);
        player1.addResource(4);
        player1.addResource(4);
        player1.addResource(4);
        flag = player1.upgrateToCity(0); // false, this settlment is already a city

        CHECK(flag == false);

        player1.removeResource(3);
        flag = player1.upgrateToCity(0); // false, there is not enough resources

        CHECK(flag == false);

    }
    SUBCASE("Test addResource & removeResource & getNumOfResource"){
        Player player1("Alice");
        player1.addResource(1);
        player1.addResource(1);

        CHECK(player1.getNumOfResource(1) == 2);

        player1.removeResource(1);
        CHECK(player1.getNumOfResource(1) == 1);
    }
    SUBCASE("Test addDevelopmentCard & implementCard & buyDevelopmentCard"){
        Player player1("Alice");
        player1.addResource(2);
        player1.addResource(3);
        player1.addResource(4);
        bool flag = player1.buyDevelopmentCard();

        CHECK(flag == true);

        flag = player1.buyDevelopmentCard();

        CHECK(flag == false); // there is not enough resources

        player1.addDevelopmentCard(1);
        flag = player1.implementCard(1);
        CHECK(flag == true);

        flag = player1.implementCard(1); // player 1 don't have a card 1 to implement
        CHECK(flag == false);
    }

    SUBCASE("Test getLongestPath & getLargestArmy & loseLongestPath & loseLargestArmy"){
        Player player1("Alice");
        int points = player1.getPoints();

        CHECK(points == 0);

        player1.getLargestArmy();
        points = player1.getPoints();

        CHECK(points == 2);

        player1.getLongestPath();
        points = player1.getPoints();

        CHECK(points == 4);

        player1.loseLargestArmy();
        points = player1.getPoints();

        CHECK(points == 2);

        player1.loseLongestPath();
        points = player1.getPoints();

        CHECK(points == 0);

    }
    SUBCASE("Test getName"){
        Player player1("Alice");
        CHECK(player1.getName() == "Alice");
    }
}

TEST_CASE("Test Board class"){
    SUBCASE("isTwoTilesNeighbors & isThreeTilesNeighbors"){
        Board board;
        board.initializeBoard();

        bool flag = board.isTwoTilesNeighbors(1,5);

        CHECK(flag == true);

        flag = board.isTwoTilesNeighbors(3,5);

        CHECK(flag == false);

        flag = board.isThreeTilesNeighbors(32,31,36);

        CHECK(flag == true);

        flag = board.isThreeTilesNeighbors(9,7,12);

        CHECK(flag == false);
    }
    SUBCASE("Test initializeBoard & getTiles"){
        Board board;
        board.initializeBoard();

        // check if the indexs is a sea(sea type = -2), in catan board we have 18 sea lands
        int count = 0;

        //check 0, 4, 9, 15 indexs
        size_t j = 3;
        for(size_t i = 0; i<16; i = i+j){
            if(board.getTiles()[i].getType() == -2){
                count++;
            }
            j++;
        }
        //check 22, 28, 33
        for(size_t i = 22; i<34; i = i+j){
            if(board.getTiles()[i].getType() == -2){
                count++;
            }
            j--;
        } 

        //check 3,8,14    
        j = 4;
        for(size_t i = 3; i<15; i = i+j){
            if(board.getTiles()[i].getType() == -2){
                count++;
            }
            j++;
        }
        //check 21 27 32 36
        for(size_t i = 21; i<37; i = i+j){
            if(board.getTiles()[i].getType() == -2){
                count++;

            }
            j--;
        } 
        //check 1,2
        if(board.getTiles()[1].getType() == -2 && board.getTiles()[2].getType() == -2){
            count=count+2;
        }
        if(board.getTiles()[34].getType() == -2 && board.getTiles()[35].getType() == -2){
            count=count+2;

        }    
        CHECK(count == 18);
        // check if the indexs is a lands(type >= 0), in catan board we have 19 lands(lands that diffrent from sea)
        count = 0;
        for (size_t i = 5; i < 32; i++)
        {
            if(i == 8) i++;
            else if(i == 14) i++;
            else if(i == 21) i++;
            else if(i == 27) i++;
            else if(board.getTiles()[i].getType() >= 0){
                count++;
            }
        }
        CHECK(count == 19);
        
    }
    SUBCASE("Test getThiefPosition & moveThief"){
        Board board;
        board.initializeBoard();
        // The thief start in the desert land (type = 5)
        size_t i;
        for(i=0; i<37; i++){
            if(board.getTiles()[i].getType() == 5) break;
        }
        CHECK(i == board.getThiefPosition());
        board.moveThief(5);
        CHECK(board.getThiefPosition() == 5);
    }
}

TEST_CASE("Test Tiles class"){
    SUBCASE("Test getLandName & getType & getNumber & getPosition"){
        Tile tile;
        tile.setPosition(1,0,5);
        tile.setType(0);
        tile.setNumber(1);
        CHECK(tile.getNumber() == 1);
        CHECK(tile.getType() == 0);
        CHECK(tile.getPosition()[0] == 1);
        CHECK(tile.getPosition()[1] == 0);
        CHECK(tile.getPosition()[2] == 5);

        CHECK(tile.getLandName() == "Forest");
        tile.setType(1);
        CHECK(tile.getLandName() == "Hills");
        tile.setType(2);
        CHECK(tile.getLandName() == "Pasture Land");
        tile.setType(3);
        CHECK(tile.getLandName() == "Agricultural Land");
        tile.setType(4);
        CHECK(tile.getLandName() == "Mountains");
        tile.setType(5);
        CHECK(tile.getLandName() == "Desert");
        tile.setType(-2);
        CHECK(tile.getLandName() == "Sea");
    }
    SUBCASE("Test turnOn && turnOff && isContainsThief"){
        Tile tile;
        tile.turnOff(); // tile don't get resources
        CHECK(tile.isContainsThief() == true); 
        tile.turnOn(); // tile get resources 
        CHECK(tile.isContainsThief() == false);
    }
    SUBCASE("Test createResource"){
        Tile tile;
        tile.setType(0); // Forest
        Resource resource = tile.createResource(); // resource type = 0, resource name = wood
        CHECK(tile.createResource().getType() == 0); 
        CHECK(tile.createResource().getName() == "wood");
    }
}
TEST_CASE("Test Tool class"){
    Path path(1,5);
    CHECK(path.getPoints() == 0);
    Settlment settlment(1,5,0);
    CHECK(settlment.getPoints() == 1);
    settlment.upgrateToCity(); 
    CHECK(settlment.getIsCity() == true);
}
TEST_CASE("Test Resource class"){
    Resource resource;
    CHECK(resource.getType() == -1);
    resource.setType(0);
    CHECK(resource.getType() == 0);
    CHECK(resource.getName() == "wood");
    resource.setType(1);
    CHECK(resource.getType() == 1);
    CHECK(resource.getName() == "brick");
    resource.setType(2);
    CHECK(resource.getType() == 2);
    CHECK(resource.getName() == "wool");
    resource.setType(3);
    CHECK(resource.getType() == 3);
    CHECK(resource.getName() == "oats");
    resource.setType(4);
    CHECK(resource.getType() == 4);
    CHECK(resource.getName() == "iron");
    resource.setType(5);
    CHECK(resource.getType() == 5);
    CHECK(resource.getName() == "no resource");  // resource from desert          

}
TEST_CASE("Test DevelopCard class"){
    DevelopCard card;

    card.setType(0);
    CHECK(card.getType() == 0);
    CHECK(card.getName() == "knight");
    card.setType(1);
    CHECK(card.getType() == 1);
    CHECK(card.getName() == "victory point");
    card.setType(2);
    CHECK(card.getType() == 2);
    CHECK(card.getName() == "monopoly card");
    card.setType(3);
    CHECK(card.getType() == 3);
    CHECK(card.getName() == "build path");
    card.setType(4);
    CHECK(card.getType() == 4);
    CHECK(card.getName() == "year of plenty");
}

TEST_CASE("Test Catan functions")
{
    Catan catan;

    SUBCASE("Test addPlayer") {
        Player player1("Alice");
        Player player2("Bob");

        CHECK(catan.addPlayer(player1) == true);
        CHECK(catan.addPlayer(player2) == true);
        CHECK(catan.addPlayer(player1) == false); // Duplicate player
        Player player3("David");
        Player player4("Shlomi");
        Player player5("Yoav");
        CHECK(catan.addPlayer(player3) == true);
        CHECK(catan.addPlayer(player4) == true);
        CHECK(catan.addPlayer(player5) == false); // Maximum 4 player in the game
    }


    SUBCASE("Test Path & Settlment functions") {
        Player player1("Alice");
        Player player2("Bob");
        catan.addPlayer(player1);
        catan.addPlayer(player2);
        Board board;
        board.initializeBoard();
        catan.setBoard(board);
        Path path(1,5);
        Path path1(0,1);
        Path path2(2,3);
        Path path3(5,6);
        CHECK(catan.addPath(0,path2) == false);// there is not settlment in this tiles  
        Settlment settlment(0,1,5);
        Settlment settlment1(1,5,6);
        Settlment settlment2(31,32,36);
        CHECK(catan.isAvaliableForSettlment(settlment.getTiles()[0], settlment.getTiles()[1], settlment.getTiles()[2]) == true);
        CHECK(catan.addSettlment(0,settlment) == true);
        CHECK(catan.isAvaliableForPath(path.getTiles()[0], path.getTiles()[1]) == true);         

        CHECK(catan.addPath(0,path) == true); 
        CHECK(catan.addPath(0,path1) == false); // cant add a path for two tiles with types -2(sea)
        CHECK(catan.isAvaliableForSettlment(settlment.getTiles()[0], settlment.getTiles()[1], settlment.getTiles()[2]) == false); // player1(Alice) in this position
        CHECK(catan.isAvaliableForPath(path.getTiles()[0], path.getTiles()[1]) == false); // player1(Alice) in this position

        CHECK(catan.addSettlment(1,settlment1) == false); // there is a settlment near by 1 to this position
        CHECK(catan.addPath(1,path) == false); // there is a path of Alice in this position


        CHECK(catan.isPathConnectToPath(path,path3) == true);
        CHECK(catan.isPathConnectToPath(path,path2) == false);
        CHECK(catan.isPathConnectToSettlment(path,settlment) == true);
        CHECK(catan.isPathConnectToSettlment(path,settlment2) == false);

    }
    SUBCASE("Test Devlopment card & Longest path"){
        Player player1("Alice");
        Player player2("Bob");
        Path p1(1,5);
        Path p2(0,5);
        Path p3(4,5);
        Path p4(5,10);
        Path p5(10,11);
        player1.setPath(p1);
        player1.setPath(p2);
        player1.setPath(p3);
        player1.setPath(p4);
        player1.setPath(p5);

        catan.addPlayer(player1);
        catan.addPlayer(player2);
        CHECK(catan.findLongestPath(0) == 5);
        CHECK(catan.findLongestPath(1) == 0);
    }
}