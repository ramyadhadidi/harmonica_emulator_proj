#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <math.h>

#define pow2(X) (int)pow(2,X)

#define DEBUG_PRINT(X) \
    if (DEBUG) \
    cout << X << endl; 

#define DEBUG 1

/* 4w8/8/1/1 to 8w/64/64/64/64 */
/*
  4 bytes register and addresses
  word based inst encoding (64bit)
  # general purpose register
  # predicate registers
  # SIMD lane
  # warps
*/


#define WORD_SIZE_IN_BYTE 4
#define GPR_REG_NUM 8
#define PRED_REG_NUM 8


#define INST_SIZE_BITS WORD_SIZE_IN_BYTE*8
#define PRED_REG_BIT (int)log2(PRED_REG_NUM)
#define GPR_REG_BIT (int)log2(GPR_REG_NUM)

#define STEP_PC WORD_SIZE_IN_BYTE


typedef uint8_t  Byte;
typedef uint64_t Word;
typedef uint64_t Word_u;
typedef int64_t  Word_s;

typedef Word_u   Addr;
typedef Word_u   Size;

typedef unsigned RegNum;

#endif