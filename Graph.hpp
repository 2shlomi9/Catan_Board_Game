#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel {

    class Graph {

        private:

            std::vector<std::vector<int>> adjacencyMatrix;

        public:

            Graph() = default;

            void loadGraph(const std::vector<std::vector<int>>& graph);

            void printGraph() const;

            const std::vector<std::vector<int>>& getAdjacencyMatrix() const {
                return adjacencyMatrix;
            }

    };

} 

