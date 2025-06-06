#include "utils/parse_tsp.h"
#include "algorithms/mst_based.h"
#include "algorithms/held_karp.h"
#include "algorithms/nearest_neighbor.h"
#include "algorithms/greedy_edge.h"
#include "algorithms/jam.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <chrono>
#include <filesystem>
#include <fstream>

using namespace std;

map<string, string> DATASET_PATHS = {
    {"jam20",           "datasets/jam20.tsp"},
    {"a280",            "datasets/a280.tsp"},
    {"xql662",          "datasets/xql662.tsp"},
    {"kz9976",          "datasets/kz9976.tsp"},
    {"mona-lisa100K",   "datasets/mona-lisa100K.tsp"}
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <algorithm> <tsp_file>" << endl;
        return 1;
    }

    string algorithm_name = argv[1];

    unique_ptr<TSPSolver> tsp_solver;
    if (algorithm_name == "mst_based") {
        tsp_solver = make_unique<MSTBased>();
    } else if (algorithm_name == "held_karp") {
        tsp_solver = make_unique<HeldKarp>();
    } else if (algorithm_name == "nearest_neighbor") {
        tsp_solver = make_unique<NearestNeighbor>();
    } else if (algorithm_name == "randomized_nearest_neighbor") {
        tsp_solver = make_unique<RandomizedNearestNeighbor>();
    } else if (algorithm_name == "greedy_edge") {
        tsp_solver = make_unique<GreedyEdge>();
    } else if (algorithm_name == "jam") {
        tsp_solver = make_unique<Jam>();
    } else {
        cout << "Error: Algorithm '" << algorithm_name << "' not found" << endl;
        cout << "Available algorithms: mst_based, held_karp, jam" << endl;
        return 1;
    }

    string dataset_name = argv[2];
    if (DATASET_PATHS.find(dataset_name) == DATASET_PATHS.end()) {
        cout << "Error: Dataset '" << dataset_name << "' not found" << endl;
        cout << "Available datasets: ";
        for (const auto& [name, path] : DATASET_PATHS)
            cout << name << " ";
        cout << endl;
        return 1;
    }
    string dataset_path = DATASET_PATHS[dataset_name];
    
    vector<Node> nodes = parse_tsp(dataset_path);
    auto start = chrono::system_clock::now();
    tsp_solver->solve(nodes);
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;

    string result_path = "results/" + dataset_name + "/" + algorithm_name + ".txt";
    filesystem::create_directories("results/" + dataset_name);

    ofstream file(result_path);
    file << "Length: " << fixed << tsp_solver->get_total_distance(nodes) << endl;
    file << "Duration (s): " << fixed << duration.count() << endl;
    file << endl;
    file << "[ ";
    for (int i = 0; i < tsp_solver->solution.size(); i++) {
        file << tsp_solver->solution[i] + 1;
        if (i != tsp_solver->solution.size() - 1)
            file << ", ";
    }
    file << " ]";
    

    cout << "Length: " << fixed << tsp_solver->get_total_distance(nodes) << endl;
    cout << "Duration (s): " << fixed << duration.count() << endl;
    cout << endl;
    cout << "[ ";
    for (int i = 0; i < tsp_solver->solution.size(); i++) {
        cout << tsp_solver->solution[i] + 1;
        if (i != tsp_solver->solution.size() - 1)
            cout << ", ";
    }
    cout << " ]";

    return 0;
}
