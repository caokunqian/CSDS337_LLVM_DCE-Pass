#include "multiplication.h"

std::unique_ptr<VarType> ASTExpressionMultiplication::ReturnType(ASTFunction& func) {
    if (!returnType) {
        // Check and coerce types of both expressions to ensure they are compatible for multiplication.
        if (!ASTExpression::CoerceMathTypes(func, a1, a2, returnType)) {
            throw std::runtime_error("ERROR: Cannot coerce types in multiplication expression! Are they both either ints or floats?");
        }
    }
    return std::make_unique<VarTypeSimple>(*returnType); // Return a new instance of the determined return type.
}
// Result  is not an lvalue.
bool ASTExpressionMultiplication::IsLValue(ASTFunction& func) {
    return false; 
}

llvm::Value* ASTExpressionMultiplication::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    auto retType = ReturnType(func); 
    if (retType->Equals(&VarTypeSimple::IntType)) {
        // integer multiplication.
        return builder.CreateMul(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "mulTmp");
    } else if (retType->Equals(&VarTypeSimple::FloatType)) {
        // floating-point multiplication.
        return builder.CreateFMul(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "fMulTmp");
    } else {
        throw std::runtime_error("ERROR: Cannot perform multiplication! Both inputs must be either ints or floats.");
    }
}

std::string ASTExpressionMultiplication::ToString(const std::string& prefix) {
    std::string ret = "(*)\n";
    ret += prefix + "├──" + a1->ToString(prefix + "│  ");
    ret += prefix + "└──" + a2->ToString(prefix + "   ");
    return ret;
}
