#pragma once

#include <iostream>
#include "primitives.hpp"
#include "mathtools.hpp"
#include "floatcompar.hpp"

//checks if bounding boxes overlap
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

// rotates vertices about a given triangle num times preserving the order
void rotate_TriangleVertices(Triangle_t &tr, int num){
    for (int j = 0; j < num; j++) {
        Point_t temp = tr.v3;
        tr.v3 = tr.v2;
        tr.v2 = tr.v1;
        tr.v1 = temp; //hope, assignment works
    }
    return;
}

// swaps vertices in triangle to change direction of normal
void swap_TriangleVertices(Triangle_t &tr) {
    Point_t temp = tr.v2;
    tr.v2 = tr.v3;
    tr.v3 = temp;
    for (int i = 0; i < 3; ++i) 
        tr.normal[i] = (-1) * tr.normal[i];
    return;
}

//calculates distances between tr1's plane and tr2's vertices considering orientability 
void count_vdistance(const Triangle_t &tr1, Triangle_t &tr2) { 
    tr2.vdistance[0] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v1);
    tr2.vdistance[1] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v2);
    tr2.vdistance[2] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v3);
}

bool allDistSameSigned(const Triangle_t &tr) {
    return ((greater(tr.vdistance[0], 0) && greater(tr.vdistance[1], 0) && greater(tr.vdistance[2], 0)) 
        || (less(tr.vdistance[0], 0) && less(tr.vdistance[1], 0) && less(tr.vdistance[2], 0)));
}

bool allDistZero(const Triangle_t &tr) {
     return (is_zero(tr.vdistance[0]) && is_zero(tr.vdistance[1]) && is_zero(tr.vdistance[2]));
}

void make_consistentTriangleOrientation(Triangle_t &tr1, Triangle_t &tr2) {
    /* making a consistent form of relative position of triangles:
    vertix v1 of each triangle is the only vertix in positive subspace of the other triangle's plane */
    /*if ((less(Y5, 0) && greater(Y4, 0) && greater(Y6, 0)) || (greater(Y5, 0) && less(Y4, 0) && less(Y6,0))) {
        rotate_TriangleVertices(tr1, 2); 
        //rotate until v1 is the only vertix on that side of the other triangle's plane
        float Y = determinant3x3(tr2.v1, tr2.v2, tr2.v3, tr1.v1);
        if (Y < 0)
            swap_TriangleVertices(tr2); //assure v1 in tr1 in positive subspace of tr2's plane
    } else if ((less_equal(Y6, 0) && greater_equal(Y4, 0) && greater_equal(Y5, 0)) || (greater_equal(Y6, 0) && less_equal(Y4, 0) && less_equal(Y5, 0))) {
        rotate_TriangleVertices(tr1, 1);
        float Y = determinant3x3(tr2.v1, tr2.v2, tr2.v3, tr1.v1);
        if (Y < 0)
            swap_TriangleVertices(tr2);
    }
    
    if ((less_equal(Y2, 0) && greater(Y1, 0) && greater(Y3, 0)) || (greater(Y2, 0) && less(Y1, 0) && less(Y3,0))) {
        rotate_TriangleVertices(tr2, 2);
        float Y = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v1);
        if (Y < 0)
            swap_TriangleVertices(tr1);
    } else if ((less_equal(Y3, 0) && greater(Y1, 0) && greater(Y2, 0)) || (greater(Y3, 0) && less(Y1, 0) && less(Y2, 0))) {
        rotate_TriangleVertices(tr2, 1);
        float Y = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v1);
        if (Y < 0)
            swap_TriangleVertices(tr1);
    }*/
}

//looks up if intersection between two triangles happens
bool lookup_intersection(Triangle_t &tr1, Triangle_t &tr2) {
    if (!boundingboxes_overlap(tr1, tr2))
        return false; //no intersection
    
    assert(tr1.valid() && tr2.valid());

    //calculate distances between one triangle's plane and other triangle's vertices considering orientability 
    count_vdistance(tr1, tr2);
    count_vdistance(tr2, tr1);
    
    //analyse these distances
    if (allDistSameSigned(tr1) || allDistSameSigned(tr2))
        return false; //no intersection
    if (allDistZero(tr1)) {
        //coplanar
    }

    //make_consistentTriangleOrientation(tr1, tr2);  maybe useful


    //under construction


}

