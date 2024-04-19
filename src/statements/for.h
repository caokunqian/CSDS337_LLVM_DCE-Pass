#pragma once 

#include "../expression.h"
#include "../statement.h"

class ASTStatementFor : public ASTStatement {
    using ExprPtr = std::unique_ptr<ASTExpression>;
    using StmtPtr = std::unique_ptr<ASTStatement>;
public:
    ASTStatementFor(ExprPtr before, ExprPtr condition, ExprPtr after, StmtPtr then) : before(std::move(before)), condition(std::move(condition)), after(std::move(after)), then(std::move(then)) {}


    static auto Create(ExprPtr before, ExprPtr condition, ExprPtr after, StmtPtr then)
    {
        return std::make_unique<ASTStatementFor>(std::move(before), std::move(condition), std::move(after), std::move(then));
    }

    virtual std::unique_ptr<VarType> StatementReturnType(ASTFunction& func) override;
    virtual void Compile(llvm::Module& mod, llvm::IRBuilder<>& builder, ASTFunction& func) override;
    virtual std::string ToString(const std::string& prefix) override;

private:
    ExprPtr condition, before, after;
    StmtPtr then;
};