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

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "vector.h"

void *
vector_at(struct vector *v, size_t i)
{
#ifdef DEBUG
  assert(i < v->len);
#endif
  return v->data + i * v->stride;
}

void
vector_append(struct vector *v, void *data)
{
  size_t s = v->stride;
  if (v->len >= v->cap) {
    v->cap *= 2;
    v->data = realloc(v->data, v->cap*s);
  }
  (void)memcpy(v->data + v->len*s, (uint8_t *)data, s);
  v->len++;
}

void
vector_free(struct vector *v)
{
  free(v->data);
  v->data = NULL;
  v->len = v->cap = v->stride = 0;
}
