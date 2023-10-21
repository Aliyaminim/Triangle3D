#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "primitives.hpp"

//reads data
void read_data(std::pair<int, std::vector<double>> &input) {
    std::cin >> input.first; //number of triangles
    assert(std::cin.good());

    for (int i = 0; i < input.first * 9; ++i) {
        float tmp;
        std::cin >> tmp;
        assert(std::cin.good());
        input.second.push_back(tmp);
    }
}

//constructs triangles from given data
std::vector<Triangle_t> get_triangles (std::pair<int, std::vector<double>> &input) {
        std::vector<Triangle_t> triangles;

        Point_t v1 {};
        Point_t v2 {};
        Point_t v3 {};

        auto coord_it = input.second.begin();

        for (int i = 0; i < input.first; ++i) {
                v1.set(coord_it[0], coord_it[1], coord_it[2]);
                coord_it += 3;
                v2.set(coord_it[0], coord_it[1], coord_it[2]);
                coord_it += 3;
                v3.set(coord_it[0], coord_it[1], coord_it[2]);
                coord_it += 3;
                
                assert(v1.valid() && v2.valid() && v3.valid());
                triangles.push_back(Triangle_t(v1, v2, v3));
        }

        return triangles;
}

void add_result(int i, int j, std::vector<int> &output, std::unordered_map<int, int> &hash_output) {
    if (hash_output.find(i) == hash_output.end()) {
        hash_output.emplace(i, i);
        output.push_back(i);
    }

    if (hash_output.find(j) == hash_output.end()) {
        hash_output.emplace(j,j);
        output.push_back(j);
    }
}

//prints numbers of intersecting triangles
void print_results(std::vector<int> &output) {
    auto it_begin = output.begin();
    auto it_end = output.end();

    std::sort(it_begin, it_end);
    for (auto it = it_begin; it != it_end; ++it)
        std::cout << *it << "\n";
    
    std::cout << std::endl;
}
