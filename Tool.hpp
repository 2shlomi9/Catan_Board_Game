#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel{
    class Tool{
        private:
            int points; // the points of the tools
            vector<int>tiles; // list of the tiles of the tool
            
        public:
        // ---------------- : Constructors : ----------------
            Tool(const int points, const vector<int> tiles) : points(points), tiles(tiles){}

        // ---------------- : Functions : ----------------
            const int getPoints(); // return the points of the Tool(settlment 1, city 2)
            vector<int> getTiles() const; // return the tiles of the Tool
            string toString() const; // return string of this tool

    };

// ---------------- : Class path : ----------------

    class Path : public Tool{
        private:
            
        public:
        // ---------------- : Constructors : ----------------
            Path(const int t1, const int t2) : Tool(0,{t1, t2}){}
    };


// ---------------- : Class settlment : ----------------

    class Settlment : public Tool{
        private:
            bool isCity; // true if the settlment is a city
            
        public:
        // ---------------- : Constructors : ----------------
            Settlment(const int t1, const int t2, const int t3) : Tool(1,{t1,t2,t3}), isCity(false){} 

        // ---------------- : Functions : ----------------

            void upgrateToCity(); // upgrate a settlment to city
            bool getIsCity()const; // check if the setllment is already a city
    };

    
}