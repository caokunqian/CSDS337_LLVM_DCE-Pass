#pragma once

#include "../expression.h"

enum ASTExpressionComparisonType
{
    Equal,
    NotEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual
};


class ASTExpressionComparison : public ASTExpression
{
    // Type of comparison to do.
    ASTExpressionComparisonType type;

    // oper
    std::unique_ptr<ASTExpression> a1;
    std::unique_ptr<ASTExpression> a2;

public:

    ASTExpressionComparison(ASTExpressionComparisonType type, std::unique_ptr<ASTExpression> a1, std::unique_ptr<ASTExpression> a2) : type(type), a1(std::move(a1)), a2(std::move(a2)) {}

    // comparison expression function

    static auto Create(ASTExpressionComparisonType type, std::unique_ptr<ASTExpression> a1, std::unique_ptr<ASTExpression> a2)
    {
        return std::make_unique<ASTExpressionComparison>(type, std::move(a1), std::move(a2));
    }

    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
};