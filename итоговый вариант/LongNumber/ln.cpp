//LongNumber.cpp
#include "ln.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>


namespace LongMath {
    LongNumber::LongNumber() {
        sign = false;
        point = 0;
        digits.push_back(0);
        precision = 100;
    }

    LongNumber::LongNumber(int input) {
        point = 0;
        precision = 100;
        sign = false;

        if (input == 0) {
            digits.push_back(0);
            return;
        }

        if (input < 0) {
            sign = true;
            input = -input;
        }

        while (input > 0) {
            digits.push_back(input % 10);
            input /= 10;
        }
    }

    LongNumber::LongNumber(int input, int _precision) {
        point = 0;
        precision = _precision;
        sign = false;

        if (input == 0) {
            digits.push_back(0);
            return;
        }

        if (input < 0) {
            sign = true;
            input = -input;
        }

        while (input > 0) {
            digits.push_back(input % 10);
            input /= 10;
        }
    }

    LongNumber::LongNumber(std::string input) {
        if (input[0] == '-') {
            sign = true;
            input.erase(input.begin());
        } else {
            sign = false;
        }

        auto separator = input.find('.');

        if (separator < std::string::npos) {
            point = input.length() - separator - 1;
            input.erase(input.begin() + separator);
        } else {
            separator = input.find(',');
            if (separator < std::string::npos) {
                point = input.length() - separator - 1;
                input.erase(input.begin() + separator);
            } else {
                point = 0;
            }
        }

        precision = fmax(100, point + 10);

        auto iter = input.end();
        while (iter != input.begin()) {
            iter--;
            digits.push_back(*iter - '0');
        }

        deleteZeros();
    }

    bool LongNumber::isZero() const {
        return digits.size() == 1 && digits[0] == 0;
    }

    int LongNumber::magnitude() const {
        int magnitude = digits.size() - point;
        auto iterator = digits.end() - 1;
        while (iterator >= digits.begin() && *iterator == 0){
            magnitude--;
            iterator--;
        }
        return magnitude;
    }

    void LongNumber::deleteZeros() {
        while (point > 0 && digits.front() == 0) {
            digits.erase(digits.begin());
            --point;
        }

        while (digits.size() > point + 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    std::string LongNumber::toString() const {
        std::string number;

        if (sign) number += '-';

        for (int i = digits.size() - 1; i >= 0; --i) {

            number += static_cast<char>(digits[i] + '0');

            if (i == point) {
                number += '.';
            }
        }

        if(point == 0)
            number += '0';

        return number;
    }

    std::string LongNumber::toString(int accuracy) const {
        std::string number;

        if (sign) number += '-';

        for (int i = digits.size() - 1; i >= 0 && i >= point - accuracy; --i) {

            number += static_cast<char>(digits[i] + '0');

            if (i == point) {
                number += '.';
            }

        }

        if(point == 0)
            number += '0';

        return number;
    }
LongNumber LongNumber::binaryToLongNumber(const std::string& binary) {
    bool isNegative = false;
    std::string binaryCopy = binary;

    if (binaryCopy[0] == '-') {
        isNegative = true;
        binaryCopy.erase(binaryCopy.begin());
    }

    size_t dotPos = binaryCopy.find('.');
    std::string integerPart = binaryCopy.substr(0, dotPos);
    std::string fractionalPart = (dotPos != std::string::npos) ? binaryCopy.substr(dotPos + 1) : "";

    LongNumber result = 0_ln;  

    for (size_t i = 0; i < integerPart.length(); ++i) {
        if (integerPart[i] == '1') {
            LongNumber power = 1_ln;  
            for (size_t j = 0; j < integerPart.length() - i - 1; ++j) {
                power *= 2_ln;  
            }
            result += power;  
        }
    }

    for (size_t i = 0; i < fractionalPart.length(); ++i) {
        if (fractionalPart[i] == '1') {
            LongNumber power = 1_ln;  
            for (size_t j = 0; j <= i; ++j) {
                power /= 2_ln;  
            }
            result += power;  
        }
    }

    if (isNegative) {
        result = -result;
    }

    return result;
}
    std::ostream &operator<<(std::ostream &os, const LongNumber &number) {
        return os << number.toString();
    }

    LongNumber LongNumber::operator-() const {
        LongNumber inverse(*this);
        inverse.sign = !sign;
        return inverse;
    }

    bool operator==(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() && y.isZero()) return true;

        if (y.sign != x.sign || y.point != x.point || x.digits.size() != y.digits.size()) return false;

        for (auto i = 0; i < x.digits.size(); ++i)
            if (x.digits[i] != y.digits[i]) return false;

        return true;
    }

    bool operator!=(const LongNumber &x, const LongNumber &y) {
        return !(y == x);
    }

    bool operator<(const LongNumber &x, const LongNumber &y) {
        if (x.isZero()) {
            if (y.isZero()) {
                return false;
            }
            return !y.sign;
        } else if (y.isZero()) {
            return x.sign;
        }

        if (y.sign && x.sign) {
            return -y < -x;
        }

        if (y.sign != x.sign) {
            return !y.sign;
        }

        if (y.magnitude() != x.magnitude()) return x.magnitude() < y.magnitude();

        int i = x.digits.size() - 1;
        int j = y.digits.size() - 1;
        while (i >= 0 && j >= 0) {
            if (x.digits[i] != y.digits[j]) {
                return x.digits[i] < y.digits[j];
            }
            --i;
            --j;
        }

        return x.point < y.point;
    }

    bool operator>(const LongNumber &x, const LongNumber &y) {
        return y < x;
    }

    bool operator<=(const LongNumber &x, const LongNumber &y) {
        return x < y || x == y;
    }

    bool operator>=(const LongNumber &x, const LongNumber &y) {
        return x > y || x == y;
    }

    LongNumber operator+(const LongNumber &x, const LongNumber &y) {
        if (x.sign != y.sign) {
            if (y.sign) return x - (-y);
            return y - (-x);
        }

        LongNumber a, b;
        int precision_diff = static_cast<int>(x.point - y.point);
        if (precision_diff > 0) {
            a = x;
            b = y;
        } else {
            a = y;
            b = x;
            precision_diff = -precision_diff;
        }



        short carry = 0;
        int j;
        for (auto i = 0; i < b.digits.size() || carry != 0; ++i) {
            j = i + precision_diff;

            if (j == a.digits.size()) {
                if (i < b.digits.size()){
                    a.digits.push_back(b.digits[i] + carry);
                } else{
                    a.digits.push_back(carry);
                }

            } else {
                if (i < b.digits.size()){
                    a.digits[j] += b.digits[i] + carry;
                } else{
                    a.digits[j] += carry;
                }
            }

            if (a.digits[j] >= 10) {
                a.digits[j] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.deleteZeros();

        return a;
    }

    LongNumber& LongNumber::operator+=(const LongNumber &other) {
        return *this = *this + other;
    }

    LongNumber operator-(const LongNumber &x, const LongNumber &y) {


        if (y.sign) return x + (-y);
        else if (x.sign) return -(-x + y);
        else if (x < y) return -(y - x);

        LongNumber a{x}, b{y};
        int precisionDiff = static_cast<int>(x.point - y.point);

        if (precisionDiff > 0) {
            b.digits.insert(b.digits.begin(), precisionDiff, 0);
        } else if (precisionDiff != 0) {
            a.digits.insert(a.digits.begin(), -precisionDiff, 0);
            a.point -= precisionDiff;
        }

        short carry = 0;
        for (auto i = 0; i < a.digits.size() || carry != 0; ++i) {
            a.digits[i] -= carry;
            if (i < b.digits.size()) {
                a.digits[i] -= b.digits[i];
            }

            if (a.digits[i] < 0) {
                a.digits[i] += 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.deleteZeros();

        return a;
    }

    LongNumber& LongNumber::operator-=(const LongNumber &other) {
        return *this = *this - other;
    }

    LongNumber operator*(const LongNumber &x, const LongNumber &y) {
    if (x.isZero() || y.isZero()) return 0_ln;

    LongNumber c = 0_ln;
    c.sign = (x.sign != y.sign);
    c.point = x.point + y.point;  

    short carry;
    for (auto i = 0; i < x.digits.size(); ++i) {
        carry = 0;
        for (auto j = 0; j < y.digits.size() || carry != 0; ++j) {
            if (i + j >= c.digits.size()) {
                c.digits.push_back(0);
            }
            auto n = c.digits[i + j] + x.digits[i] * (j < y.digits.size() ? y.digits[j] : 0) + carry;

            c.digits[i + j] = n % 10;

            carry = n / 10;
        }
    }

    c.deleteZeros();

    return c;
}

    LongNumber& LongNumber::operator*=(const LongNumber &other) {
        return *this = *this * other;
    }

    LongNumber operator/(const LongNumber &x, const LongNumber &y) {
        if (y.isZero()) {
            throw std::overflow_error("division by 0");
        }

        LongNumber a{x}, b{y};

        LongNumber c = LongNumber();
        c.digits.pop_back();

        c.sign = (a.sign != b.sign);
        a.sign = false;
        b.sign = false;

        int magnitude = a.magnitude() - b.magnitude() + 1;

        while(b.magnitude() < a.magnitude()){
            b *= 10_ln;
        }


        int precision = fmax(a.precision, b.precision);

        LongNumber bd;
        short digit;
        int size = magnitude > 0 ? precision + magnitude : precision + 1;
        while (!a.isZero() && c.digits.size() <= size) {
            while (a < b) {
                c.digits.insert(c.digits.begin(), 0);
                a *= 10_ln;
            }

            digit = 1;
            bd = b;
            while (bd + b <= a && digit < 9) {
                bd += b;
                digit++;
            }

            c.digits.insert(c.digits.begin(), digit);
            a -= bd;
            a *= 10_ln;
        }

        if (magnitude <= 0){
            c.point = c.digits.size() - 1;
        } else {
            c.digits.insert(c.digits.cbegin(), magnitude, 0);
            c.point = c.digits.size() - magnitude;
        }

        c.precision = precision;

        c.deleteZeros();
        return c;
    }

    LongNumber& LongNumber::operator/=(const LongNumber &other) {
        return *this = *this / other;
    }
}

LongMath::LongNumber operator ""_ln(unsigned long long number) {
    return LongMath::LongNumber(number);
}
LongMath::LongNumber operator ""_ln(long double number) {
    return LongMath::LongNumber(std::to_string(number));
}
LongMath::LongNumber operator"" _ln(const char* str, size_t) {
        return LongMath::LongNumber::binaryToLongNumber(str);
    }