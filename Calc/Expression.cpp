#include "Expression.h"
#include <cmath>

Constant::Constant(double value) : value_(value) {}

double Constant::Evaluate() const {
    return value_;
}

UnaryOperation::UnaryOperation(std::unique_ptr<Expression> expr, char op)
    : ex_(std::move(expr)), op_(op) {}

double UnaryOperation::Evaluate() const {
    if (op_ == 'l') {
        return std::log(ex_->Evaluate());
    }
    if (op_ == 's') {
        return std::sin(ex_->Evaluate());
    }
    if (op_ == 'c') {
        return std::cos(ex_->Evaluate());
    }
    if (op_ == 't') {
        return std::tan(ex_->Evaluate());
    }
    if (op_ == 'h') {
        return std::sinh(ex_->Evaluate());
    }
    return ex_->Evaluate();
}

BinaryOperation::BinaryOperation(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, char op)
    : left_(std::move(left)), right_(std::move(right)), op_(op) {}

double BinaryOperation::Evaluate() const {
    switch (op_) {
    case '+':
        return left_->Evaluate() + right_->Evaluate();
    case '-':
        return left_->Evaluate() - right_->Evaluate();
    case '*':
        return left_->Evaluate() * right_->Evaluate();
    case '/':
        return left_->Evaluate() / right_->Evaluate();
    case '^':
        return std::pow(left_->Evaluate(), right_->Evaluate());
    default:
        return 0.0;
    }
}
