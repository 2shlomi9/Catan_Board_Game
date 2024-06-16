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
    catan.addPlayer(p1);
    catan.addPlayer(p2);
    catan.runGame();
  

}