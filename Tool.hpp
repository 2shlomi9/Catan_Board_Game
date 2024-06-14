#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel{
    class Tool{
        private:
            int points;
            

        public:
            Tool(const int points) : points(points){}
            const int getPoints();

    };
    class Path : public Tool{
        private:
            vector<int>tiles;
        public:
            Path(vector<int> tiles) : Tool(0), tiles(tiles){} 
    };
    class Settlment : public Tool{
        private:
            vector<int>tiles;
        public:
            Settlment(vector<int> tiles) : Tool(1), tiles(tiles){} 
    };
    class City : public Tool{
        private:
            vector<int>tiles;
        public:
            City(vector<int> tiles) : Tool(2), tiles(tiles){} 
    };

    
}