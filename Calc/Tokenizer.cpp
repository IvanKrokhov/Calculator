#include "Tokenizer.h"

inline bool Tokenizer::IsSign(const char& symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
        symbol == '^' || symbol == ')' || symbol == '(' || symbol == 's' ||
        symbol == 'c' || symbol == 't' || symbol == 'h' || symbol == 'l';
}

inline bool Tokenizer::IsValid(const char& symbol) {
    return IsSign(symbol) || std::isdigit(symbol) || symbol == '.';
}

Tokenizer::Tokenizer(std::istream* in) : in_{ in } {
    Consume();
}

void Tokenizer::Consume() {
    if (in_->get(symbol_)) {
        while (!IsValid(symbol_) && in_->get(symbol_)) {}
        if (IsSign(symbol_)) {
            type_ = kSymbol;
            number_ = 0.0;
        }
        else if (std::isdigit(symbol_) || symbol_ == '.') {
            std::string str;
            type_ = kNumber;
            while (std::isdigit(symbol_) || symbol_ == '.') {
                str += symbol_;
                if (!in_->get(symbol_)) {
                    break;
                }
                if (!std::isdigit(symbol_) && symbol_ != '.') {
                    in_->putback(symbol_);
                    break;
                }
            }
            number_ = std::stod(str);
        }
        else if (symbol_ == 's' || symbol_ == 'c' || symbol_ == 't' || symbol_ == 'h') {
            type_ = kTrig;
            next_symbol_ = symbol_;
            ConsumeFunction();
        }
        else {
            type_ = kEnd;
        }
    }
    else {
        type_ = kEnd;
    }
}

void Tokenizer::ConsumeFunction() {
    if (next_symbol_ == 's' && in_->get(symbol_) && symbol_ == 'i') {
        type_ = kTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 'c' && in_->get(symbol_) && symbol_ == 'o') {
        type_ = kTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 't' && in_->get(symbol_) && symbol_ == 'a') {
        type_ = kTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 'c' && in_->get(symbol_) && symbol_ == 't') {
        type_ = kTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 's' && in_->get(symbol_) && symbol_ == 'h') {
        type_ = kHyperTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 'c' && in_->get(symbol_) && symbol_ == 'h') {
        type_ = kHyperTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 't' && in_->get(symbol_) && symbol_ == 'h') {
        type_ = kHyperTrig;
        symbol_ = '(';
    }
    else if (next_symbol_ == 'c' && in_->get(symbol_) && symbol_ == 't') {
        type_ = kHyperTrig;
        symbol_ = '(';
    }
    else {
        type_ = kEnd;
    }
}

Tokenizer::TokenType Tokenizer::GetType() const {
    return type_;
}

double Tokenizer::GetNumber() const {
    return number_;
}

char Tokenizer::GetSymbol() const {
    return symbol_;
}
