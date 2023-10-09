#pragma once

#include <iostream>
#include "primitives.hpp"
#include "mathtools.hpp"
#include "floatcompar.hpp"

bool boundingboxes_overlap(const Triangle_t &tr1, const Triangle_t &tr2) {
    Point_t Amin{std::min({tr1.v1.x, tr1.v2.x, tr1.v3.x}), std::min({tr1.v1.y, tr1.v2.y, tr1.v3.y}), 
                std::min({tr1.v1.z, tr1.v2.z, tr1.v3.z})};
    Point_t Amax{std::max({tr1.v1.x, tr1.v2.x, tr1.v3.x}), std::max({tr1.v1.y, tr1.v2.y, tr1.v3.y}), 
                std::max({tr1.v1.z, tr1.v2.z, tr1.v3.z})};

    Point_t Bmin{std::min({tr2.v1.x, tr2.v2.x, tr2.v3.x}), std::min({tr2.v1.y, tr2.v2.y, tr2.v3.y}), 
                std::min({tr2.v1.z, tr2.v2.z, tr2.v3.z})};
    Point_t Bmax{std::max({tr2.v1.x, tr2.v2.x, tr2.v3.x}), std::max({tr2.v1.y, tr2.v2.y, tr2.v3.y}), 
                std::max({tr2.v1.z, tr2.v2.z, tr2.v3.z})};
    
    if ((Bmin.x > Amax.x) || (Bmin.y > Amax.y) || (Bmin.z > Amax.z) 
        || (Amin.x > Bmax.x) || (Amin.y > Bmax.y) || (Amin.z >Bmax.z))
        return false; //no intersect
    else 
        return true;  
}

bool lookup_intersection(Triangle_t &tr1, Triangle_t &tr2) {
    if (!boundingboxes_overlap(tr1, tr2))
        return false; //no intersection
    
    assert(tr1.valid() && tr2.valid());

    //........................................
    //count distances between tr1 and vertices from tr2, с учетом ориентации посчитает расстояния
    float Y1 = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v1);
    float Y2 = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v2);
    float Y3 = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v3);
    
    if ((greater(Y1, 0) && greater(Y2, 0) && greater(Y3, 0)) || (less(Y1, 0) && less(Y2, 0) && less(Y3, 0)))
        return false; //no intersection

    if (is_zero(Y1) && is_zero(Y2) && is_zero(Y3)) {
        //coplanar 
    }
    //.............................


    //....................
    //count distances between tr2 and vertices from tr1, с учетом ориентации посчитает расстояния
    float Y4 = determinant3x3(tr2.v1, tr2.v2, tr2.v3, tr1.v1);
    float Y5 = determinant3x3(tr2.v1, tr2.v2, tr2.v3, tr1.v2);
    float Y6 = determinant3x3(tr2.v1, tr2.v2, tr2.v3, tr1.v3);

    if ((greater(Y4, 0) && greater(Y5, 0) && greater(Y6, 0)) || (less(Y4, 0) && less(Y5, 0) && less(Y6, 0)))
        return false; //no intersection

    //..........................

    /*rotation and swapping next, check orientation*/

}