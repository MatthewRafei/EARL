// MIT License

// Copyright (c) 2023 malloc-nbytes

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <any>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>

#include "interpreter.hpp"
#include "err.hpp"
#include "token.hpp"
#include "ast.hpp"
#include "ctx.hpp"
#include "earlvar.hpp"
#include "common.hpp"

EarlTy::Type ExprEvalResult::get_earl_type(Ctx &ctx) {
  if (m_expr_term_type == ExprTermType::Ident) {
    Token *tok = std::any_cast<Token *>(m_expr_value);
    if (!ctx.earlvar_in_scope(tok->lexeme())) {
      ERR_WARGS(ErrType::Fatal, "variable `%s` is not in scope", tok->lexeme().c_str());
    }
    EarlVar &var = ctx.get_earlvar_from_scope(tok->lexeme());
    return var.m_type;
  }

  switch (m_expr_term_type) {
  case ExprTermType::Int_Literal:
    return EarlTy::Type::Int;
  case ExprTermType::Str_Literal:
    return EarlTy::Type::Str;
  default:
    ERR_WARGS(ErrType::Fatal, "ExprTermType `%d` is not a valid EARL type",
              static_cast<int>(m_expr_term_type));
  }
}

ExprEvalResult eval_expr(Expr *expr, Ctx &ctx);

ExprEvalResult eval_funccall(ExprFuncCall *expr, Ctx &ctx) {
  // Check if it is intrinsic
  if (expr->m_id->lexeme() == "print") {
    for (std::unique_ptr<Expr> &e : expr->m_params) {
      ExprEvalResult param = eval_expr(e.get(), ctx);
      if (param.m_expr_term_type == ExprTermType::Int_Literal) {
        std::cout << std::any_cast<int>(param.m_expr_value) << '\n';
      }
    }
  }

  // Check for user defined functions
  // ...

  return ExprEvalResult{};
}

ExprEvalResult eval_expr_term(ExprTerm *expr, Ctx &ctx) {
  switch (expr->get_term_type()) {
  case ExprTermType::Ident: {
    ExprIdent *ident = dynamic_cast<ExprIdent *>(expr);
    return ExprEvalResult {ident->m_tok.get(), ident->get_term_type()};
  } break;
  case ExprTermType::Int_Literal: {
    ExprIntLit *intlit = dynamic_cast<ExprIntLit *>(expr);
    return ExprEvalResult {std::stoi(intlit->m_tok->lexeme()), intlit->get_term_type()};
  } break;
  case ExprTermType::Str_Literal: {
    assert(false && "unimplemented");
  } break;
  case ExprTermType::Func_Call: {
    return eval_funccall(dynamic_cast<ExprFuncCall *>(expr), ctx);
  } break;
  default:
    ERR_WARGS(ErrType::Fatal, "%d is not a valid expression term type is not valid",
              static_cast<int>(expr->get_term_type()));
  }
}

ExprEvalResult eval_expr_bin(ExprBinary *expr, Ctx &ctx) {
  assert(false && "unimplemented");
  (void)expr;
  (void)ctx;
  return ExprEvalResult {};
}

ExprEvalResult eval_expr(Expr *expr, Ctx &ctx) {
  switch (expr->get_type()) {
  case ExprType::Term: {
    return eval_expr_term(dynamic_cast<ExprTerm *>(expr), ctx);
  } break;
  case ExprType::Binary: {
    assert(false && "unimplemented");
  } break;
  default:
    ERR_WARGS(ErrType::Fatal, "expression type %d is not a valid expression",
              static_cast<int>(expr->get_type()));
  }
}

void eval_stmt_let(StmtLet *stmt, Ctx &ctx) {
  const std::string &id = stmt->m_id->lexeme();
  if (ctx.earlvar_in_scope(id)) {
    ERR_WARGS(ErrType::Redeclared, "variable `%s` is already defined", id.c_str());
  }

  // The `let` type binding i.e., let x: <TYPE> = ...;
  EarlTy::Type binding_type = EarlTy::of_str(stmt->m_type->lexeme());

  ExprEvalResult expr_eval = eval_expr(stmt->m_expr.get(), ctx);

  // The type of the right side of the equals sign
  EarlTy::Type rval_type = expr_eval.get_earl_type(ctx);

  if (!EarlTy::earlvar_type_compat(binding_type, rval_type)) {
    ERR_WARGS(ErrType::ERR_FATAL, "type (%d) is not compatable with type (%d)",
              static_cast<int>(binding_type), static_cast<int>(rval_type));
  }

  ctx.add_earlvar_to_scope(std::move(stmt->m_id), binding_type, false, expr_eval);
}

void eval_stmt_expr(StmtExpr *stmt, Ctx &ctx) {
  (void)eval_expr(stmt->m_expr.get(), ctx);
}

void eval_stmt(std::unique_ptr<Stmt> stmt, Ctx &ctx) {
  switch (stmt->stmt_type()) {
  case StmtType::Let: {
    eval_stmt_let(dynamic_cast<StmtLet *>(stmt.get()), ctx);
  } break;
  case StmtType::Mut: {
    assert(false && "unimplemented");
  } break;
  case StmtType::Def: {
    assert(false && "unimplemented");
  } break;
  case StmtType::Block: {
    assert(false && "unimplemented");
  } break;
  case StmtType::Stmt_Expr: {
    eval_stmt_expr(dynamic_cast<StmtExpr *>(stmt.get()), ctx);
  } break;
  default:
    assert(false && "eval_stmt: invalid statement");
  }
}

void interpret(Program &program) {
  Ctx ctx;

  for (size_t i = 0; i < program.m_stmts.size(); ++i) {
    eval_stmt(std::move(program.m_stmts.at(i)), ctx);
  }
}
