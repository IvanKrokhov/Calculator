#pragma once
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>
#include <string>
#include <memory>
#include <cstdint>
#include <cmath>

class Tokenizer {
public:
    explicit Tokenizer(std::istream* in);
    enum TokenType : uint8_t { kNumber, kSymbol, kEnd, kLog, kTrig, kHyperTrig };
    void Consume();
    TokenType GetType() const;
    double GetNumber() const;
    char GetSymbol() const;

private:
    std::istream* in_;
    TokenType type_;
    double number_ = 0.0;
    char symbol_{};
    char next_symbol_{};
    void ConsumeFunction();
    inline bool IsSign(const char& symbol);
    inline bool IsValid(const char& symbol);
};

#endif // TOKENIZER_H
