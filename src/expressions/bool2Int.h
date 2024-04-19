#pragma once

#include "../expression.h"

// Whoops! Looks like someone removed the declarations...


class ASTExpressionBool2Int : public ASTExpression {
public:
    ASTExpressionBool2Int(std::unique_ptr<ASTExpression> expr) : expr(std::move(expr)) {}

    static auto Create(std::unique_ptr<ASTExpression> expr) {
        return std::make_unique<ASTExpressionBool2Int>(std::move(expr));
    }

    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
private:
    std::unique_ptr<ASTExpression> expr;
};