#include "and.h"
#include "../function.h"

std::unique_ptr<VarType> ASTExpressionAnd::ReturnType(ASTFunction& func) {
    // AND operation
    return VarTypeSimple::BoolType.Copy();
}

bool ASTExpressionAnd::IsLValue(ASTFunction& func) {
    // AND results
    return false;
}

llvm::Value* ASTExpressionAnd::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    // Make sure to cast both sides
    ASTExpression::ImplicitCast(func, left, &VarTypeSimple::BoolType);
    ASTExpression::ImplicitCast(func, right, &VarTypeSimple::BoolType);

    // LLVM function.
    auto* funcVal = static_cast<llvm::Function*>(func.GetVariableValue(func.name));

    // Create basic blocks for the AND logic.
    auto* falseBlock = llvm::BasicBlock::Create(builder.getContext(), "andFalse", funcVal);
    auto* trueBlock = llvm::BasicBlock::Create(builder.getContext(), "andTrue", funcVal);
    auto* contBlock = llvm::BasicBlock::Create(builder.getContext(), "andCont", funcVal);

    // left expression.
    auto* leftVal = left->CompileRValue(builder, func);
    builder.CreateCondBr(leftVal, trueBlock, falseBlock);

    // right expression
    builder.SetInsertPoint(trueBlock);
    auto* rightVal = right->CompileRValue(builder, func);
    builder.CreateBr(contBlock);

    // Direct flow from the false block
    builder.SetInsertPoint(falseBlock);
    builder.CreateBr(contBlock);

    // select the correct value
    builder.SetInsertPoint(contBlock);
    auto* phiNode = builder.CreatePHI(llvm::Type::getInt1Ty(builder.getContext()), 2, "andTmp");
    phiNode->addIncoming(llvm::ConstantInt::getFalse(builder.getContext()), falseBlock);
    phiNode->addIncoming(rightVal, trueBlock);

    return phiNode;
}

std::string ASTExpressionAnd::ToString(const std::string& prefix) {
    std::string ret = "(&&)\n";
    ret += prefix + "├──" + left->ToString(prefix + "│  ");
    ret += prefix + "└──" + right->ToString(prefix + "   ");
    return ret;
}
