#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>

#include "intrinsics.hpp"
#include "interpreter.hpp"
#include "err.hpp"
#include "ctx.hpp"
#include "ast.hpp"

const std::unordered_map<std::string, Intrinsics::IntrinsicFunction> Intrinsics::intrinsic_functions = {
    {"print", &Intrinsics::print},
};

bool Intrinsics::is_intrinsic_function(const std::string &id) {
    return intrinsic_functions.find(id) != intrinsic_functions.end();
}

Interpreter::ExprEvalResult Intrinsics::run_intrinsic_function(ExprFuncCall *expr, std::vector<Interpreter::ExprEvalResult> params, Ctx &ctx) {
    auto retval = Intrinsics::intrinsic_functions.at(expr->m_id->lexeme())(expr, params, ctx);

    return Interpreter::ExprEvalResult{};
}

Interpreter::ExprEvalResult Intrinsics::print(ExprFuncCall *expr, std::vector<Interpreter::ExprEvalResult> params, Ctx &ctx) {
    for (size_t i = 0; i < expr->m_params.size(); ++i) {
        Interpreter::ExprEvalResult param = params[i];

        if (param.m_expr_term_type == ExprTermType::Int_Literal) {
            std::cout << std::any_cast<int>(param.m_expr_value) <<
                (i == expr->m_params.size()-1 ? "" : " ");
        }

        else if (param.m_expr_term_type == ExprTermType::Str_Literal) {
            std::cout << std::any_cast<std::string>(param.m_expr_value) <<
                (i == expr->m_params.size()-1 ? "" : " ");
        }

        // Identifier
        else {
            Token *tok = std::any_cast<Token *>(param.m_expr_value);
            EarlVar *var = ctx.get_earlvar_from_scope(tok->lexeme());
            switch (var->m_type) {
            case EarlTy::Type::Int: {
                std::cout << std::any_cast<int>(var->m_value) << (i == expr->m_params.size()-1 ? "" : " ");
            } break;
            case EarlTy::Type::Str: {
                std::cout << std::any_cast<std::string>(var->m_value) << (i == expr->m_params.size()-1 ? "" : " ");
            } break;
            default:
                ERR_WARGS(ErrType::Fatal, "invalid type for printing (%d)", (int)var->m_type);
            }
        }
    }
    std::cout << '\n';
    return Interpreter::ExprEvalResult{};
}

