//test.cpp
#include <iostream>
#include "LongNumber.cpp"

using namespace LongMath;

void test_bin() {
    LongNumber a(5);
    std::string binary = a.toBinaryString(0);
    if (binary == "101.0") {
        std::cout << "Binary test OK" << std::endl;
    } else {
        std::cout << "Binary test FAIL" << std::endl;
    }

}

void test_addition() {
    LongNumber a(5), b(3);
    LongNumber result = a + b;
    if (result == LongNumber(8)) {
        std::cout << "Addition test OK" << std::endl;
    } else {
        std::cout << "Addition test FAIL" << std::endl;
    }
    std::cout << result << std::endl;
}

void test_subtraction() {
    LongNumber a(10), b(4);
    LongNumber result = a - b;
    if (result == LongNumber(6)) {
        std::cout << "Subtraction test OK" << std::endl;
    } else {
        std::cout << "Subtraction test FAIL" << std::endl;
    }
}

void test_multiplication() {
    LongNumber a(7), b(7);
    LongNumber result = a * b;
    if (result == LongNumber(49)) {
        std::cout << "Multiplication test OK" << std::endl;
    } else {
        std::cout << "Multiplication test FAIL" << std::endl;
    }
     std::cout << result << std::endl;
}

void test_division() {
    LongNumber a(20), b(5);
    LongNumber result = a / b;
    if (result == LongNumber(4)) {
        std::cout << "Division test OK" << std::endl;
    } else {
        std::cout << "Division test FAIL" << std::endl;
    }
}

void test_comparisons() {
    LongNumber a(10), b(10), c(5);
    if (a == b && a != c && a > c && c < a) {
        std::cout << "Comparison test OK" << std::endl;
    } else {
        std::cout << "Comparison test FAIL" << std::endl;
    }
}

void test_negative() {
    LongNumber a(-5), b(-3.);
    LongNumber result = a + b;
    if (result == LongNumber(-8)) {
        std::cout << "Negative test OK" << std::endl;
    } else {
        std::cout << "Negative test FAIL" << std::endl;
    }
}

int main() {
    test_negative();
    test_bin();
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_comparisons();
    return 0;
}