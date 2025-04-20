#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "String.h"

int main() {
    String s0;
    String s1("Hello");

    std::cout << s1 << std::endl;
    s1[4] = 'P';
    std::cout << s1 << std::endl;

    String s2 = s1;
    std::cout << s2 << '\n';
    s2[4] = 'o';
    std::cout << s2 << '\n';
    std::cout << s1 << '\n';

    return 0;
}
