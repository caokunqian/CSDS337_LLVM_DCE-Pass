#include "bool2Int.h"

std::unique_ptr<VarType> ASTExpressionBool2Int::ReturnType(ASTFunction& func)
{
    return VarTypeSimple::IntType.Copy();
}
bool ASTExpressionBool2Int::IsLValue(ASTFunction& func)
{
    return false; 
}

llvm::Value* ASTExpressionBool2Int::Compile(llvm::IRBuilder<>& builder, ASTFunction& func)
{
    if (!expr->ReturnType(func)->Equals(&VarTypeSimple::BoolType))
        throw std::runtime_error("ERROR: Expected bool operand in bool2int but got another type instead!");
    return builder.CreateIntCast(expr->CompileRValue(builder, func), VarTypeSimple::IntType.GetLLVMType(builder.getContext()), true);
    
}
std::string ASTExpressionBool2Int::ToString(const std::string& prefix)
{
    return "bool2Int\n" + prefix + "└──" + expr->ToString(prefix + "   ");
}