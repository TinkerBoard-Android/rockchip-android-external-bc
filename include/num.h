/*
 * *****************************************************************************
 *
 * Copyright 2018 Gavin D. Howard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * *****************************************************************************
 *
 * Definitions for the num type.
 *
 */

#ifndef BC_NUM_H
#define BC_NUM_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <status.h>

typedef signed char BcDigit;

typedef struct BcNum {

  BcDigit *num;
  size_t rdx;
  size_t len;
  size_t cap;
  bool neg;

} BcNum;

#define BC_NUM_MIN_BASE (2)
#define BC_NUM_MAX_INPUT_BASE (16)
#define BC_NUM_DEF_SIZE (16)
#define BC_NUM_PRINT_WIDTH (69)

#define BC_NUM_ONE(n) ((n)->len == 1 && (n)->rdx == 0 && (n)->num[0] == 1)
#define BC_NUM_INT(n) ((n)->len - (n)->rdx)
#define BC_NUM_AREQ(a, b) \
  (BC_MAX((a)->rdx, (b)->rdx) + BC_MAX(BC_NUM_INT(a), BC_NUM_INT(b)) + 1)
#define BC_NUM_MREQ(a, b, scale) \
  (BC_NUM_INT(a) + BC_NUM_INT(b) + BC_MAX((scale), (a)->rdx + (b)->rdx))

typedef BcStatus (*BcNumBinaryOp)(BcNum*, BcNum*, BcNum*, size_t);
typedef BcStatus (*BcNumDigitOp)(size_t, size_t, bool, size_t*, size_t);

BcStatus bc_num_init(BcNum *n, size_t request);
BcStatus bc_num_expand(BcNum *n, size_t request);
BcStatus bc_num_copy(BcNum *d, BcNum *s);
void bc_num_free(void *num);

BcStatus bc_num_ulong(BcNum *n, unsigned long *result);
BcStatus bc_num_ulong2num(BcNum *n, unsigned long val);

ssize_t bc_num_cmp(BcNum *a, BcNum *b);

BcStatus bc_num_add(BcNum *a, BcNum *b, BcNum *res, size_t scale);
BcStatus bc_num_sub(BcNum *a, BcNum *b, BcNum *res, size_t scale);
BcStatus bc_num_mul(BcNum *a, BcNum *b, BcNum *res, size_t scale);
BcStatus bc_num_div(BcNum *a, BcNum *b, BcNum *res, size_t scale);
BcStatus bc_num_mod(BcNum *a, BcNum *b, BcNum *res, size_t scale);
BcStatus bc_num_pow(BcNum *a, BcNum *b, BcNum *res, size_t scale);

// ** Exclude start. **
BcStatus bc_num_sqrt(BcNum *a, BcNum *res, size_t scale);

void bc_num_zero(BcNum *n);
void bc_num_one(BcNum *n);
void bc_num_ten(BcNum *n);

BcStatus bc_num_parse(BcNum *n, const char *val, BcNum *base, size_t base_t);
BcStatus bc_num_print(BcNum *n, BcNum *base, size_t base_t, bool newline,
                      size_t *nchars, size_t line_len);
// ** Exclude end. **

extern const char bc_num_hex_digits[];

#endif // BC_NUM_H
