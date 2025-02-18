//LongNumber.h
#ifndef LONGNUMBER_H
#define LONGNUMBER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace LongMath {
    class LongNumber {
    private:
        std::vector<bool> bits;  
        unsigned point;         
        unsigned precision;     
        bool sign;               

        void deleteZeros();
        int magnitude() const;
        void setPrecision(int precision);
        void alignPoints(LongNumber& other);

        double binaryToDecimal() const;
        std::string toDecimalString(int accuracy = 6) const;

    public:
        LongNumber();
        bool isZero() const;
        void truncateToPrecision();
        explicit LongNumber(const std::string& binaryString);
        explicit LongNumber(double value);
        LongNumber(double value, int _precision);

        std::string toBinaryString() const;
        std::string toBinaryString(int accuracy) const;

        friend std::ostream &operator<<(std::ostream &, const LongNumber &);

        LongNumber operator-() const;

        friend bool operator==(const LongNumber &, const LongNumber &);
        friend bool operator<(const LongNumber &, const LongNumber &);
        friend bool operator>(const LongNumber &, const LongNumber &);
        friend bool operator<=(const LongNumber &, const LongNumber &);
        friend bool operator>=(const LongNumber &, const LongNumber &);
        friend bool operator!=(const LongNumber &, const LongNumber &);

        friend LongNumber operator-(const LongNumber &, const LongNumber &);
        friend LongNumber operator+(const LongNumber &, const LongNumber &);
        friend LongNumber operator*(const LongNumber &, const LongNumber &);
        friend LongNumber operator/(const LongNumber &, const LongNumber &);

        LongNumber &operator-=(const LongNumber &);
        LongNumber &operator+=(const LongNumber &);
        LongNumber &operator*=(const LongNumber &);
        LongNumber &operator/=(const LongNumber &);
    };

    LongNumber operator ""_ln(const char* binaryString, size_t);
}

#endif // LONGNUMBER_H