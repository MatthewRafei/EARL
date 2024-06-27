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

#include <cassert>

#include "earl.hpp"
#include "err.hpp"

using namespace earl::value;

Str::Str(std::string value) : m_value(std::move(value)) {}

std::string &Str::value(void) {
    return m_value;
}

void Str::fill(std::string value) {
    m_value = std::move(value);
}

Obj *Str::nth(Obj *idx) {
    auto *index = dynamic_cast<Int *>(idx);
    if (index->value() < 0 || static_cast<size_t>(index->value()) > this->value().size()) {
        ERR_WARGS(Err::Type::Fatal, "index %d is out of range of length %zu",
                  index->value(), this->value().size());
    }
    return new earl::value::Char(std::string(1, m_value[index->value()]));
}

Type Str::type(void) const {
    return Type::Str;
}

Obj *Str::binop(Token *op, Obj *other) {
    if (!type_is_compatable(this, other)) {
        assert(false && "cannot binop (fix this message)");
    }

    switch (op->type()) {
    case TokenType::Plus: {
        assert(other->type() == earl::value::Type::Str);
        return new Str(this->value() + dynamic_cast<Str *>(other)->value());
    } break;
    case TokenType::Double_Equals: {
        assert(other->type() == earl::value::Type::Str);
        return new Int(static_cast<int>(this->value() == dynamic_cast<Str *>(other)->value()));
    } break;
    default: {
        Err::err_wtok(op);
        ERR(Err::Type::Fatal, "invalid binary operator");
    }
    }
}

bool Str::boolean(void) {
    return true;
}

void Str::mutate(Obj *other) {
    if (!type_is_compatable(this, other)) {
        assert(false && "cannot mutate (fix this message)");
    }

    switch (other->type()) {
    case Type::Str: {
        this->fill(dynamic_cast<Str *>(other)->value());
    } break;
    default: {
        assert(false && "unreachable");
    }
    }
}

Obj *Str::copy(void) {
    return new Str(this->value());
}
