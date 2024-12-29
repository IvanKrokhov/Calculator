#include <catch2/catch.hpp>
#include "Calculator.h"

TEST_CASE("Basic Operations", "[calculator]") {
    REQUIRE(EvaluateExpression("2 + 2") == Approx(4.0));
    REQUIRE(EvaluateExpression("5 - 3") == Approx(2.0));
    REQUIRE(EvaluateExpression("3 * 4") == Approx(12.0));
    REQUIRE(EvaluateExpression("8 / 2") == Approx(4.0));
}

TEST_CASE("Power Operations", "[calculator]") {
    REQUIRE(EvaluateExpression("2 ^ 3") == Approx(8.0));
    REQUIRE(EvaluateExpression("5 ^ 0") == Approx(1.0));
    REQUIRE(EvaluateExpression("0 ^ 5") == Approx(0.0));
}

TEST_CASE("Trigonometric Functions", "[calculator]") {
    REQUIRE(EvaluateExpression("sin(0)") == Approx(0.0));
    REQUIRE(EvaluateExpression("cos(0)") == Approx(1.0));
    REQUIRE(EvaluateExpression("tan(0)") == Approx(0.0));
    REQUIRE(EvaluateExpression("sin(3.14159 / 2)") == Approx(1.0));
    REQUIRE(EvaluateExpression("cos(3.14159)") == Approx(-1.0));
}

TEST_CASE("Hyperbolic Functions", "[calculator]") {
    REQUIRE(EvaluateExpression("sinh(0)") == Approx(0.0));
    REQUIRE(EvaluateExpression("cosh(0)") == Approx(1.0));
    REQUIRE(EvaluateExpression("tanh(0)") == Approx(0.0));
}

TEST_CASE("Logarithmic Functions", "[calculator]") {
    REQUIRE(EvaluateExpression("log(1)") == Approx(0.0));
}

TEST_CASE("Complex Expressions", "[calculator]") {
    REQUIRE(EvaluateExpression("2 + 3 * 4") == Approx(14.0));
    REQUIRE(EvaluateExpression("(2 + 3) * 4") == Approx(20.0));
    REQUIRE(EvaluateExpression("3 + 2 ^ 3") == Approx(11.0));
    REQUIRE(EvaluateExpression("sin(3.14159 / 2) + cos(0)") == Approx(2.0));
}

TEST_CASE("Error Handling", "[calculator]") {
    REQUIRE_THROWS_AS(EvaluateExpression("8 / 0"), std::exception);
    REQUIRE_THROWS_AS(EvaluateExpression("2 + (3 *"), std::exception);
    REQUIRE_THROWS_AS(EvaluateExpression("sin(1 +"), std::exception);
}

TEST_CASE("Floating Point Operations", "[calculator]") {
    REQUIRE(EvaluateExpression("3.5 + 2.5") == Approx(6.0));
    REQUIRE(EvaluateExpression("7.5 - 2.5") == Approx(5.0));
    REQUIRE(EvaluateExpression("2.0 * 3.0") == Approx(6.0));
    REQUIRE(EvaluateExpression("5.0 / 2.0") == Approx(2.5));
}

TEST_CASE("Parentheses", "[calculator]") {
    REQUIRE(EvaluateExpression("2 * (3 + 4)") == Approx(14.0));
    REQUIRE(EvaluateExpression("(1 + 2) * (3 + 4)") == Approx(21.0));
    REQUIRE(EvaluateExpression("((2 + 3) * 4) / 5") == Approx(4.0));
}
