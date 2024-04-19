#include "for.h"
#include "../function.h"

std::unique_ptr<VarType> ASTStatementFor::StatementReturnType(ASTFunction& func) {
    // loops do not return a value.
    return nullptr;
}

void ASTStatementFor::Compile(llvm::Module& mod, llvm::IRBuilder<>& builder, ASTFunction& func) {
    // ensure it is a boolean expression.
    ASTExpression::ImplicitCast(func, condition, &VarTypeSimple::BoolType);

    // Retrieve the LLVM function 
    auto* funcVal = static_cast<llvm::Function*>(func.GetVariableValue(func.name));

    // basic blocks
    auto* forInitBlock = llvm::BasicBlock::Create(builder.getContext(), "forInit", funcVal);
    auto* forCondBlock = llvm::BasicBlock::Create(builder.getContext(), "forCond", funcVal);
    auto* forBodyBlock = llvm::BasicBlock::Create(builder.getContext(), "forBody", funcVal);
    auto* forEndBlock = llvm::BasicBlock::Create(builder.getContext(), "forEnd", funcVal);

    // jump to the condition block.
    builder.CreateBr(forInitBlock);
    builder.SetInsertPoint(forInitBlock);
    before->Compile(builder, func);
    builder.CreateBr(forCondBlock);

    // Check the loop condition
    builder.SetInsertPoint(forCondBlock);
    auto* condValue = condition->CompileRValue(builder, func);
    builder.CreateCondBr(condValue, forBodyBlock, forEndBlock);

    // 
    builder.SetInsertPoint(forBodyBlock);
    then->Compile(mod, builder, func);
    //  iteration step and jump back to the condition block.
    after->Compile(builder, func);
    builder.CreateBr(forCondBlock);

    // compiling code 
    builder.SetInsertPoint(forEndBlock);
}

std::string ASTStatementFor::ToString(const std::string& prefix) {
    std::string output = "for loop\n";
    output += prefix + "├── Init: " + before->ToString(prefix + "│  ") + "\n";
    output += prefix + "├── Cond: " + condition->ToString(prefix + "│  ") + "\n";
    output += prefix + "├── Body: " + then->ToString(prefix + "│  ") + "\n";
    output += prefix + "└── Iter: " + after->ToString(prefix + "   ");
    return output;
}
