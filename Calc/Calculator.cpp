#include "Calculator.h"
#include "Tokenizer.h"
#include "Expression.h"
#include <iostream>
#include <sstream>

std::unique_ptr<Expression> ParseExpression(Tokenizer* tokenizer);
std::unique_ptr<Expression> ParseUnit(Tokenizer* tokenizer);
std::unique_ptr<Expression> ParsePow(Tokenizer* tokenizer);
std::unique_ptr<Expression> ParseMult(Tokenizer* tokenizer);

void PrintHelp() {
    std::cout << "��������� �������:\n";
    std::cout << "1. ������� ��������� ��� ���������� (��������, 2 + 2 ��� sin(3.14))\n";
    std::cout << "2. ������� 'exit' ��� ������ �� ���������.\n\n";

    std::cout << "�������������� �������:\n";
    std::cout << "- s(x)  : ����� ���� x\n";
    std::cout << "- c(x)  : ������� ���� x\n";
    std::cout << "- t(x)  : ������� ���� x\n";
    std::cout << "- sh(x) : ��������������� ����� ���� x\n";
    std::cout << "- ch(x) : ��������������� ������� ���� x\n";
    std::cout << "- th(x) : ��������������� ������� ���� x\n";
    std::cout << "- l(x)  : ����������� �������� x\n";
    std::cout << "- +     : ��������\n";
    std::cout << "- -     : ���������\n";
    std::cout << "- *     : ���������\n";
    std::cout << "- /     : �������\n";
    std::cout << "- (x)^(y) : ���������� x � ������� y\n";
}

double EvaluateExpression(const std::string& expression) {
    std::istringstream ss{ expression };
    Tokenizer tokenizer{ &ss };
    auto expr = ParseExpression(&tokenizer);
    return expr->Evaluate();
}

void Calculator() {
    std::string input;
    PrintHelp();

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "����� �� ������������. �� ��������!\n";
            break;
        }

        try {
            double result = EvaluateExpression(input);
            std::cout << "���������: " << result << '\n';
        }
        catch (const std::exception& e) {
            std::cout << "������: " << e.what() << '\n';
        }
    }
}

std::unique_ptr<Expression> ParseUnit(Tokenizer* tokenizer) {
    if (tokenizer->GetType() == Tokenizer::kNumber) {
        auto num = tokenizer->GetNumber();
        auto x = std::make_unique<Constant>(num);
        tokenizer->Consume();
        return x;
    }
    if (tokenizer->GetType() == Tokenizer::kSymbol) {
        if (tokenizer->GetSymbol() == '(') {
            tokenizer->Consume();
            auto temp = ParseExpression(tokenizer);
            tokenizer->Consume();
            return temp;
        }
        if (tokenizer->GetSymbol() == 'l' || tokenizer->GetSymbol() == 's' ||
            tokenizer->GetSymbol() == 'c' || tokenizer->GetSymbol() == 't' ||
            tokenizer->GetSymbol() == 'h') {
            char func = tokenizer->GetSymbol();
            tokenizer->Consume();
            tokenizer->Consume();
            auto operand = ParseExpression(tokenizer);
            tokenizer->Consume();
            return std::make_unique<UnaryOperation>(std::move(operand), func);
        }
        auto operation = tokenizer->GetSymbol();
        tokenizer->Consume();
        auto x = ParseUnit(tokenizer);
        return std::make_unique<UnaryOperation>(std::move(x), operation);
    }
    return nullptr;
}

std::unique_ptr<Expression> ParsePow(Tokenizer* tokenizer) {
    auto base = ParseUnit(tokenizer);
    while (tokenizer->GetType() == Tokenizer::kSymbol && tokenizer->GetSymbol() == '^') {
        tokenizer->Consume();
        auto exponent = ParseUnit(tokenizer);
        base = std::make_unique<BinaryOperation>(std::move(base), std::move(exponent), '^');
    }
    return base;
}

std::unique_ptr<Expression> ParseMult(Tokenizer* tokenizer) {
    auto x = ParsePow(tokenizer);
    while (tokenizer->GetType() == Tokenizer::kSymbol &&
        (tokenizer->GetSymbol() == '*' || tokenizer->GetSymbol() == '/')) {
        auto op = tokenizer->GetSymbol();
        tokenizer->Consume();
        auto y = ParsePow(tokenizer);
        x = std::make_unique<BinaryOperation>(std::move(x), std::move(y), op);
    }
    return x;
}

std::unique_ptr<Expression> ParseExpression(Tokenizer* tokenizer) {
    auto x = ParseMult(tokenizer);
    while (tokenizer->GetType() == Tokenizer::kSymbol &&
        (tokenizer->GetSymbol() == '+' || tokenizer->GetSymbol() == '-')) {
        auto op = tokenizer->GetSymbol();
        tokenizer->Consume();
        auto y = ParseMult(tokenizer);
        x = std::make_unique<BinaryOperation>(std::move(x), std::move(y), op);
    }
    return x;
}
