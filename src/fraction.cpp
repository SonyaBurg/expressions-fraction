#include "fraction.h"
Fraction::Fraction(std::int64_t num)
    : num(num)
    , den(1)
{
    simplify();
}

Fraction::Fraction(std::int64_t num, std::int64_t den)
    : num(num)
    , den(den)
{
    simplify();
}
Fraction::Fraction()
    : Fraction(0)
{
}

std::int64_t Fraction::numerator() const
{
    return num;
}
std::int64_t Fraction::denominator() const
{
    return den;
}

Fraction::operator double() const
{
    return static_cast<double>(num) / den;
}

const Fraction & Fraction::operator+=(const Fraction & other)
{
    if (other.den == den) {
        num += other.num;
        return *this;
    }
    std::int64_t lcm = std::lcm(other.den, den);
    std::int64_t new_num = (lcm / den) * num + other.num * (lcm / other.den);
    den = lcm;
    num = new_num;
    simplify();
    return *this;
}

Fraction operator+(Fraction left, const Fraction & right)
{
    left += right;
    return left;
}

const Fraction & Fraction::operator-=(const Fraction & other)
{
    if (other.den == den) {
        num -= other.num;
        return *this;
    }
    std::int64_t lcm = std::lcm(other.den, den);
    std::int64_t new_num = (lcm / den) * num - other.num * (lcm / other.den);
    den = lcm;
    num = new_num;
    simplify();
    return *this;
}

Fraction operator-(Fraction left, const Fraction & right)
{
    left -= right;
    return left;
}

const Fraction & Fraction::operator*=(const Fraction & other)
{
    if (den == 0 || other.den == 0) {
        num = ((num < 0) ^ (other.num > 0) ? -1 : 1);
        return *this;
    }
    std::int64_t gcd1 = std::gcd(den, other.num);
    std::int64_t gcd2 = std::gcd(other.den, num);
    den /= gcd1;
    num /= gcd2;

    den *= other.den / gcd2;
    num *= other.num / gcd1;
    simplify();
    return *this;
}

Fraction operator*(Fraction left, const Fraction & right)
{
    left *= right;
    return left;
}

const Fraction & Fraction::operator/=(const Fraction & other)
{
    *this *= Fraction(other.den, other.num);
    return *this;
}

Fraction operator/(Fraction left, const Fraction & right)
{
    left /= right;
    return left;
}

Fraction Fraction::operator-() const
{
    return *this * -1;
}

bool Fraction::operator<(const Fraction & other) const
{
    std::int64_t gcd = std::gcd(den, other.den);
    std::int64_t den1 = den / gcd;
    std::int64_t den2 = other.den / gcd;
    return other.num * den1 > num * den2;
}
bool Fraction::operator>(const Fraction & other) const
{
    return !(*this <= other);
}
bool Fraction::operator<=(const Fraction & other) const
{
    return *this < other || *this == other;
}
bool Fraction::operator>=(const Fraction & other) const
{
    return !(*this < other);
}
bool Fraction::operator!=(const Fraction & other) const
{
    return !(*this == other);
}

std::string Fraction::str() const
{
    return std::to_string(num) + "/" + std::to_string(den);
}

void Fraction::simplify()
{
    if (den == 0) {
        num = (num > 0 ? 1 : (num < 0 ? -1 : 0));
        return;
    }
    if (num <= 0 && den < 0) {
        num = -num;
        den = -den;
    }
    std::int64_t gcd = std::gcd(num, den);
    num /= gcd;
    den /= gcd;
    if (num > 0 && den < 0) {
        num = -num;
        den = -den;
    }
}
std::ostream & operator<<(std::ostream & stream, const Fraction & fraction)
{
    stream << fraction.str();
    return stream;
}
