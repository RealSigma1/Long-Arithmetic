#include "ln.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

namespace LongMath {
    LongNumber::LongNumber() {
        neg = false;
        dot = 0;
        bits.push_back(0);
        prec = 100;
    }

    LongNumber::LongNumber(int val) {
        dot = 0;
        prec = 100;
        neg = false;

        if (val == 0) {
            bits.push_back(0);
            return;
        }

        if (val < 0) {
            neg = true;
            val = -val;
        }

        while (val > 0) {
            bits.push_back(val % 10);
            val /= 10;
        }
    }

    LongNumber::LongNumber(int val, int customPrec) {
        dot = 0;
        prec = customPrec;
        neg = false;

        if (val == 0) {
            bits.push_back(0);
            return;
        }

        if (val < 0) {
            neg = true;
            val = -val;
        }

        while (val > 0) {
            bits.push_back(val % 10);
            val /= 10;
        }
    }

    LongNumber::LongNumber(std::string s) {
        if (s[0] == '-') {
            neg = true;
            s.erase(s.begin());
        } else {
            neg = false;
        }

        auto pos = s.find('.');

        if (pos < std::string::npos) {
            dot = s.length() - pos - 1;
            s.erase(s.begin() + pos);
        } else {
            pos = s.find(',');
            if (pos < std::string::npos) {
                dot = s.length() - pos - 1;
                s.erase(s.begin() + pos);
            } else {
                dot = 0;
            }
        }

        prec = fmax(100, dot + 10);

        auto it = s.end();
        while (it != s.begin()) {
            it--;
            bits.push_back(*it - '0');
        }

        trim();
    }

    bool LongNumber::isZero() const {
        return bits.size() == 1 && bits[0] == 0;
    }

    int LongNumber::exp() const {
        int e = bits.size() - dot;
        auto it = bits.end() - 1;
        while (it >= bits.begin() && *it == 0){
            e--;
            it--;
        }
        return e;
    }

    void LongNumber::trim() {
        while (dot > 0 && bits.front() == 0) {
            bits.erase(bits.begin());
            --dot;
        }

        while (bits.size() > dot + 1 && bits.back() == 0) {
            bits.pop_back();
        }
    }

    std::string LongNumber::toStr() const {
        std::string res;

        if (neg) res += '-';

        for (int i = bits.size() - 1; i >= 0; --i) {
            res += static_cast<char>(bits[i] + '0');

            if (i == dot) {
                res += '.';
            }
        }

        if(dot == 0)
            res += '0';

        return res;
    }

    std::string LongNumber::toStr(int p) const {
        std::string res;

        if (neg) res += '-';

        for (int i = bits.size() - 1; i >= 0 && i >= dot - p; --i) {
            res += static_cast<char>(bits[i] + '0');

            if (i == dot) {
                res += '.';
            }
        }

        if(dot == 0)
            res += '0';

        return res;
    }

    LongNumber LongNumber::fromBin(const std::string& bin) {
        bool isNeg = false;
        std::string s = bin;

        if (s[0] == '-') {
            isNeg = true;
            s.erase(s.begin());
        }

        size_t pos = s.find('.');
        std::string intPart = s.substr(0, pos);
        std::string fracPart = (pos != std::string::npos) ? s.substr(pos + 1) : "";

        LongNumber res = 0_ln;  

        for (size_t i = 0; i < intPart.length(); ++i) {
            if (intPart[i] == '1') {
                LongNumber p = 1_ln;  
                for (size_t j = 0; j < intPart.length() - i - 1; ++j) {
                    p *= 2_ln;  
                }
                res += p;  
            }
        }

        for (size_t i = 0; i < fracPart.length(); ++i) {
            if (fracPart[i] == '1') {
                LongNumber p = 1_ln;  
                for (size_t j = 0; j <= i; ++j) {
                    p /= 2_ln;  
                }
                res += p;  
            }
        }

        if (isNeg) {
            res = -res;
        }

        return res;
    }

    std::ostream &operator<<(std::ostream &os, const LongNumber &n) {
        return os << n.toStr();
    }

    LongNumber LongNumber::operator-() const {
        LongNumber inv(*this);
        inv.neg = !neg;
        return inv;
    }

    bool operator==(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() && y.isZero()) return true;

        if (y.neg != x.neg || y.dot != x.dot || x.bits.size() != y.bits.size()) return false;

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
            return !y.neg;
        } else if (y.isZero()) {
            return x.neg;
        }

        if (y.neg && x.neg) {
            return -y < -x;
        }

        if (y.neg != x.neg) {
            return !y.neg;
        }

        if (y.exp() != x.exp()) return x.exp() < y.exp();

        int i = x.bits.size() - 1;
        int j = y.bits.size() - 1;
        while (i >= 0 && j >= 0) {
            if (x.bits[i] != y.bits[j]) {
                return x.bits[i] < y.bits[j];
            }
            --i;
            --j;
        }

        return x.dot < y.dot;
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
        if (x.neg != y.neg) {
            if (y.neg) return x - (-y);
            return y - (-x);
        }

        LongNumber a, b;
        int diff = static_cast<int>(x.dot - y.dot);
        if (diff > 0) {
            a = x;
            b = y;
        } else {
            a = y;
            b = x;
            diff = -diff;
        }

        short carry = 0;
        int j;
        for (auto i = 0; i < b.bits.size() || carry != 0; ++i) {
            j = i + diff;

            if (j == a.bits.size()) {
                if (i < b.bits.size()){
                    a.bits.push_back(b.bits[i] + carry);
                } else{
                    a.bits.push_back(carry);
                }

            } else {
                if (i < b.bits.size()){
                    a.bits[j] += b.bits[i] + carry;
                } else{
                    a.bits[j] += carry;
                }
            }

            if (a.bits[j] >= 10) {
                a.bits[j] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.trim();

        return a;
    }

    LongNumber& LongNumber::operator+=(const LongNumber &other) {
        return *this = *this + other;
    }

    LongNumber operator-(const LongNumber &x, const LongNumber &y) {
        if (y.neg) return x + (-y);
        else if (x.neg) return -(-x + y);
        else if (x < y) return -(y - x);

        LongNumber a{x}, b{y};
        int diff = static_cast<int>(x.dot - y.dot);

        if (diff > 0) {
            b.bits.insert(b.bits.begin(), diff, 0);
        } else if (diff != 0) {
            a.bits.insert(a.bits.begin(), -diff, 0);
            a.dot -= diff;
        }

        short carry = 0;
        for (auto i = 0; i < a.bits.size() || carry != 0; ++i) {
            a.bits[i] -= carry;
            if (i < b.bits.size()) {
                a.bits[i] -= b.bits[i];
            }

            if (a.bits[i] < 0) {
                a.bits[i] += 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.trim();

        return a;
    }

    LongNumber& LongNumber::operator-=(const LongNumber &other) {
        return *this = *this - other;
    }

    LongNumber operator*(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() || y.isZero()) return 0_ln;

        LongNumber c = 0_ln;
        c.neg = (x.neg != y.neg);
        c.dot = x.dot + y.dot;  

        short carry;
        for (auto i = 0; i < x.bits.size(); ++i) {
            carry = 0;
            for (auto j = 0; j < y.bits.size() || carry != 0; ++j) {
                if (i + j >= c.bits.size()) {
                    c.bits.push_back(0);
                }
                auto n = c.bits[i + j] + x.bits[i] * (j < y.bits.size() ? y.bits[j] : 0) + carry;

                c.bits[i + j] = n % 10;

                carry = n / 10;
            }
        }

        c.trim();

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
        c.bits.pop_back();

        c.neg = (a.neg != b.neg);
        a.neg = false;
        b.neg = false;

        int e = a.exp() - b.exp() + 1;

        while(b.exp() < a.exp()){
            b *= 10_ln;
        }

        int p = fmax(a.prec, b.prec);

        LongNumber bd;
        short d;
        int size = e > 0 ? p + e : p + 1;
        while (!a.isZero() && c.bits.size() <= size) {
            while (a < b) {
                c.bits.insert(c.bits.begin(), 0);
                a *= 10_ln;
            }

            d = 1;
            bd = b;
            while (bd + b <= a && d < 9) {
                bd += b;
                d++;
            }

            c.bits.insert(c.bits.begin(), d);
            a -= bd;
            a *= 10_ln;
        }

        if (e <= 0){
            c.dot = c.bits.size() - 1;
        } else {
            c.bits.insert(c.bits.cbegin(), e, 0);
            c.dot = c.bits.size() - e;
        }

        c.prec = p;

        c.trim();
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
    return LongMath::LongNumber::fromBin(str);
}