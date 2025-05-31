#include "tsp_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Node> TSPParser::parse(const string& filepath) {
    ifstream file(filepath);
    vector<Node> nodes;
    string line;
    bool reading_coords = false;

    if (!file.is_open()) {
        cout << "Failed to open file: " << filepath << endl;
        return nodes;
    }

    while (getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            reading_coords = true;
            continue;
        }
        if (line.find("EOF") != string::npos) {
            break;
        }
        if (reading_coords) {
            istringstream iss(line);
            Node node;
            if (iss >> node.id >> node.x >> node.y) {
                nodes.push_back(node);
            } else {
                cout << "Failed to parse coordinate: " << line << endl;
            }
        }
    }

    return nodes;
}
