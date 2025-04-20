#include "Point.h"
#include <iostream>

using namespace std;

int main() {
    Point closestPoint;
    Point currentPoint;
    bool firstPoint = true;

    while (true) {
        input(currentPoint);

        if (currentPoint.isEqual(Point(0.0, 0.0))) {
            break;
        }

        
        if (firstPoint || currentPoint.getDistance(Point(0.0, 0.0)) < closestPoint.getDistance(Point(0.0, 0.0))) {
            closestPoint = currentPoint;
            firstPoint = false;  
        }
    }

    
    cout << "Closest point to the origin: ";
    output(closestPoint);

    return 0;
}