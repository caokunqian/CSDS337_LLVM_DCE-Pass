#pragma once

#include "../expression.h"

class ASTExpressionNegation : public ASTExpression {
public:
    ASTExpressionNegation(std::unique_ptr<ASTExpression> expr) : expr(std::move(expr)) {}

    static auto Create(std::unique_ptr<ASTExpression> expr) {
        return std::make_unique<ASTExpressionNegation>(std::move(expr));
    }

    // Virtual functions. See base class for details.
    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
private:
    std::unique_ptr<ASTExpression> expr;
};