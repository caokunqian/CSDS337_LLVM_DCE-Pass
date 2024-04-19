#pragma once

#include "../expression.h"
#include "../statement.h"

class ASTExpressionAnd : public ASTExpression {
    using ExprPtr = std::unique_ptr<ASTExpression>;
public:
    ASTExpressionAnd(ExprPtr left, ExprPtr right) : left(std::move(left)), right(std::move(right)) {}

    static auto Create(ExprPtr left, ExprPtr right) {
        return std::make_unique<ASTExpressionAnd>(std::move(left), std::move(right));
    }

    // Virtual functions. See base class for details.
    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
private:
    ExprPtr left, right;
};