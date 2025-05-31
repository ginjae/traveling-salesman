#ifndef PARSE_TSP_H
#define PARSE_TSP_H

#include "node.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector<Node> parse_tsp(const std::string& file_path) {
    std::ifstream file(file_path);
    std::vector<Node> nodes;
    std::string line;
    bool reading_coords = false;

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << file_path << std::endl;
        return nodes;
    }

    while (getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != std::string::npos) {
            reading_coords = true;
            continue;
        }
        if (line.find("EOF") != std::string::npos) {
            break;
        }
        if (reading_coords) {
            std::istringstream iss(line);
            Node node;
            if (iss >> node.id >> node.x >> node.y) {
                nodes.push_back(node);
            } else {
                std::cout << "Failed to parse coordinate: " << line << std::endl;
            }
        }
    }

    return nodes;
}

#endif
