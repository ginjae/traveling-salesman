#include "utils/parse_tsp.h"
#include "algorithms/mst_based.h"
#include "algorithms/held_karp.h"
#include "algorithms/jam.h"

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <filesystem>
#include <fstream>

using namespace std;

unordered_map<string, string> DATASET_PATHS = {
    {"jam20",           "datasets/jam20.tsp"},
    {"a280",            "datasets/a280.tsp"},
    {"xql662",          "datasets/xql662.tsp"},
    {"kz9976",          "datasets/kz9976.tsp"},
    {"mona-lisa100K",   "datasets/mona-lisa100K.tsp"}
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <tsp_file> <algorithm>" << endl;
        return 1;
    }

    string dataset_name = argv[1];
    if (DATASET_PATHS.find(dataset_name) == DATASET_PATHS.end()) {
        cout << "Error: Dataset '" << dataset_name << "' not found" << endl;
        cout << "Available datasets: jam20, a280, xql662, kz9976, mona-lisa100K" << endl;
        return 1;
    }

    string dataset_path = DATASET_PATHS[dataset_name];
    string algorithm_name = argv[2];

    TSPSolver* tsp_solver;
    if (algorithm_name == "mst-based") {
        tsp_solver = new MSTBased;
    } else if (algorithm_name == "held-karp") {
        tsp_solver = new HeldKarp;
    } else if (algorithm_name == "jam") {
        tsp_solver = new Jam;
    } else {
        cout << "Error: Algorithm '" << algorithm_name << "' not found" << endl;
        cout << "Available algorithms: mst-baed, held-karp, jam" << endl;
        return 1;
    }
 
    
    vector<Node> nodes = parse_tsp(dataset_path);
    auto start = chrono::system_clock::now();
    tsp_solver->solve(nodes);
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;

    string result_path = "results/" + dataset_name + "_" + algorithm_name + ".txt";
    filesystem::create_directories("results");

    ofstream file(result_path);
    file << "Length: " << fixed << tsp_solver->get_total_length(nodes) << endl;
    file << "Duration (s): " << fixed << duration.count() << endl;
    file << endl;
    file << "[ ";
    for (int i = 0; i < tsp_solver->solution.size(); i++) {
        file << tsp_solver->solution[i] + 1;
        if (i != tsp_solver->solution.size() - 1)
            file << ", ";
    }
    file << " ]";
    

    cout << "Length: " << fixed << tsp_solver->get_total_length(nodes) << endl;
    cout << "Duration (s): " << fixed << duration.count() << endl;

    delete tsp_solver;

    return 0;
}