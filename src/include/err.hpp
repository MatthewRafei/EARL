/** @file */

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

/**
 * Provides an easy way of displaying
 * error messages and crashing.
 */

#include "token.hpp"

#ifndef ERR_H
#define ERR_H

/// @brief The namespace for all errors
namespace Err {
    /// @brief The different classes of errors
    /// that can be issued.
    enum class Type {
        /** Used for syntactical errors, usually during parsing */
        Syntax,
        /** Used for errors that ocur during runtime */
        Runtime,
        /** An internal error */
        Internal,
        /** Unrecoverable error */
        Fatal,
        /** Variable was redeclared at runtime */
        Redeclared,
        /** Varriable is undeclared at runtime */
        Undeclared,
        /** Incorrect usage of a type during runtime */
        Types,
        /** For use during development of TODO functions */
        Todo,
    };

    void err_wtok(Token *tok);
    void err_wconflict(Token *tok1, Token *tok2);
};


/// \brief Prints a error message of type `errtype`
/// with the message `msg` with any arguments of VA_ARGS.
#define ERR_WARGS(errtype, msg, ...)            \
    do {                                        \
        fprintf(stderr, "%s: ", __func__);      \
        fprintf(stderr, msg, __VA_ARGS__);      \
        fprintf(stderr, "\n");                  \
        std::exit(1);                           \
    } while (0)

/// @brief Prints a error message of type `errtype`
/// with the message `msg` with no arguments.
#define ERR(errtype, msg)                       \
    do {                                        \
        fprintf(stderr, "%s: ", __func__);      \
        fprintf(stderr, msg);                   \
        fprintf(stderr, "\n");                  \
        std::exit(1);                           \
    } while (0)

#endif // ERR_H
