#include "Treagle.h"

using namespace std;

#include <iostream>

#include "Point.h"


int main() {
    Triangle triangle(Point(0.0, 0.0), Point(1.0, 0.0), Point(0.0, 1.0));
    output(triangle);
    std::cout << "Perimeter: " << triangle.getPerimeter() << std::endl;

    Triangle triangleCopy(triangle);
    if (triangle.isEqual(triangleCopy)) {
        std::cout << "Triangles are equal." << std::endl;
    }
    else {
        std::cout << "Triangles are not equal." << std::endl;
    }

    triangle.move(2.0, 2.0);
    output(triangle);
    std::cout << "Perimeter: " << triangle.getPerimeter() << std::endl;

    if (isEqualSquare(triangle, triangleCopy)) {
        std::cout << "Triangles have equal area." << std::endl;
    }
    else {
        std::cout << "Triangles do not have equal area." << std::endl;
    }

    return 0;
}