#include "comparison.h"


std::unique_ptr<VarType> ASTExpressionComparison::ReturnType(ASTFunction& func) {
    return VarTypeSimple::BoolType.Copy();
}

bool ASTExpressionComparison::IsLValue(ASTFunction& func) {
    return false;
}

llvm::Value* ASTExpressionComparison::Compile(llvm::IRBuilder<>& builder, ASTFunction& func) {
    //ensures both expressions are of the same type
    auto leftType = a1->ReturnType(func);
    auto rightType = a2->ReturnType(func);
    if (!leftType->Equals(rightType.get())) {
        throw std::runtime_error("ERROR: Cannot coerce types in comparison expression! Are they all booleans, ints, and floats?");
    }

    auto a1Val = a1->CompileRValue(builder, func);
    auto a2Val = a2->CompileRValue(builder, func);

    llvm::Value* result = nullptr;
   
    if (leftType->Equals(&VarTypeSimple::IntType) || leftType->Equals(&VarTypeSimple::FloatType)) {
        llvm::CmpInst::Predicate predicate;
        switch (type) {
            case Equal: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_EQ : llvm::CmpInst::FCMP_OEQ; break;
            case NotEqual: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_NE : llvm::CmpInst::FCMP_ONE; break;
            case GreaterThan: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_SGT : llvm::CmpInst::FCMP_OGT; break;
            case GreaterThanOrEqual: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_SGE : llvm::CmpInst::FCMP_OGE; break;
            case LessThan: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_SLT : llvm::CmpInst::FCMP_OLT; break;
            case LessThanOrEqual: predicate = leftType->Equals(&VarTypeSimple::IntType) ? llvm::CmpInst::ICMP_SLE : llvm::CmpInst::FCMP_OLE; break;
            default: throw std::runtime_error("Invalid comparison type.");
        }
        result = builder.CreateCmp(predicate, a1Val, a2Val, "cmpResult");
    } else {
        throw std::runtime_error("ERROR: Comparison is supported only for integer and float types.");
    }

    return result;
}

std::string ASTExpressionComparison::ToString(const std::string& prefix) {
    std::string op;
    switch (type) {
        case Equal: op = "=="; break;
        case NotEqual: op = "!="; break;
        case LessThan: op = "<"; break;
        case LessThanOrEqual: op = "<="; break;
        case GreaterThan: op = ">"; break;
        case GreaterThanOrEqual: op = ">="; break;
        default: op = "unknown"; break;
    }
    return "(" + op + ")\n" + prefix + "├──" + a1->ToString(prefix + "│  ") + "\n" + prefix + "└──" + a2->ToString(prefix + "   ");
}
