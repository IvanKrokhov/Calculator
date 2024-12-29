#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

class Expression {
public:
    virtual ~Expression() = default;
    virtual double Evaluate() const = 0;
};

class Constant : public Expression {
public:
    explicit Constant(double value);
    double Evaluate() const override;

private:
    double value_;
};

class UnaryOperation : public Expression {
public:
    UnaryOperation(std::unique_ptr<Expression> expr, char op);
    double Evaluate() const override;

private:
    std::unique_ptr<Expression> ex_;
    char op_;
};

class BinaryOperation : public Expression {
public:
    BinaryOperation(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, char op);
    double Evaluate() const override;

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
    char op_;
};

#endif // EXPRESSION_H
