#include <iostream>

#include "Point.h"

#include "Triangle.h"

#include <string>




const Point GLOBAL_POINT(1, 1);

const string WRONG_INPUT = "Íåêîððåêòíûé ââîä êîîðäèíàò";

int main() {
    setlocale(LC_ALL, "Ru");
    double x1, y1, x2, y2;
    try {
        cout << "Ââåäèòå êîîðäèíàòû ïåðâîé òî÷êè: x1 and y1 > " << endl;
        cin >> x1 >> y1;
        if (!cin) {
            throw(WRONG_INPUT);
        }
        cout << "Ââåäèòå êîîðäèíàòû âòîðîé òî÷êè: x2 and y2 > " << endl;
        cin >> x2 >> y2;
        if (!cin) {
            throw(WRONG_INPUT);
        }

    }
    catch (const string thr) {
        cerr << "Error: " << thr << endl;
        return EXIT_FAILURE;

    }
    
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3 = p2;

    cout << "Point 1: " << p1 << endl;
    cout << "Point 2: " << p2 << endl;
    cout << "Point 3: " << p3 << endl;

  
    Triangle t1;
    Triangle t2(p1, p2, p3);
    Triangle t3 = t2;

    cout << "Triangle 1: " << t1 << endl;
    cout << "Triangle 2: " << t2 << endl;
    cout << "Triangle 3: " << t3 << endl;

    t1.setA(p2);
    t1.setB(p3);
    t1.setC(p1);
    cout << "Triangle 1 ïîñëå setA, setB, setC: " << t1 << endl;

    cout << "Ïåðèìåòð Triangle 2: " << t2.getPerimeter() << endl;

    if (t2 == t3) {
        cout << "Triangle 2 è Triangle 3 èìåþò îäèíàêîâûå êîîðäèíàòû." << endl;
    }
    else {
        cout << "Triangle 2 è Triangle 3 íå èìåþò îäèíàêîâûõ êîîðäèíàò." << endl;
    }

    if (t1 < t2) {
        cout << "Triangle 1 ìåíüøå ïî ïëîùàäè, ÷åì Triangle 2." << endl;
    }
    else {
        cout << "Triangle 1 íå ìåíüøå ïî ïëîùàäè, ÷åì Triangle 2." << endl;
    }

    Triangle t4 = t2 + 2.0;
    cout << "Triangle 4 (Triangle 2 + 2.0): " << t4 << endl;

    t2 += 3.0;
    cout << "Triangle 2 ïîñëå += 3.0: " << t2 << endl;

    return 0;
}
