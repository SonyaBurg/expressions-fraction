#pragma once

#include <cstdint>
#include <numeric>
#include <ostream>
struct Fraction
{
    Fraction(std::int64_t num);
    Fraction(std::int64_t num, std::int64_t den);
    Fraction();

    std::int64_t numerator() const;
    std::int64_t denominator() const;

    explicit operator double() const;
    const Fraction & operator+=(const Fraction & other);

    friend Fraction operator+(Fraction left, const Fraction & right);

    const Fraction & operator-=(const Fraction & other);

    friend Fraction operator-(Fraction left, const Fraction & right);

    const Fraction & operator*=(const Fraction & other);

    friend Fraction operator*(Fraction left, const Fraction & right);

    const Fraction & operator/=(const Fraction & other);

    friend Fraction operator/(Fraction left, const Fraction & right);

    Fraction operator-() const;

    bool operator==(const Fraction & other) const = default;

    bool operator<(const Fraction & other) const;
    bool operator>(const Fraction & other) const;
    bool operator<=(const Fraction & other) const;
    bool operator>=(const Fraction & other) const;
    bool operator!=(const Fraction & other) const;

    std::string str() const;

    friend std::ostream & operator<<(std::ostream & stream, const Fraction & fraction);

private:
    std::int64_t num;
    std::int64_t den;
    void simplify();
};
