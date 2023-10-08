#pragma once

static float flt_tolerance = 0.00001;

//(a < b) return 1, (a == b) return 0, (a > b) return -1; using relative epsilon comparison
int float_comparator(float a, float b) {
    auto diff = std::abs(a-b);

    if (diff < flt_tolerance)
        return 0;
    else if (diff < std::max(std::abs(a), std::abs(b)) * flt_tolerance)
        return 0;
    else if (a < b)
        return 1;
    else if (a > b)
        return -1;
}
