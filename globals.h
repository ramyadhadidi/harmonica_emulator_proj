/**
 * @brief Global definitions, variables and architecture setting
 * @file
 * @author Ramyad Hadidi (rhadidi@gatech.edu)
 * @data 2015-10
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

#include <map>
#include <set>
#include <stack>

/** @brief Prints instructions debug messages */
//#define DEBUG

/** @brief prints warp debug messages: PC, warp States */
//#define DEBUG_WARP

/** @brief prints core: number of warp changes */
//#define DEBUG_CORE

/** @brief Just prints PC **/
//#define DEBUG_PC

#ifdef DEBUG
#define DEBUG_PRINT(X) cout << X << endl;
#define DEBUG_PRINTF(x) printf x;
#else
#define DEBUG_PRINT(X) do {} while (0);
#define DEBUG_PRINTF(x) do {} while (0);
#endif

#ifdef DEBUG_WARP
#define DEBUG_WARP_PRINT(X) cout << X << endl;
#define DEBUG_WARP_PRINTF(x) printf x;
#else
#define DEBUG_WARP_PRINT(X) do {} while (0);
#define DEBUG_WARP_PRINTF(x) do {} while (0);
#endif

#ifdef DEBUG_CORE
#define DEBUG_CORE_PRINT(X) cout << X << endl;
#define DEBUG_CORE_PRINTF(x) printf x;
#else
#define DEBUG_CORE_PRINT(X) do {} while (0);
#define DEBUG_CORE_PRINTF(x) do {} while (0);
#endif

#ifdef DEBUG_PC
#define DEBUG_PC_PRINT(X) cout << hex << X << endl;
#else
#define DEBUG_PC_PRINT(X) do {} while (0);
#endif

/** @brief save output to the file at argv[2], else to stdout */
#define OUTPUT_TO_FILE 

////////////////////////////////////////////////////////////////
// Harp Architecture Setting                                  //
////////////////////////////////////////////////////////////////
                                                              //
/** 4w8/8/1/1 to 8w/64/64/64/64 */                            //
/**                                                           //
 * 4 bytes register and addresses                             //
 * word based inst encoding (64bit)                           //
 * # general purpose registers                                //
 * # predicate registers                                      //
 * # SIMD Number of SM (1warp/SM)                             //
 * # warps                                                    //
*/                                                            //
                                                              //
                                                              //
#define WORD_SIZE_IN_BYTE 4                                   //
#define GPR_REG_NUM 8                                         //
#define PRED_REG_NUM 8                                        //
#define SIMD_LANE_NUM 8                                       //
#define WARP_SIZE 8                                           //
                                                              //
////////////////////////////////////////////////////////////////

#define WORD_SIZE_IN_BITS WORD_SIZE_IN_BYTE*8
#define INST_SIZE_BITS WORD_SIZE_IN_BYTE*8
#define PRED_REG_BIT (int)log2(PRED_REG_NUM)
#define GPR_REG_BIT (int)log2(GPR_REG_NUM)

#define STEP_PC WORD_SIZE_IN_BYTE

/** @brief max registers that could be in single instruction */
#define MAX_REG_SOURCES 3
#define MAX_PREG_SOURCES 3

/** typedefs */
typedef uint8_t  Byte;
typedef uint64_t Word;
typedef uint64_t Word_u;
typedef int64_t  Word_s;
typedef uint32_t uint32;

typedef Word_u   Addr;
typedef Word_u   Size;

typedef unsigned RegNum;

/** @breif global value of exection is finished or not (currently all thread can access it) */
extern bool exec_finish;

/** @brief global output file stream, defined in main.cpp */
extern std::ofstream output_file;

#endif