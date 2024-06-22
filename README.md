# System Programming 2 Course Assignment 3
### For Computer Science B.Sc. Ariel University

**By Shlomi Zecharia**

## Description

This project is part of the System Programming 2 course assignment at Ariel University. The task involves implementing catan board game.

### Files Included

* **Catan.hpp**: Header file containing the declaration of the catan game class.

* **Board.hpp**: Header file containing the declaration of the catan board class.

* **Resource.hpp**: Header file containing the declaration of the resources class.

* **Player.hpp**: Header file containing the declaration of the Player class.

* **Tile.hpp**: Header file containing the declaration of the Tile class.

* **DevelopCard.hpp**: Header file containing the declaration of the DevelopCard class.

* **Tool.hpp**: Header file containing the declaration of the Tool class.

* **Catan.cpp**: Source file containing the implementation of the catan game class.

* **Board.cpp**: Source file containing the implementation of the catan board class.

* **Resource.hpp**: Source file containing the implementation of the resources class.

* **Player.hpp**: Source file containing the implementation of the Player class.

* **Tile.hpp**: Source file containing the implementation of the Tile class.

* **DevelopCard.hpp**: Source file containing the implementation of the DevelopCard class.

* **Tool.hpp**: Source file containing the implementation of the Tool class.

## How to play  

### Run demo.cpp file 

#### initializing the board
After run the game, press "Y" if this is the board that you want, else press "N" and new board initialize

#### Choose the first two settlements position & two paths position
The players order is randomly, player choose the first settlment - "x" "y" "z" that represent the ID (index of tiles), this tiles need to be connected. 
After the player choose settlement is need to choose the first path - "x" "y" that represent the ID (index of tiles),this tiles need to be connectd, can't be both sea and must connected to settlment of this player. 

player choose the second settlment - "x" "y" "z" that represent the ID (index of tiles), this tiles need to be connected. 
After the player choose settlement is need to choose the second path - "x" "y" that represent the ID (index of tiles), this tiles need to be connectd, can't be both sea and must connected to settlment of this player. 

#### Start menu
- Press "1" - view the board
- Press "2" - view player game data (settlement ,resources ,Points and more.....)
- Press "3" - roll dices :
if dices resources is 7, all the player with more then 7 resources need to give half of they resources (A menu with player resources open after if they have more then 7 resources (choose by index 1...5)).
else, each player with tiles with the number like the dices result, get resources from this tiles

#### Action menu
- Press "1" - view the board

- Press "2" - view player game data (settlement ,resources ,Points.....)

- Press "3" - build path (1 wood & 1 brick needed)

- Press "4" - build settlement (1 wood & 1 brick & 1 wool & 1 oats needed)

- Press "5" - build city (2 oats & 3 iron needed), A menu with player settlement open after press 5 to build a city (choose by index)

- Press "6" - buy development card (1 wool & 1 oats & 1 iron needed)

- Press "7" - use development card , A menu with player development cards open after press 7 to use a development card :
    - press 1 (knight card): move the thief, the player with most knight card get the largest army(2 more points) after more then 3 knight card.
    - press 2 (victory point): the player get one more victory point
    - press 3 (monopoly card):the player choose which resource to take from all players, the players must give all the resources of this type of resource to the player that use monoply card  
    - press 4 (build path): the player can build two paths for free
    - press 5 (year of plenty): the player get to choose 2 resources for free 

- Press "8" - trade, A menu with player resources open after press 8 to use trade :
player that want to trade choose resource (by index 1...5) to give and choose resource to take , after all the player ask if they want to trade.

- Press "9" - pass the turn

#### Points
 - Longest path : the player with the longest path(count from 5+) get 2 victory points
 - Largest army : the player with largest army(count from 3+) get 2 victory points
 - Build settlement : the plsyer get 1 victory point for each settlement
 - Build city : the player get 1 victory point for each city

### Victory

The first player that reach to 10 victory points, won the game !!

## Requirements

* Linux machine (Ubuntu 22.04.1 LTS preferable)
* GNU cpp (g++ Compiler)
* Make

## Building

```bash
# Cloning the repo to local machine.
git clone https://github.com/2shlomi9/Catan_Board_Game.git

# Install g++ compiler 
sudo apt-get install g++

# Building all the necessary files & the main programs.
make demo
make test

# Clean files(test, demo, *.o).
make clean
```
## Running:


##### Run Demo:
./demo

##### Run Tests:
./test

```
