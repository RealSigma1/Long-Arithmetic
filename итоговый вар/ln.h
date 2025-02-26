#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>
#include <string>
#include <iostream>

namespace LongMath {
    class LongNumber {
    public:
        LongNumber();
        static LongNumber fromBin(const std::string& binary);
        explicit LongNumber(std::string);

        explicit LongNumber(int);

        LongNumber(int, int);
        LongNumber(const LongNumber& other) = default;
        ~LongNumber() = default;

        std::string toStr() const;

        std::string toStr(int) const;

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
    
	private:
        std::vector<short> bits;  
        unsigned dot;             
        unsigned prec;            
        bool neg;                

        void trim();             

        bool isZero() const;     

        int exp() const;
	};
}

LongMath::LongNumber operator ""_ln(unsigned long long);

LongMath::LongNumber operator ""_ln(long double);

LongMath::LongNumber operator"" _ln(const char* str, size_t);

#endif