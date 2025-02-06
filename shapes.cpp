//  File:           shapes.cpp
//  Description:    Defines all of the formulas by shape for use in main
//  Author:         Thomas Sotherland
//  Course:         CS 3350, Spring 2025
//
//
#include "shapes.h"
#include <cmath>

const double PI = 3.14159265358979323846;

// Triangle implementations
Triangle::Triangle(int s1, int s2, int s3) : Polygon(s1), side2(s2), side3(s3) {}

double Triangle::area() {
    // Heron's formula
    double s = (side1 + side2 + side3) / 2.0;
    return sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

double Triangle::perimeter() {
    return side1 + side2 + side3;
}

// IsoscelesTriangle implementations
IsoscelesTriangle::IsoscelesTriangle(int equalSides, int base)
    : Triangle(equalSides, equalSides, base) {
}

double IsoscelesTriangle::area() {
    return Triangle::area();
}

double IsoscelesTriangle::perimeter() {
    return Triangle::perimeter();
}

// Equilateral Triangle implementations
EquilateralTriangle::EquilateralTriangle(int side)
    : Triangle(side, side, side) {
}

double EquilateralTriangle::area() {
    return (sqrt(3) / 4) * side1 * side1;
}

double EquilateralTriangle::perimeter() {
    return 3 * side1;
}

// Quadrilateral implementations
Quadrilateral::Quadrilateral(int s1, int s2, int s3, int s4, double ang)
    : Polygon(s1), side2(s2), side3(s3), side4(s4), angle(ang) {
}

double Quadrilateral::area() {
    // Using triangulation method with SAS formula
    double radians = angle * PI / 180.0;
    double area1 = 0.5 * side1 * side2 * sin(radians);

    // Calculate the diagonal using law of cosines
    double diagonal = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(radians));

    // Calculate the remaining angle using law of cosines
    double cos_remaining = (side3 * side3 + diagonal * diagonal - side4 * side4) / (2 * side3 * diagonal);
    double remaining_angle = acos(cos_remaining);

    // Calculate area of second triangle
    double area2 = 0.5 * side3 * diagonal * sin(remaining_angle);

    return area1 + area2;
}

double Quadrilateral::perimeter() {
    return side1 + side2 + side3 + side4;
}

// Rectangle implementations
Rectangle::Rectangle(int length, int width)
    : Quadrilateral(length, width, length, width, 90) {
}

double Rectangle::area() {
    return side1 * side2;
}

double Rectangle::perimeter() {
    return 2 * (side1 + side2);
}

// Square implementations
Square::Square(int side)
    : Rectangle(side, side) {
}

double Square::area() {
    return side1 * side1;
}

double Square::perimeter() {
    return 4 * side1;
}

// Pentagon implementations
Pentagon::Pentagon(int side)
    : Polygon(side) {
}

double Pentagon::area() {
    return (5 * side1 * side1 * tan(54 * PI / 180)) / 4;
}

double Pentagon::perimeter() {
    return 5 * side1;
}

// Hexagon implementations
Hexagon::Hexagon(int side)
    : Polygon(side) {
}

double Hexagon::area() {
    return (3 * sqrt(3) * side1 * side1) / 2;
}

double Hexagon::perimeter() {
    return 6 * side1;
}

// Octagon implementations
Octagon::Octagon(int side)
    : Polygon(side) {
}

double Octagon::area() {
    return 2 * side1 * side1 * (1 + sqrt(2));
}

double Octagon::perimeter() {
    return 8 * side1;
}