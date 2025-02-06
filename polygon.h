//  File:           polygon.h
//  Description:    Defines the class Polygon for inheritance
//  Author:         Thomas Sotherland
//  Course:         CS 3350, Spring 2025
//
//
#pragma once
#ifndef POLYGON_H
#define POLYGON_H

class Polygon {
protected:
    int side1;

public:
    Polygon(int s1 = 0) : side1(s1) {}
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual ~Polygon() {}
};

#endif