#pragma once

#include <iostream>
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

//prints numbers of intersecting triangles
void print_results(int i, int j, std::unordered_map<int, int> &output) {
    if (output.find(i) == output.end()) {
        std::cout << i << " ";
        output.emplace(i, i);
    }

    if (output.find(j) == output.end()) {
        std::cout << j << " ";
        output.emplace(j,j);
    }
}
