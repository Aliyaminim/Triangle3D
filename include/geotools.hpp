#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "primitives.hpp"
#include "mathtools.hpp"
#include "floatcompar.hpp"

//checks if bounding boxes overlap
/* min and max don't work with initializer_list, it seems that in std::min({tr1.v1.x, tr1.v2.x, tr1.v3.x})
std::min() is provided with only one argument which is tried to be constructed by Point_t constructor */
bool boundingboxes_overlap(const Triangle_t &tr1, const Triangle_t &tr2) {
    assert(tr1.valid() && tr2.valid());
    Point_t Amin{std::min(tr1.v1.x, std::min(tr1.v2.x, tr1.v3.x)), std::min(tr1.v1.y, std::min(tr1.v2.y, tr1.v3.y)), 
                std::min(tr1.v1.z, std::min(tr1.v2.z, tr1.v3.z))};
    Point_t Amax{std::max(tr1.v1.x, std::max(tr1.v2.x, tr1.v3.x)), std::max(tr1.v1.y, std::max(tr1.v2.y, tr1.v3.y)), 
                std::max(tr1.v1.z, std::max(tr1.v2.z, tr1.v3.z))};

    Point_t Bmin{std::min(tr2.v1.x, std::min(tr2.v2.x, tr2.v3.x)), std::min(tr2.v1.y, std::min(tr2.v2.y, tr2.v3.y)), 
                std::min(tr2.v1.z, std::min(tr2.v2.z, tr2.v3.z))};
    Point_t Bmax{std::max(tr2.v1.x, std::max(tr2.v2.x, tr2.v3.x)), std::max(tr2.v1.y, std::max(tr2.v2.y, tr2.v3.y)), 
                std::max(tr2.v1.z, std::max(tr2.v2.z, tr2.v3.z))};

    /* preferrable option
    Point_t Amin{std::min({tr1.v1.x, tr1.v2.x, tr1.v3.x}), std::min({tr1.v1.y, tr1.v2.y, tr1.v3.y}), 
                std::min({tr1.v1.z, tr1.v2.z, tr1.v3.z})};
    Point_t Amax{std::max({tr1.v1.x, tr1.v2.x, tr1.v3.x}), std::max({tr1.v1.y, tr1.v2.y, tr1.v3.y}), 
                std::max({tr1.v1.z, tr1.v2.z, tr1.v3.z})};

    Point_t Bmin{std::min({tr2.v1.x, tr2.v2.x, tr2.v3.x}), std::min({tr2.v1.y, tr2.v2.y, tr2.v3.y}), 
                std::min({tr2.v1.z, tr2.v2.z, tr2.v3.z})};
    Point_t Bmax{std::max({tr2.v1.x, tr2.v2.x, tr2.v3.x}), std::max({tr2.v1.y, tr2.v2.y, tr2.v3.y}), 
                std::max({tr2.v1.z, tr2.v2.z, tr2.v3.z})};*/
    
    if ((Bmin.x > Amax.x) || (Bmin.y > Amax.y) || (Bmin.z > Amax.z) 
        || (Amin.x > Bmax.x) || (Amin.y > Bmax.y) || (Amin.z >Bmax.z))
        return false; //no intersect
    else 
        return true;  
}

// rotates vertices about a given triangle num times preserving the order
void rotate_TriangleVertices(Triangle_t &tr, int num) {
    assert(tr.valid());
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
    assert(tr.valid());
    Point_t temp = tr.v2;
    tr.v2 = tr.v3;
    tr.v3 = temp;
    for (int i = 0; i < 3; ++i) 
        tr.normal.drc_vec[i] = (-1) * tr.normal.drc_vec[i];
    return;
}

//calculates distances between tr1's plane and tr2's vertices considering orientability 
void count_vdistance(const Triangle_t &tr1, Triangle_t &tr2) { 
    assert(tr1.valid() && tr2.valid());
    tr2.vdistance[0] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v1);
    tr2.vdistance[1] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v2);
    tr2.vdistance[2] = determinant3x3(tr1.v1, tr1.v2, tr1.v3, tr2.v3);
}

//checks if all distances between triangle's vertices and given plane are same signed
bool allDistSameSigned(const Triangle_t &tr) {
    assert(tr.valid());
    return ((greater(tr.vdistance[0], 0) && greater(tr.vdistance[1], 0) && greater(tr.vdistance[2], 0)) 
        || (less(tr.vdistance[0], 0) && less(tr.vdistance[1], 0) && less(tr.vdistance[2], 0)));
}

//checks if all distances between triangle's vertices and given plane are zero
bool allDistZero(const Triangle_t &tr) {
    assert(tr.valid());
    return (is_zero(tr.vdistance[0]) && is_zero(tr.vdistance[1]) && is_zero(tr.vdistance[2]));
}

/*void make_consistentTriangleOrientation(Triangle_t &tr1, Triangle_t &tr2) {
    //making a consistent form of relative position of triangles:
    //vertix v1 of each triangle is the only vertix in positive subspace of the other triangle's plane
    if ((less(Y5, 0) && greater(Y4, 0) && greater(Y6, 0)) || (greater(Y5, 0) && less(Y4, 0) && less(Y6,0))) {
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
    }
}*/
   

//checks if given segment intersects triangle, using method from Geometric tools for Computer Graphics(P.J.Schneider, D.H.Eberly)
bool SegmentTriangleIntersect(const Triangle_t &tr, const Segment_t &seg) {
    /* parametric representation of seg = barycentric coordinates of any point in triangle
                            P + t * vec(d) = (1 − (u + v))* V1 + u * V2 + v * V3  */
    assert(tr.valid() && seg.valid());
    Line_t e1(tr.v1, tr.v2, 0);
    Line_t e2(tr.v1, tr.v3, 0);

    Line_t p = seg.cross(e2);
    float tmp = p.dot(e1);
    assert(!std::isnan(tmp));

    if (is_zero(tmp))
        return false;

    assert(seg.r0.valid());
    Line_t s (tr.v1, seg.r0, 0);
    float u = s.dot(p) / tmp;
    assert(!std::isnan(u));
    if (less(u, 0) || greater(u, 1))
        return false;
    
    Line_t q = s.cross(e1);
    float v = seg.dot(q) / tmp;
    assert(!std::isnan(v));
    if (less(v, 0) || greater(v, 1))
        return false;

    if((u + v) > 1)
        return false;

    float t = e2.dot(q) / tmp;
    assert(!std::isnan(t));
    if (less(t, 0) || greater(t, 1))
        return false;

    float x_ = seg.r0.x + t * seg.drc_vec[0];
    float y_ = seg.r0.y + t * seg.drc_vec[1];
    float z_ = seg.r0.z + t * seg.drc_vec[2];

    Point_t intersection_point(x_, y_, z_); //maybe useful

    return true; //return intersection_point;
}

//checks if any of the segments of second triangle intersects first triangle
bool checkAll_SegmentTriangleIntersect(const Triangle_t &tr1, const Triangle_t &tr2) {
    assert(tr1.valid() && tr2.valid());
    if (SegmentTriangleIntersect(tr1, {tr2.v1, tr2.v2, 1})) 
        return true;
    else if (SegmentTriangleIntersect(tr1, {tr2.v1, tr2.v3, 1})) 
        return true;
    else if (SegmentTriangleIntersect(tr1, {tr2.v2, tr2.v3, 1}))
        return true;
    else 
        return false;
}

//checks if intersection occurs between given edges
bool edgeEdgeIntersection(const Point_t &a1, const Point_t &b1, const Point_t &a2, const Point_t &b2) {
    Line_t a1b1{a1, b1, 0};
    Line_t a2b2{a2, b2, 0};

    Line_t b1a2{b1, a2, 0};
    Line_t b1b2{b1, b2, 0};

    Line_t cp1 = a1b1.cross(b1a2);
    Line_t cp2 = a1b1.cross(b1b2);

    if (cp1.dot(cp2) > 0)
        return 0;
    
    Line_t b2a1{b2, a1, 0};
    Line_t b2b1{b2, b1, 0};

    cp1 = a2b2.cross(b2a1);
    cp2 = a2b2.cross(b2b1);
    if (cp1.dot(cp2) > 0)
        return 0;
    
    return 1;
}

// checks if vertix lies within a coplanar triangle
bool vertixliesWithincoplanarTriangle(const Point_t &vertix, const Triangle_t &tr) {
    assert(vertix.valid() && tr.valid());			
    Line_t a1b1{tr.v1, tr.v2, 0};
    Line_t b1c1{tr.v2, tr.v3, 0};
    Line_t c1a1{tr.v3, tr.v1, 0};

    Line_t N1 = a1b1.cross(tr.normal);
    Line_t N2 = b1c1.cross(tr.normal);
    Line_t N3 = c1a1.cross(tr.normal);

    Line_t a1p{tr.v1, vertix, 0};
    Line_t b1p{tr.v2, vertix, 0};
    Line_t c1p{tr.v3, vertix, 0};

    float S1 = a1p.dot(N1);
    float S2 = b1p.dot(N2);
    float S3 = c1p.dot(N3);

    if ((greater(S1, 0) && greater(S2, 0) && greater(S3, 0)) || (less(S1, 0) && less(S2, 0) && less(S3, 0)))
        //vertix is inside triangle
        return 1;
    else
        return 0;
}

//checks if intersection occurs between coplanar triangles
bool find_intersection_coplanarTriangles(const Triangle_t &tr1, const Triangle_t &tr2) {
    //test if any tr1 edges cross tr2 edges
    assert(tr1.valid() && tr2.valid());

    if (edgeEdgeIntersection(tr1.v1, tr1.v2, tr2.v1, tr2.v2) ||
        edgeEdgeIntersection(tr1.v1, tr1.v2, tr2.v2, tr2.v3) ||
        edgeEdgeIntersection(tr1.v1, tr1.v2, tr2.v3, tr2.v1) ||
        edgeEdgeIntersection(tr1.v2, tr1.v3, tr2.v1, tr2.v2) ||
        edgeEdgeIntersection(tr1.v2, tr1.v3, tr2.v2, tr2.v3) ||
        edgeEdgeIntersection(tr1.v2, tr1.v3, tr2.v3, tr2.v1) ||
        edgeEdgeIntersection(tr1.v3, tr1.v1, tr2.v1, tr2.v2) ||
	    edgeEdgeIntersection(tr1.v3, tr1.v1, tr2.v2, tr2.v3) ||	
        edgeEdgeIntersection(tr1.v3, tr1.v1, tr2.v3, tr2.v1))
        return 1;

    if (vertixliesWithincoplanarTriangle(tr1.v1, tr2))
        return 1;
    if (vertixliesWithincoplanarTriangle(tr2.v1, tr1))
        return 1;

    return 0; //no intersection of coplanar triangles
}


//looks up if intersection between two triangles happens
bool lookup_intersection(Triangle_t &tr1, Triangle_t &tr2) {
    assert(tr1.valid() && tr2.valid());
    if (!boundingboxes_overlap(tr1, tr2))
        return false; //no intersection

    //calculate distances between one triangle's plane and other triangle's vertices considering orientability 
    count_vdistance(tr1, tr2);
    count_vdistance(tr2, tr1);
    
    //analyse these distances
    if (allDistSameSigned(tr1) || allDistSameSigned(tr2))
        return false; //no intersection
    if (allDistZero(tr1)) {
        //coplanar
        return find_intersection_coplanarTriangles(tr1, tr2);
    }
    
    return (checkAll_SegmentTriangleIntersect(tr1, tr2) || checkAll_SegmentTriangleIntersect(tr2, tr1));
}