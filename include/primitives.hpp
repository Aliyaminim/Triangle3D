/*
Нам понадобятся:
• Структуры для двумерной точки, отрезка, треугольника, полигона.
• Важный инсайт: координаты лучше сразу закладывать FP.
• Это будут типы в нашей программе.
• Выделим операции над объектами этих типов.
• Пересечение отрезков, взаимоположение точки и отрезка, построение
полигона как выпуклой оболочки множества точек, вычисление площади
полигона, вероятно что-то ещё....
• Это будут методы классов
*/
#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <array>

extern float flt_tolerance;
//#define inter_area_width 100.0

class Point_t {
public:
    float x = NAN, y = NAN, z = NAN;

    //constructor
    explicit Point_t(float x_, float y_, float z_): x(x_), y(y_), z(z_) {} 
    Point_t() = default;

    //operator =

    bool valid() const { return !(std::isnan(x) || std::isnan(y) || std::isnan(z)); }

    bool equal (const Point_t &rhs) const {
        assert(valid() && rhs.valid());
        
        //relative epsilon comparisons
        auto diff_x = std::abs(x - rhs.x);
        auto diff_y = std::abs(y - rhs.y);
        auto diff_z = std::abs(z - rhs.z);

        if ((diff_x < flt_tolerance) && (diff_y < flt_tolerance) && (diff_z < flt_tolerance))
            return true;
        else {
            bool cond_x = (diff_x < std::max(std::abs(x), std::abs(rhs.x)) * flt_tolerance);
            bool cond_y = (diff_y < std::max(std::abs(y), std::abs(rhs.y)) * flt_tolerance);
            bool cond_z = (diff_z < std::max(std::abs(z), std::abs(rhs.z)) * flt_tolerance);
            return (cond_x && cond_y && cond_z);
        }
    }

    void print() const { std::cout << "(" << x << " ; " << y << " ; " << z << ")"; }
};

class Line_t {
    Point_t r0;
    std::array<float, 3> drc_vec{NAN, NAN, NAN};

public:
    //constructor, is line direction strict, copy of point_t, 
    explicit Line_t(const Point_t &p1, const Point_t &p2): r0(p1) {
        drc_vec[0] = p2.x - p1.x;
        drc_vec[1] = p2.y - p1.y;
        drc_vec[2] = p2.z - p1.z;
    } 

    bool valid() const {
        return !((!r0.valid()) || std::isnan(drc_vec[0]) || std::isnan(drc_vec[1]) 
                               || std::isnan(drc_vec[2]));
    }
};

class Triangle_t {
public:
    Point_t v1, v2, v3;
    //constructor
    explicit Triangle_t(const Point_t &v1_, const Point_t &v2_, const Point_t &v3_) : v1(v1_), v2(v2_),
                                                                             v3(v3_) {}
    bool valid() const { return (v1.valid() && v2.valid() && v3.valid());}
};