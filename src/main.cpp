#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include "primitives.hpp"
#include "geotools.hpp"
#include "tools.hpp"

int main() {
    std::pair<int, std::vector<double>> input; 
    std::unordered_map<int, int> hash_output;
    std::vector<int> output;
    
    read_data(input);
    std::vector<Triangle_t> triangles = get_triangles(input);

    int kol_intersection = 0;
    for (int i = 0; i < input.first; ++i)
        for (int j = i + 1; j < input.first; ++j) {
            if(lookup_intersection(triangles[i], triangles[j])) {
                add_result(i, j, output, hash_output);
                ++kol_intersection;
            }
        }

    if (kol_intersection == 0)
        std::cout << "No intersection occurs" << std::endl;
    else 
        print_results(output);

    return 0;
}

//checking input is needed