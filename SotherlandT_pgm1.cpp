//  File:           SotherlandT_pgm1.cpp
//  Description:    Contains the functions that display and validate input from user
//                  and calls the functions from shapes.cpp via shapes.h for calculations
//  Author:         Thomas Sotherland
//  Course:         CS 3350, Spring 2025
//  Reflection:     I really enjoyed getting to review alot of the concepts covered in CS 2010 & 2020 when making this program.
//                  I initially had a bit of difficulty getting used to the class structure and what data types to set to public/private.
//                  I also really struggled to understand the quadrilateral formula at first as I haven't taken geometry in a good few years.
//                  A few things I could've done differently are the class declarations for the various shapes as I had them inherit from
//                  newer classes rather than just pulling from polygon and overriding. I also really should've started this program earlier
//                  in the week as it ended up being quite a bit more difficult and had new error codes I hadn't run into before. Namely
//                  issues with class inheritance and formulas calculating out very strangely.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
#include <cmath>
#include "shapes.h"

using namespace std;

// Function prototypes
int getUserChoice();
Polygon* createPolygon(int);
void showAreaPerimeter(Polygon*);
bool isNumeric(string);
int convert2Numeric(string);
bool getValidNumber(const string& prompt, double& number);
bool getValidNumber(const string& prompt, int& number);
bool getContinueChoice();

// Function definitions
bool isNumeric(string str) {
    if (str.empty()) return false;

    bool hasDecimal = false;
    bool hasDigit = false;

    for (size_t i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-') continue;  // Allow negative numbers

        if (str[i] == '.') {
            if (hasDecimal) return false;  // More than one decimal point
            hasDecimal = true;
        }
        else if (isdigit(str[i])) {
            hasDigit = true;
        }
        else {
            return false;
        }
    }

    return hasDigit;  // Must have at least one digit
}

int convert2Numeric(string str) {
    return stoi(str);
}

void showAreaPerimeter(Polygon* p) {
    cout << fixed << setprecision(2);
    cout << "Area is: " << p->area() << endl;
    cout << "Perimeter is: " << p->perimeter() << endl;
}

bool getValidNumber(const string& prompt, double& number) {
    string input;
    if (!prompt.empty()) {
        cout << prompt;
    }
    getline(cin, input);

    if (!isNumeric(input)) {
        cout << "Error: Please enter a valid number.\n";
        return false;
    }

    number = stod(input);
    if (number <= 0) {
        cout << "Error: Please enter a positive number.\n";
        return false;
    }
    return true;
}

bool getValidNumber(const string& prompt, int& number) {
    double temp;
    if (!getValidNumber(prompt, temp)) {
        return false;
    }

    if (temp != floor(temp)) {
        cout << "Error: Please enter a whole number.\n";
        return false;
    }

    number = (int)temp;
    return true;
}

bool getContinueChoice() {
    string input;
    cout << "\nAnother [Y or N]? ";
    getline(cin, input);

    // Convert to uppercase for comparison
    for (char& c : input) {
        c = toupper(c);
    }

    if (input == "Y" || input == "YES") return true;
    if (input == "N" || input == "NO") return false;

    cout << "Please enter Y or N.\n";
    return getContinueChoice();
}

int getUserChoice() {
    string input;
    cout << "\nWhich Shape [1-9]?\n";
    cout << "1. Generic Triangle\n";
    cout << "2. Isosceles Triangle\n";
    cout << "3. Equilateral Triangle\n";
    cout << "4. Generic Quadrilateral\n";
    cout << "5. Rectangle\n";
    cout << "6. Square\n";
    cout << "7. Pentagon\n";
    cout << "8. Hexagon\n";
    cout << "9. Octagon\n";
    cout << "Enter choice (1-9): ";

    getline(cin, input);

    if (!isNumeric(input)) {
        cout << "Error: Please enter a numeric value.\n";
        return getUserChoice();
    }

    int choice = convert2Numeric(input);
    if (choice < 1 || choice > 9) {
        cout << "Error: Please enter a value between 1 and 9.\n";
        return getUserChoice();
    }

    return choice;
}

Polygon* createPolygon(int choice) {
    int s1, s2, s3, s4;
    double angle;

    switch (choice) {
    case 1: // Generic Triangle
        do {
            cout << "Enter first side: ";
            if (!getValidNumber("", s1)) continue;
            cout << "Enter second side: ";
            if (!getValidNumber("", s2)) continue;
            cout << "Enter third side: ";
            if (!getValidNumber("", s3)) continue;

            // Check triangle inequality
            if (s1 + s2 <= s3 || s2 + s3 <= s1 || s1 + s3 <= s2) {
                cout << "Error: These sides cannot form a triangle.\n";
                continue;
            }
            return new Triangle(s1, s2, s3);
        } while (true);

    case 2: // Isosceles Triangle
        do {
            cout << "Enter equal sides: ";
            if (!getValidNumber("", s1)) continue;
            cout << "Enter base: ";
            if (!getValidNumber("", s2)) continue;

            // Checks if shape is possible
            if (2 * s1 <= s2) {
                cout << "Error: These sides cannot form an isosceles triangle.\n";
                continue;
            }
            return new IsoscelesTriangle(s1, s2);
        } while (true);

    case 3: // Equilateral Triangle
        if (getValidNumber("Enter side length: ", s1)) {
            return new EquilateralTriangle(s1);
        }
        return createPolygon(choice);

    case 4: // Generic Quadrilateral
        do {
            cout << "Enter first side: ";
            if (!getValidNumber("", s1)) continue;
            cout << "Enter second side: ";
            if (!getValidNumber("", s2)) continue;
            cout << "Enter third side: ";
            if (!getValidNumber("", s3)) continue;
            cout << "Enter fourth side: ";
            if (!getValidNumber("", s4)) continue;
            cout << "Enter angle between first two sides (degrees): ";
            if (!getValidNumber("", angle)) continue;

            if (angle <= 0 || angle >= 180) {
                cout << "Error: Angle must be between 0 and 180 degrees.\n";
                continue;
            }
            return new Quadrilateral(s1, s2, s3, s4, angle);
        } while (true);

    case 5: // Rectangle
        do {
            cout << "Enter length: ";
            if (!getValidNumber("", s1)) continue;
            cout << "Enter width: ";
            if (!getValidNumber("", s2)) continue;
            return new Rectangle(s1, s2);
        } while (true);

    case 6: // Square
        if (getValidNumber("Enter side length: ", s1)) {
            return new Square(s1);
        }
        return createPolygon(choice);

    case 7: // Pentagon
        if (getValidNumber("Enter side length: ", s1)) {
            return new Pentagon(s1);
        }
        return createPolygon(choice);

    case 8: // Hexagon
        if (getValidNumber("Enter side length: ", s1)) {
            return new Hexagon(s1);
        }
        return createPolygon(choice);

    case 9: // Octagon
        if (getValidNumber("Enter side length: ", s1)) {
            return new Octagon(s1);
        }
        return createPolygon(choice);
    }

    return nullptr;
}

int main() {
    do {
        int choice = getUserChoice();
        Polygon* shape = createPolygon(choice);
        if (shape != nullptr) {
            showAreaPerimeter(shape);
            delete shape;
        }
    } while (getContinueChoice());

    return 0;
}