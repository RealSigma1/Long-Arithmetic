#include "LongNumber.h"

namespace LongMath {
    double LongNumber::binaryToDecimal() const {
        double result = 0.0;
        for (int i = bits.size() - 1; i >= 0; --i) {
            if (bits[i]) {
                if (i >= point) {
                    result += std::pow(2, i - point);
                } else {
                    result += std::pow(2, i - point);
                }
            }
        }
        return sign ? -result : result;
    }

    std::string LongNumber::toDecimalString(int accuracy) const {
        double decimalValue = binaryToDecimal();
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.*f", accuracy, decimalValue);
        return std::string(buffer);
    }

    LongNumber::LongNumber() {
        sign = false;
        point = 0;
        bits.push_back(false);  
        precision = 32;         
    }

    LongNumber::LongNumber(double value) {
        point = 0;
        precision = 32;
        sign = value < 0;

        if (value == 0) {
            bits.push_back(false);
            return;
        }

        value = std::abs(value);
        double fractionalPart = value - std::floor(value);
        int integerPart = static_cast<int>(std::floor(value));

        while (integerPart > 0) {
            bits.push_back(integerPart % 2);
            integerPart /= 2;
        }

        if (fractionalPart > 0) {
            point = bits.size();
            while (fractionalPart > 0 && bits.size() < precision) {
                fractionalPart *= 2;
                bits.push_back(fractionalPart >= 1);
                if (fractionalPart >= 1) {
                    fractionalPart -= 1;
                }
            }
        }
    }

    LongNumber::LongNumber(double value, int _precision) {
        point = 0;
        precision = _precision;
        sign = value < 0;

        if (value == 0) {
            bits.push_back(false);
            return;
        }

        value = std::abs(value);
        double fractionalPart = value - std::floor(value);
        int integerPart = static_cast<int>(std::floor(value));

        while (integerPart > 0) {
            bits.push_back(integerPart % 2);
            integerPart /= 2;
        }

        if (fractionalPart > 0) {
            point = bits.size();
            while (fractionalPart > 0 && bits.size() < precision) {
                fractionalPart *= 2;
                bits.push_back(fractionalPart >= 1);
                if (fractionalPart >= 1) {
                    fractionalPart -= 1;
                }
            }
        }
    }

    LongNumber::LongNumber(const std::string& binaryString) {
        sign = binaryString[0] == '-';
        auto separator = binaryString.find('.');

        if (separator != std::string::npos) {
            point = binaryString.length() - separator - 1;
            for (size_t i = separator + 1; i < binaryString.length(); ++i) {
                bits.push_back(binaryString[i] == '1');
            }
        } else {
            point = 0;
        }

        for (size_t i = sign ? 1 : 0; i < (separator == std::string::npos ? binaryString.length() : separator); ++i) {
            bits.push_back(binaryString[i] == '1');
        }

        precision = bits.size();
        deleteZeros();
    }

    bool LongNumber::isZero() const {
        return bits.size() == 1 && !bits[0];
    }

    int LongNumber::magnitude() const {
        return bits.size() - point;
    }

    void LongNumber::deleteZeros() {
        while (point > 0 && bits.front() == false) {
            bits.erase(bits.begin());
            --point;
        }

        while (bits.size() > point + 1 && bits.back() == false) {
            bits.pop_back();
        }
    }

    void LongNumber::setPrecision(int precision) {
        this->precision = precision;
        truncateToPrecision(); 
    }

    void LongNumber::truncateToPrecision() {
        if (point > precision) {
            bits.erase(bits.begin(), bits.begin() + (point - precision));
            point = precision;
        }
        deleteZeros();
    }

    void LongNumber::alignPoints(LongNumber& other) {
        int pointDiff = point - other.point;
        if (pointDiff > 0) {
            other.bits.insert(other.bits.begin(), pointDiff, false);
            other.point += pointDiff;
        } else if (pointDiff < 0) {
            bits.insert(bits.begin(), -pointDiff, false);
            point += -pointDiff;
        }
    }

    std::string LongNumber::toBinaryString() const {
        std::string binaryString;
        if (sign) binaryString += '-';

        for (int i = bits.size() - 1; i >= 0; --i) {
            if (i == point) binaryString += '.';  
            binaryString += bits[i] ? '1' : '0';
        }

        if (point == 0) binaryString += '0';  

        return binaryString;
    }

    std::string LongNumber::toBinaryString(int accuracy) const {
        std::string binaryString;

        if (sign) binaryString += '-';

        for (int i = bits.size() - 1; i >= 0 && i >= point - accuracy; --i) {
            binaryString += bits[i] ? '1' : '0';

            if (i == point) {
                binaryString += '.';
            }
        }

        if (point == 0)
            binaryString += '0';

        return binaryString;
    }

    std::ostream &operator<<(std::ostream &os, const LongNumber &number) {
        return os << number.toDecimalString();  
    }

    LongNumber LongNumber::operator-() const {
        LongNumber inverse(*this);
        inverse.sign = !sign;
        return inverse;
    }

    bool operator==(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() && y.isZero()) return true;

        if (y.sign != x.sign || y.point != x.point || x.bits.size() != y.bits.size()) return false;

        for (auto i = 0; i < x.bits.size(); ++i)
            if (x.bits[i] != y.bits[i]) return false;

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

        int i = x.bits.size() - 1;
        int j = y.bits.size() - 1;
        while (i >= 0 && j >= 0) {
            if (x.bits[i] != y.bits[j]) {
                return x.bits[i] < y.bits[j];
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

        LongNumber result;
        result.sign = x.sign;

        LongNumber a = x, b = y;
        a.alignPoints(b);

        bool carry = false;
        size_t maxSize = std::max(a.bits.size(), b.bits.size());
        for (size_t i = 0; i < maxSize || carry; ++i) {
            bool bitA = (i < a.bits.size()) ? a.bits[i] : false;
            bool bitB = (i < b.bits.size()) ? b.bits[i] : false;
            bool sum = bitA ^ bitB ^ carry;
            carry = (bitA && bitB) || (bitA && carry) || (bitB && carry);

            if (i < result.bits.size()) {
                result.bits[i] = sum;
            } else {
                result.bits.push_back(sum);
            }
        }

        result.point = a.point;
        result.deleteZeros();
        return result;
    }

    LongNumber& LongNumber::operator+=(const LongNumber &other) {
        return *this = *this + other;
    }

    LongNumber operator-(const LongNumber &x, const LongNumber &y) {
        if (y.sign) return x + (-y);
        else if (x.sign) return -(-x + y);
        else if (x < y) return -(y - x);

        LongNumber a{x}, b{y};
        a.alignPoints(b);

        bool carry = false;
        for (auto i = 0; i < a.bits.size() || carry; ++i) {
            a.bits[i] = a.bits[i] ^ carry;
            if (i < b.bits.size()) {
                a.bits[i] = a.bits[i] ^ b.bits[i];
            }

            carry = (i < b.bits.size() && b.bits[i] && carry) || (a.bits[i] && carry) || (i < b.bits.size() && b.bits[i] && a.bits[i]);
        }

        a.deleteZeros();
        a.truncateToPrecision();
        return a;
    }

    LongNumber& LongNumber::operator-=(const LongNumber &other) {
        return *this = *this - other;
    }

    LongNumber operator*(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() || y.isZero()) return LongNumber(0);

        LongNumber result;
        result.sign = (x.sign != y.sign);
        result.bits.assign(x.bits.size() + y.bits.size(), false);
        
        for (size_t i = 0; i < x.bits.size(); ++i) {
            if (x.bits[i]) {
                bool carry = false;
                for (size_t j = 0; j < y.bits.size() || carry; ++j) {
                    size_t index = i + j;
                    bool bitY = (j < y.bits.size()) ? y.bits[j] : false;
                    bool sum = result.bits[index] ^ bitY ^ carry;
                    carry = (result.bits[index] && bitY) || (result.bits[index] && carry) || (bitY && carry);
                    result.bits[index] = sum;
                }
            }
        }

        result.point = x.point + y.point;
        result.deleteZeros();
        result.truncateToPrecision();
        return result;
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
        c.bits.pop_back();

        c.sign = (a.sign != b.sign);
        a.sign = false;
        b.sign = false;

        int magnitude = a.magnitude() - b.magnitude() + 1;

        while(b.magnitude() < a.magnitude()){
            b *= LongNumber(2);
        }

        int precision = std::max(a.precision, b.precision);

        LongNumber bd;
        bool digit;
        int size = magnitude > 0 ? precision + magnitude : precision + 1;
        while (!a.isZero() && c.bits.size() <= size) {
            while (a < b) {
                c.bits.insert(c.bits.begin(), false);
                a *= LongNumber(2);
            }

            digit = true;
            bd = b;
            while (bd + b <= a && digit) {
                bd += b;
                digit = false;
            }

            c.bits.insert(c.bits.begin(), digit);
            a -= bd;
            a *= LongNumber(2);
        }

        if (magnitude <= 0){
            c.point = c.bits.size() - 1;
        } else {
            c.bits.insert(c.bits.cbegin(), magnitude, false);
            c.point = c.bits.size() - magnitude;
        }

        c.precision = precision;

        c.deleteZeros();
        c.truncateToPrecision();
        return c;
    }

    LongNumber& LongNumber::operator/=(const LongNumber &other) {
        return *this = *this / other;
    }

    LongNumber operator ""_ln(const char* binaryString, size_t) {
        return LongNumber(binaryString);
    }
}