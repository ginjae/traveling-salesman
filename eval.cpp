#include <iostream>
#include <unordered_map>

#include "utils/tsp_parser.h"

using namespace std;

std::unordered_map<std::string, std::string> DATASET_PATHS = {
    {"a280",            "datasets/a280.tsp"},
    {"kz9976",          "datasets/kz9976.tsp"},
    {"mona-lisa100K",   "datasets/mona-lisa100K.tsp"},
    {"xql662",          "datasets/xql662.tsp"}
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <tsp_file>" << endl;
        return 1;
    }

    string dataset_name = argv[1];
    if (DATASET_PATHS.find(dataset_name) == DATASET_PATHS.end()) {
        cout << "Error: Dataset '" << dataset_name << "' not found" << endl;
        return 1;
    }


    auto nodes = TSPParser::parse(DATASET_PATHS[dataset_name]);
    // for (const auto& node : nodes)
    //     cout << node.id << ": " << node.x << ", " << node.y << endl;

    return 0;
}