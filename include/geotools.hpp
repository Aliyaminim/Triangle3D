#pragma once

#include <iostream>
#include "primitives.hpp"

bool boundingboxes_overlap(const Triangle_t &tr1, const Triangle_t &tr2) {
    Point_t Amin{std::min(tr1.v1.x, std::min(tr1.v2.x, tr1.v3.x)), std::min(tr1.v1.y, std::min(tr1.v2.y, tr1.v3.y)), 
                std::min(tr1.v1.z, std::min(tr1.v2.z, tr1.v3.z))};
    Point_t Amax{std::max(tr1.v1.x, std::max(tr1.v2.x, tr1.v3.x)), std::max(tr1.v1.y, std::max(tr1.v2.y, tr1.v3.y)), 
                std::max(tr1.v1.z, std::max(tr1.v2.z, tr1.v3.z))};

    Point_t Bmin{std::min(tr2.v1.x, std::min(tr2.v2.x, tr2.v3.x)), std::min(tr2.v1.y, std::min(tr2.v2.y, tr2.v3.y)), 
                std::min(tr2.v1.z, std::min(tr2.v2.z, tr2.v3.z))};
    Point_t Bmax{std::max(tr2.v1.x, std::max(tr2.v2.x, tr2.v3.x)), std::max(tr2.v1.y, std::max(tr2.v2.y, tr2.v3.y)), 
                std::max(tr2.v1.z, std::max(tr2.v2.z, tr2.v3.z))};
    
    if ((Bmin.x > Amax.x) || (Bmin.y > Amax.y) || (Bmin.z > Amax.z) 
        || (Amin.x > Bmax.x) || (Amin.y > Bmax.y) || (Amin.z >Bmax.z))
        return false; //no intersect
    else 
        return true;  
}