#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cmath>


#define flt_tolerance 0.00001
#define inter_area_width 100.0

class point_t {
public:
    float x = NAN, y = NAN, z = NAN;
    //constructor explicit?
    point_t(float x_, float y_, float z_): x(x_), y(y_), z(z_) {} 

    //operator =

    bool valid() const { return !(x != x || y != y || z != z); }

    bool equal(const point_t &rhs) const {
        assert(valid() && rhs.valid());
        return  (std::abs(x - rhs.x) < flt_tolerance) && 
                (std::abs(y - rhs.y) < flt_tolerance) &&
                (std::abs(z - rhs.z) < flt_tolerance);
    }

    void print() const { std::cout << "(" << x << " ; " << y << " ; " << z << ")"; }
};

class line_t {
    point_t r0;
    std::vector<float> drc_vec{NAN, NAN, NAN};

public:
    //constructor, is line direction strict, copy of point_t, 
    line_t(const point_t &p1, const point_t &p2): r0(p1) {
        drc_vec.push_back(p2.x - p1.x);
        drc_vec.push_back(p2.y - p1.y);
        drc_vec.push_back(p2.z - p1.z);
    } 

    bool valid() const {
        return !((!r0.valid()) || (drc_vec[0] != drc_vec[0]) ||
                 (drc_vec[1] != drc_vec[1]) ||(drc_vec[2] != drc_vec[2]));
    }

};