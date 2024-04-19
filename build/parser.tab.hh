/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MNT_D_UNIVERSITY_COURSE_GRADE4_CSDS337_PROJECT_PJ4_CODE_PG4_1_PG4_BUILD_PARSER_TAB_HH_INCLUDED
# define YY_YY_MNT_D_UNIVERSITY_COURSE_GRADE4_CSDS337_PROJECT_PJ4_CODE_PG4_1_PG4_BUILD_PARSER_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/frontend/parser.y"

  #include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cstring>
#include <variant>
#include <iostream>
  //all of these includes are done as relative paths starting from the build/ directory, since that's where CMake places parser.tab.cc
#include "../src/ast.h"
#include "../src/expressions/call.h"
#include "../src/expressions/int.h"
#include "../src/expressions/float.h"
#include "../src/expressions/string.h"
#include "../src/expressions/variable.h"
#include "../src/expressions/addition.h"
#include "../src/expressions/subtraction.h"
#include "../src/expressions/multiplication.h"
#include "../src/expressions/division.h"
#include "../src/expressions/assignment.h"
#include "../src/expressions/comparison.h"
#include "../src/expressions/and.h"
#include "../src/expressions/or.h"
#include "../src/statements/block.h"
#include "../src/statements/while.h"
#include "../src/statements/if.h"
#include "../src/statements/return.h"

  //add few more
#include "../src/expressions/bool.h"
#include "../src/expressions/modulus.h"
#include "../src/statements/for.h"
#include "../src/expressions/negative.h"
#include "../src/types/simple.h"
extern FILE *yyin;
 

#line 87 "/mnt/d/University/Course/Grade4/CSDS337/Project/PJ4/code/PG4-1/PG4/build/parser.tab.hh"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    BOOL_TYPE = 259,               /* BOOL_TYPE  */
    INT_TYPE = 260,                /* INT_TYPE  */
    FLOAT_TYPE = 261,              /* FLOAT_TYPE  */
    STRING_TYPE = 262,             /* STRING_TYPE  */
    VOID_TYPE = 263,               /* VOID_TYPE  */
    SEMICOLON = 264,               /* SEMICOLON  */
    FOR = 265,                     /* FOR  */
    LPAREN = 266,                  /* LPAREN  */
    RPAREN = 267,                  /* RPAREN  */
    COMMA = 268,                   /* COMMA  */
    LBRACE = 269,                  /* LBRACE  */
    RBRACE = 270,                  /* RBRACE  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    BREAK = 274,                   /* BREAK  */
    RETURN = 275,                  /* RETURN  */
    EQUALS_SIGN = 276,             /* EQUALS_SIGN  */
    LOGICAL_OR = 277,              /* LOGICAL_OR  */
    LOGICAL_AND = 278,             /* LOGICAL_AND  */
    LOGICAL_NOT = 279,             /* LOGICAL_NOT  */
    RELOP_GT = 280,                /* RELOP_GT  */
    RELOP_LT = 281,                /* RELOP_LT  */
    RELOP_GE = 282,                /* RELOP_GE  */
    RELOP_LE = 283,                /* RELOP_LE  */
    RELOP_EQ = 284,                /* RELOP_EQ  */
    RELOP_NE = 285,                /* RELOP_NE  */
    ARITH_PLUS = 286,              /* ARITH_PLUS  */
    ARITH_MINUS = 287,             /* ARITH_MINUS  */
    ARITH_MULT = 288,              /* ARITH_MULT  */
    ARITH_DIV = 289,               /* ARITH_DIV  */
    ARITH_MOD = 290,               /* ARITH_MOD  */
    VARIADIC = 291,                /* VARIADIC  */
    BOOL_LITERAL = 292,            /* BOOL_LITERAL  */
    INT_LITERAL = 293,             /* INT_LITERAL  */
    FLOAT_LITERAL = 294,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 295,          /* STRING_LITERAL  */
    EOL = 296                      /* EOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 55 "src/frontend/parser.y"

  bool boolval;
  int intval;
  double fltval;
  char *strval;
  struct node *nodeval;
  ASTFunctionParameter *var;
  std::vector<ASTFunctionParameter *> *vars;
  ASTStatement *stmt;
  std::vector<ASTStatement *> *stmtVec;
  ASTExpression *exp;
  std::vector<ASTExpression *> *exprVec;
  VarType *type;
  ASTExpressionComparisonType rel;

#line 161 "/mnt/d/University/Course/Grade4/CSDS337/Project/PJ4/code/PG4-1/PG4/build/parser.tab.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MNT_D_UNIVERSITY_COURSE_GRADE4_CSDS337_PROJECT_PJ4_CODE_PG4_1_PG4_BUILD_PARSER_TAB_HH_INCLUDED  */
