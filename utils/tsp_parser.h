#ifndef TSP_PARSER_H
#define TSP_PARSER_H

#include <vector>
#include <string>

class Node {
public:
    int id;
    double x, y;
};

class TSPParser {
public:
    static std::vector<Node> parse(const std::string& file_path);
//    std::string name;
//    std::string dimension;
};

#endif
