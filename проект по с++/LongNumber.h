//LongNumber.h
#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

namespace LongMath {
    class LongNumber {
    private:
        std::vector<bool> bits;  
        unsigned point;         
        unsigned precision;     
        bool sign;               

        void deleteZeros();

        bool isZero() const;
	
        int magnitude() const;
		void setPrecision(int precision);
		void truncateToPrecision();
    public:
        LongNumber();

        explicit LongNumber(const std::string& binaryString);

        explicit LongNumber(int value);

        LongNumber(int value, int _precision);

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
        ~LongNumber() = default;
    };
}

LongMath::LongNumber operator ""_ln(const char* binaryString, size_t);

#endif 

