/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Board.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
using namespace std;
using namespace ariel;

int main()
{

    Board board; // get the board of the game.
    board.initializeBoard();
    cout<<board.toString();
    board.moveThief(6);
    cout<<board.toString();
    board.moveThief(4);
    cout<<board.toString();
    board.moveThief(6);
    cout<<board.toString();

}