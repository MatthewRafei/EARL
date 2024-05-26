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

// File: common.h
// Description:
//   A few things that are useful
//   throughout the entire project.

#ifndef COMMON_H
#define COMMON_H

// Keywords
#define COMMON_EARLKW_LET    "let"
#define COMMON_EARLKW_DEF    "def"
#define COMMON_EARLKW_RETURN "return"
#define COMMON_EARLKW_ASCPL {COMMON_EARLKW_LET, COMMON_EARLKW_DEF, COMMON_EARLKW_RETURN}

// Types
#define COMMON_EARLTY_INT32 "int"
#define COMMON_EARLTY_STR   "str"
#define COMMON_EARLTY_ASCPL {COMMON_EARLTY_INT32, COMMON_EARLTY_STR}

#endif // COMMON_H
