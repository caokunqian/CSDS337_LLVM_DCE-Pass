#pragma once

#include "function.h"
#include "scopeTable.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

// Abstract Syntax Tree, is the main representation of our program.
class AST
{
    // Main LLVM context. Note: If we want support for multiple compilation units, this should be moved elsewhere.
    llvm::LLVMContext context;

    // Module containing all functions.
    llvm::Module module;

    // Builder to build IR code in functions.
    llvm::IRBuilder<> builder;

    // List of functions to be compiled in order.
    std::vector<std::string> functionList;

    // Map function names to values.
    std::map<std::string, std::unique_ptr<ASTFunction>> functions;

    // If the module has been compiled or not.
    bool compiled = false;

public:
    // Function pass manager for function optimizations.
    llvm::legacy::FunctionPassManager fpm;

    // Scope table for variables and functions.
    ScopeTable scopeTable;

    // Constructor: Create a new abstract syntax tree.
    AST(std::string modName);

    // Add a function to the AST.
    ASTFunction* AddFunction(const std::string& name, std::unique_ptr<VarType> returnType, ASTFunctionParameters parameters, bool variadic = false);

    // Get a function from a name.
    ASTFunction* GetFunction(const std::string& name);

    // Compile the AST. This must be done before exporting any object files.
    void Compile();

    // Eliminate dead code from the AST.
    void EliminateDeadCode();

    // Get a string representation of the AST.
    std::string ToString();

    // Write LLVM assembly (.ll) to file. Must be done after compilation.
    void WriteLLVMAssemblyToFile(const std::string& outFile);

    // Write LLVM bitcode (.bc) to file. Must be done after compilation.
    void WriteLLVMBitcodeToFile(const std::string& outFile);
};
