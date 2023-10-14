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
#include "floatcompar.hpp"

//#define inter_area_width 100.0

class Point_t {
public:
    float x = NAN, y = NAN, z = NAN;

    //constructor
    explicit Point_t(float x_, float y_, float z_): x(x_), y(y_), z(z_) {} 
    Point_t() = default;

    //operator = default

    bool valid() const { return !(std::isnan(x) || std::isnan(y) || std::isnan(z)); }

    bool equal_point (const Point_t &rhs) const {
        assert(valid() && rhs.valid());      
        return (equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z));
    }

    void set (const float x_, const float y_, const float z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    void print() const { std::cout << "(" << x << " ; " << y << " ; " << z << ")"; }
};

class Line_t { //also using this class for segments and vectors

public:
    Point_t r0;
    std::array<float, 3> drc_vec;

    //constructor
    Line_t(const Point_t &p1, const Point_t &p2): r0(p1) {
        drc_vec[0] = p2.x - p1.x;
        drc_vec[1] = p2.y - p1.y;
        drc_vec[2] = p2.z - p1.z;

        float len = std::hypot(drc_vec[0], drc_vec[1], drc_vec[2]);

        for (int i = 0; i < 3; ++i)
            drc_vec[i] /= len; 
    } 

    //constructor mostly for vectors
    explicit Line_t(float x, float y, float z) {
        float len = std::hypot(x, y, z);
        drc_vec[0] = x / len;
        drc_vec[1] = y / len;
        drc_vec[2] = z / len;
    }

    Line_t() = default;

    bool valid() const {
        return r0.valid() && !(std::isnan(drc_vec[0]) || std::isnan(drc_vec[1]) 
                               || std::isnan(drc_vec[2]));
    }

    void set(float x_, float y_, float z_) {
        float len = std::hypot(x_, y_, z_);
        drc_vec[0] = x_ / len;
        drc_vec[1] = y_ / len;
        drc_vec[2] = z_ / len;
    }

    Line_t cross(const Line_t &line) const {
        float x = drc_vec[1] * line.drc_vec[2] - drc_vec[2] * line.drc_vec[1];
        float y = drc_vec[2] * line.drc_vec[0] - drc_vec[0] * line.drc_vec[2];
        float z = drc_vec[0] * line.drc_vec[1] - drc_vec[1] * line.drc_vec[0];

        Line_t res(x, y, z);
        return res;
    }

    float dot(const Line_t &line) const {
        return (drc_vec[0] * line.drc_vec[0]) + (drc_vec[1] * line.drc_vec[1]) + (drc_vec[2] * line.drc_vec[2]);
    }
};

class Triangle_t {
    void getNormal(const Point_t &v1_, const Point_t &v2_, const Point_t &v3_) {
        float vec12[3] = {v2_.x - v1.x, v2_.y - v1_.y, v2_.z - v1_.z}; 
        float vec13[3] = {v3_.x - v1.x, v3_.y - v1_.y, v3_.z - v1_.z}; 
        float normal_[3];

        //vec12 x vec13
        normal_[0] = vec12[1]*vec13[2] - vec12[2]*vec13[1];
        normal_[1] = vec12[2]*vec13[0] - vec12[0]*vec13[2];
        normal_[2] = vec12[0]*vec13[1] - vec12[1]*vec13[0];
        float len = std::hypot(normal_[0], normal_[1], normal_[2]);

        for (int i = 0; i < 3; ++i) 
            normal_[i] /= len;

        normal.set(normal_[0], normal_[1], normal_[2]);
    }
public:
    Point_t v1, v2, v3; 
    Line_t normal{};
    std::array<float, 3> vdistance; //contains distances between this vertices and other triangle's plane

    //constructor
    explicit Triangle_t(const Point_t &v1_, const Point_t &v2_, const Point_t &v3_) : v1(v1_), v2(v2_),
                                                                             v3(v3_) {       
        getNormal(v1_, v2_, v3_);
    }

    bool valid() const { return (v1.valid() && v2.valid() && v3.valid());}
};