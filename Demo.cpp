/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"

using namespace std;
using namespace ariel;

int main(){
    Player p1("shlomi");
    Player p2("sali");
    Player p3("Bibi");
    Player p4("yair");
    Catan catan;
    catan.addPlayer(p1);
    catan.addPlayer(p2);
   // catan.startGame();



    // catan.addPath(0,path1);
    // cout<<"(5,1)"<<endl;
    // cout<<catan.isAvaliableForPath(5,1)<<endl;
    // cout<<"(5,2)"<<endl;
    // cout<<catan.isAvaliableForPath(5,2)<<endl;
    // cout<<"(6,7)"<<endl;
    // cout<<catan.isAvaliableForPath(6,7)<<endl;
    // cout<<"(5,10)"<<endl;
    // cout<<catan.isAvaliableForPath(5,10)<<endl;
    // catan.addPath(1,path1);
    // catan.addPath(1,path2);
    // Player p5("EladHOREV");
    Path path1(11,5);
    Path path2(5,10);
    Path path3(10,11);
    Path path4(10,12);
    Path path5(10,9);
    Settlment settlment(5,11,10);
    cout<<catan.isPathConnectToSettlment(path1,settlment)<<endl;
    cout<<catan.isPathConnectToSettlment(path2,settlment)<<endl;
    cout<<catan.isPathConnectToSettlment(path3,settlment)<<endl;
    cout<<catan.isPathConnectToSettlment(path4,settlment)<<endl;
    cout<<catan.isPathConnectToSettlment(path5,settlment)<<endl;
    p1.setSettlment(settlment);
    p1.addResource(3);
    p1.addResource(3);
    p1.upgrateToCity(1);
    p1.upgrateToCity(0);
     cout<<p1.toString();
    p1.addResource(4);
    p1.addResource(4);
    p1.addResource(4);
    p1.upgrateToCity(0);
     cout<<p1.toString();
    p1.upgrateToCity(0);

    

    // catan.addSettlment(0,settlment);
    // cout<<"(5,6,10)"<<endl;
    // cout<<catan.isAvaliableForSettlment(5,6,10)<<endl;
    // cout<<"(0,6,10)"<<endl;
    // cout<<catan.isAvaliableForSettlment(0,6,10)<<endl;
    // cout<<"(1,2,5)"<<endl;
    // cout<<catan.isAvaliableForSettlment(1,2,5)<<endl;

    // catan.addSettlment(2,settlment);
    // catan.addSettlment(1,settlment1);
    // catan.addSettlment(3,settlment2);
    // catan.addSettlment(2,settlment3);
    // catan.addSettlment(0,settlment4);
    // catan.addSettlment(2,settlment1);
    // cout<<catan.isAvaliableForSettlment(1,0,5)<<endl;
    // catan.addPlayer(p5);


    // Board board; // get the board of the game.
    // board.initializeBoard();
    // cout<<board.toString();
    // board.moveThief(6);
    // cout<<board.toString();
    // board.moveThief(4);
    // cout<<board.toString();
    // board.moveThief(6);
    // cout<<board.toString();

}