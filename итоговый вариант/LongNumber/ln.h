#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>
#include <string>

namespace LongMath {
    class LongNumber {
    private:
        std::vector<short> digits;
        unsigned point;
        unsigned precision;
        bool sign;

        void deleteZeros();

        bool isZero() const;

        int magnitude() const;
		

    public:
        LongNumber();
		static LongNumber binaryToLongNumber(const std::string& binary);
        explicit LongNumber(std::string);

        explicit LongNumber(int);

        LongNumber(int, int);
		LongNumber(const LongNumber& other) = default;
		~LongNumber() = default;
	
        std::string toString() const;

        std::string toString(int) const;

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
}

LongMath::LongNumber operator ""_ln(unsigned long long);

LongMath::LongNumber operator ""_ln(long double);
 
LongMath::LongNumber operator"" _ln(const char* str, size_t);
#endif //LONGMATH_LONGNUMBER_H
