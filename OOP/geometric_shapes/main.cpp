#include <iostream>

#include "Point.h"

#include "Shape.h"

#include "Parallelogram.h"

#include "Regular.h"


int main() {
    setlocale(LC_ALL, "Ru");

    Point pointA(0.0, 0.0);
    Point pointB(3.0, 4.0);

    std::cout << "Point A: " << pointA << std::endl;
    std::cout << "Point B: " << pointB << std::endl;
    std::cout << "Distance between A and B: " << pointA.getDistance(pointB) << std::endl;

    FrameRectangle frameRect(2.0, 3.0, pointA);

    std::cout << "\nFrameRectangle:" << std::endl;
    std::cout << "Width: " << frameRect.getWidth() << std::endl;
    std::cout << "Height: " << frameRect.getHeight() << std::endl;
    std::cout << "Center: " << frameRect.getPos() << std::endl;

    try {
        Regular square(pointA, Point(0.0, 4.0), Point(3.0, 4.0));
        std::cout << "\nSquare:" << std::endl;
        square.getInfo(std::cout);
        std::cout << "Area: " << square.getArea() << std::endl;
û
        std::cout << "\nAfter moving and scaling:" << std::endl;
        square.move(1.0, 2.0);
        square.scale(2.0);
        square.getInfo(std::cout);
        std::cout << "Area: " << square.getArea() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in Regular: " << e.what() << std::endl;
    }

    try {
        Parallelogram parallelogram(pointA, Point(5.0, 0.0), pointB);
        std::cout << "\nParallelogram:" << std::endl;
        parallelogram.getInfo(std::cout);
        std::cout << "Area: " << parallelogram.getArea() << std::endl;

        std::cout << "\nAfter moving and scaling:" << std::endl;
        parallelogram.move(-5.0, 2.0);
        parallelogram.scale(1.5);
        parallelogram.getInfo(std::cout);
        std::cout << "Area: " << parallelogram.getArea() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in Parallelogram: " << e.what() << std::endl;
    }

    return 0;
}
