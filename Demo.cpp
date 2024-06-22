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
    Catan catan;
    for(size_t i=0; i<50;i++){
        p1.addResource(0);
        p1.addResource(1);
        p1.addResource(2);
        p1.addResource(3);
        p1.addResource(4);
    }
    p2.addDevelopmentCard(2);
    catan.addPlayer(p1);
    catan.addPlayer(p2);
    catan.runGame();
  

}