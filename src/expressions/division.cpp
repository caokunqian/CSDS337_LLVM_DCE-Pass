#include "division.h"

std::unique_ptr<VarType> ASTExpressionDivision::ReturnType(ASTFunction& func) {
    if (!returnType) {
        if (!ASTExpression::CoerceMathTypes(func, a1, a2, returnType))
            throw std::runtime_error("ERROR: Cannot coerce types in division expression! Are they both either ints or floats?");
    }
    return std::make_unique<VarTypeSimple>(*returnType);
}

bool ASTExpressionDivision::IsLValue(ASTFunction& func) {
    return false;
}

llvm::Value* ASTExpressionDivision::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    auto retType = ReturnType(func);
    if (retType->Equals(&VarTypeSimple::IntType))
        return builder.CreateSDiv(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "divtmp");
    else if (retType->Equals(&VarTypeSimple::FloatType))
        return builder.CreateFDiv(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "fdivtmp");
    else
        throw std::runtime_error("ERROR: Cannot perform division! Are both inputs either ints or floats?");
}

std::string ASTExpressionDivision::ToString(const std::string& prefix) {
    std::string ret = "(/)\n";
    ret += prefix + "├──" + a1->ToString(prefix + "│  ");
    ret += prefix + "└──" + a2->ToString(prefix + "   ");
    return ret;
}
