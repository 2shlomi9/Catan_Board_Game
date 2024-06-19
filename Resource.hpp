#pragma once
#include <iostream>
#include <string>


using namespace std;

namespace ariel{
    
    class Resource{

        private:
            int type; // resource type 

        public:
        // ---------------- : Constructors : ----------------
            Resource(const int type) : type(type){}
            Resource() : type(-1){}

        // ---------------- : Functions : ----------------
            int getType() const; // return the type of the resource

            void setType(const int& type); // set type for the resource
            
            string getName() const; // return the of the resource
    };
}
