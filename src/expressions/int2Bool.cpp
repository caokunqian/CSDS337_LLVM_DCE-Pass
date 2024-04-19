#include "int2Bool.h"

std::unique_ptr<VarType> ASTExpressionInt2Bool::ReturnType(ASTFunction& func) {
    // The return type for an int-to-bool conversion is obviously boolean.
    return VarTypeSimple::BoolType.Copy();
}

bool ASTExpressionInt2Bool::IsLValue(ASTFunction& func) {
    // a new boolean value
    return false;
}

llvm::Value* ASTExpressionInt2Bool::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    // Ensure the operand is of integer type.
    if (!operand->ReturnType(func)->Equals(&VarTypeSimple::IntType))
        throw std::runtime_error("ERROR: int2bool conversion expects an integer operand!");

    // Compile the operand to an R-Value and compare it to 0 to produce a boolean.
    auto operandVal = operand->CompileRValue(builder, func);
    auto zeroVal = llvm::ConstantInt::get(VarTypeSimple::IntType.GetLLVMType(builder.getContext()), 0, true);
    return builder.CreateICmpNE(operandVal, zeroVal, "int2booltmp");
}

std::string ASTExpressionInt2Bool::ToString(const std::string& prefix) {
    // ensure the final output a string representation for debugging.
    return "int2bool\n" + prefix + "└──" + operand->ToString(prefix + "   ");
}
