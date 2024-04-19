#include "subtraction.h"

std::unique_ptr<VarType> ASTExpressionSubtraction::ReturnType(ASTFunction& func) {
    if (!returnType) {
        if (!ASTExpression::CoerceMathTypes(func, a1, a2, returnType))
            throw std::runtime_error("ERROR: Cannot coerce types in subtraction expression");
    }
    return std::make_unique<VarTypeSimple>(*returnType);
}

bool ASTExpressionSubtraction::IsLValue(ASTFunction& func) {
    return false;
}

llvm::Value* ASTExpressionSubtraction::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    // Compile the values as needed. Remember, we can only do operations on R-Values.
    auto retType = ReturnType(func);
    if (retType->Equals(&VarTypeSimple::IntType)) // Perform standard subtraction on integer operands since we return an int.
        return builder.CreateSub(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "subtmp");
    else if (retType->Equals(&VarTypeSimple::FloatType)) // Perform subtraction on floating point operands since we return a float.
        return builder.CreateFSub(a1->CompileRValue(builder, func), a2->CompileRValue(builder, func), "fsubtmp");
    else // Call to return type should make this impossible, but best to keep it here just in case of a bug.
        throw std::runtime_error("ERROR: Cannot perform subtraction! Are both inputs either ints or floats?");
}

std::string ASTExpressionSubtraction::ToString(const std::string& prefix) {
    std::string ret = "(-)\n";
    ret += prefix + "├──" + a1->ToString(prefix + "│  ");
    ret += prefix + "└──" + a2->ToString(prefix + "   ");
    return ret;
}
