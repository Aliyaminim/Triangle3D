#include <iostream>
#include <vector>
#include <cassert>
#include "primitives.hpp"
#include "geotools.hpp"

int main() {
    std::pair<int, std::vector<double>> input; 

    std::cin >> input.first; //number of triangles
    assert(std::cin.good());

    //reading data
    for (int i = 0; i < input.first * 9; ++i) {
        float tmp;
        std::cin >> tmp;
        assert(std::cin.good());
        input.second.push_back(tmp);
    }
    std::vector<Triangle_t> triangles = get_triangles(input);

    for (int i = 0; i < input.first; ++i)
        for (int j = i + 1; j < input.first; ++j) {
            if(lookup_intersection(triangles[i], triangles[j]))
                std::cout << i << " " << j << " ";
        }

    std::cout << std::endl;

    return 0;
}

//checking input is needed