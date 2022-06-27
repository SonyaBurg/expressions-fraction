#pragma once

#include "fraction.h"

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

struct Expression
{
    virtual Fraction eval(std::map<std::string, Fraction> const & values = {}) const = 0;

    virtual Expression * clone() const = 0;

    friend std::ostream & operator<<(std::ostream & out, const Expression & expression)
    {
        out << expression.to_string();
        return out;
    }
    // protected:
    virtual std::string to_string() const = 0;
    virtual ~Expression() = default;
};

struct Const : Expression
{
    Const(Fraction data)
        : data(data){};
    Fraction eval(std::map<std::string, Fraction> const & = {}) const override
    {
        return data;
    }
    Expression * clone() const override
    {
        return new Const(*this);
    }

    std::string to_string() const override
    {
        return data.str();
    }
    ~Const() = default;

private:
    Fraction data;
};

struct Variable : Expression
{
    Variable(const std::string & name)
        : name(name){};
    Fraction eval(std::map<std::string, Fraction> const & values = {}) const override
    {
        return values.at(name);
    }

    Expression * clone() const override
    {
        return new Variable(*this);
    }
    std::string to_string() const override
    {
        return name;
    }

    ~Variable() = default;

private:
    std::string name;
};

struct Negate : Expression
{
    Negate(const std::shared_ptr<Expression> & value)
        : value(value)
    {
    }

    Negate(const Expression & value)
        : value(value.clone())
    {
    }

    Fraction eval(std::map<std::string, Fraction> const & values = {}) const override
    {
        return Fraction(-1) * value->eval(values);
    }

    Expression * clone() const override
    {
        return new Negate(*this);
    }
    std::string to_string() const override
    {
        return "(-" + value->to_string() + ")";
    }

private:
    std::shared_ptr<Expression> value;
};

template <class calculate, char symbol>
struct Binary : Expression
{
    Binary(const std::shared_ptr<Expression> & left, const std::shared_ptr<Expression> & right)
        : left(left)
        , right(right)
    {
    }

    Binary(const Expression & left, const Expression & right)
        : left(left.clone())
        , right(right.clone())
    {
    }
    Fraction eval(std::map<std::string, Fraction> const & values = {}) const override
    {
        return calculate()(left->eval(values), right->eval(values));
    }

    std::string to_string() const override
    {
        return "(" + left->to_string() + " " + symbol + " " + right->to_string() + ")";
    }

    Expression * clone() const override
    {
        return new Binary(left, right);
    }

    ~Binary() = default;

protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
};

namespace implementations {
constexpr auto add_ = std::plus<Fraction>();
constexpr auto subtract_ = std::minus<Fraction>();
constexpr auto multiply_ = std::multiplies<Fraction>();
constexpr auto divide_ = std::divides<Fraction>();
} // namespace implementations

using Add = Binary<decltype(implementations::add_), '+'>;
using Subtract = Binary<decltype(implementations::subtract_), '-'>;
using Multiply = Binary<decltype(implementations::multiply_), '*'>;
using Divide = Binary<decltype(implementations::divide_), '/'>;

Add operator+(const Expression & left, const Expression & right) { return {left, right}; }
Subtract operator-(const Expression & left, const Expression & right) { return {left, right}; }
Multiply operator*(const Expression & left, const Expression & right) { return {left, right}; }
Divide operator/(const Expression & left, const Expression & right) { return {left, right}; }
Negate operator-(const Expression & arg) { return {arg}; }
