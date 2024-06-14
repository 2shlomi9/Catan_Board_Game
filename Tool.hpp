#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel{
    class Tool{
        private:
            int points;
            vector<int>tiles;
            
        public:
            Tool(const int points, const vector<int> tiles) : points(points), tiles(tiles){}
            const int getPoints();
            vector<int> getTiles() const; 
            string toString() const;

    };
    class Path : public Tool{
        private:
            
        public:
            Path(const int t1, const int t2) : Tool(0,{t1, t2}){}
    };
    class Settlment : public Tool{
        private:
            bool isCity;
            
        public:
            Settlment(const int t1, const int t2, const int t3) : Tool(1,{t1,t2,t3}), isCity(false){} 
            void upgrateToCity();
            bool getIsCity()const;
    };

    
}