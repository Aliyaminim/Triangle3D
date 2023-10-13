#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include "primitives.hpp"
#include "geotools.hpp"
#include "tools.hpp"

int main() {
    std::pair<int, std::vector<double>> input; 
    std::unordered_map<int, int> output;
    
    read_data(input);
    std::vector<Triangle_t> triangles = get_triangles(input);

    for (int i = 0; i < input.first; ++i)
        for (int j = i + 1; j < input.first; ++j) {
            if(lookup_intersection(triangles[i], triangles[j])) {
                print_results(i, j, output);
            }
        }

    std::cout << std::endl;

    return 0;
}

//checking input is needed