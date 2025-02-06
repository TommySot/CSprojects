//  File:           main.cpp
//  Description:    Class declarations by shape inheriting from polygon
//                  needed for the functions in shapes.cpp to work properly
//  Author:         Thomas Sotherland
//  Course:         CS 3350, Spring 2025
//
//
#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#include "polygon.h"
#include <cmath>

class Triangle : public Polygon {
protected:
    int side2;
    int side3;
public:
    Triangle(int s1 = 0, int s2 = 0, int s3 = 0);
    virtual double area() override;
    virtual double perimeter() override;
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int equalSides = 0, int base = 0);
    double area() override;
    double perimeter() override;
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side = 0);
    double area() override;
    double perimeter() override;
};

class Quadrilateral : public Polygon {
protected:
    int side2;
    int side3;
    int side4;
    double angle;  // angle between side1 and side2 in degrees
public:
    Quadrilateral(int s1 = 0, int s2 = 0, int s3 = 0, int s4 = 0, double ang = 0);
    virtual double area() override;
    virtual double perimeter() override;
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(int length = 0, int width = 0);
    double area() override;
    double perimeter() override;
};

class Square : public Rectangle {
public:
    Square(int side = 0);
    double area() override;
    double perimeter() override;
};

class Pentagon : public Polygon {
public:
    Pentagon(int side = 0);
    double area() override;
    double perimeter() override;
};

class Hexagon : public Polygon {
public:
    Hexagon(int side = 0);
    double area() override;
    double perimeter() override;
};

class Octagon : public Polygon {
public:
    Octagon(int side = 0);
    double area() override;
    double perimeter() override;
};

#endif