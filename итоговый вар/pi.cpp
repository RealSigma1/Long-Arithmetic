#include "ln.h"
#include <iostream>
#include <chrono>

using namespace LongMath;

LongNumber computePi(int digits) {
    if (digits < 1) {
        digits = 1;
    }

    LongNumber pi(0, digits);
    LongNumber n0{1, digits};      
    LongNumber n(16, digits);      

    LongNumber a0{4, digits};
    LongNumber b0{2, digits};
    LongNumber c0{1, digits};
    LongNumber d0{1, digits};

    LongNumber a(1, digits);
    LongNumber b(4, digits);
    LongNumber c(5, digits);
    LongNumber d(6, digits);

    LongNumber eight(8, digits);

    for (int k = 0; k < digits; ++k) {
        pi = pi + n0 * (a0 / a - b0 / b - c0 / c - d0 / d);
        n0 = n0 / n;   

        a = a + eight;
        b = b + eight;
        c = c + eight;
        d = d + eight;
    }

    return pi;
}

int main() {
    int decimalDigits;
    std::cout << "Enter the number of decimal places: ";
    std::cin >> decimalDigits;
    
    int digits = decimalDigits;

    auto start = std::chrono::high_resolution_clock::now();
    LongNumber pi = computePi(digits);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "pi = " << pi.toStr(decimalDigits) << std::endl;
    std::cout << "Computation time: " << elapsed.count() << " seconds." << std::endl;
    
    return 0;
}
