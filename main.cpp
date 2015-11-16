/**
 * @brief
 * @file
 * @author Ramyad Hadidi (rhadidi@gatech.edu)
 * @data 2015-10
 */



#include <cstdlib>
#include <sstream>
#include <vector>
#include <queue>

#include "globals.h"
#include "binReader.h"
#include "core.h"

using namespace std;

/* Configure Architecture in globals.h */
/* 4w8/8/1/1 to 8w/64/64/64/64 */
/*
  4 bytes register and addresses
  word based inst encoding (64bit)
  # general purpose register
  # predicate registers
  # SIMD lane
  # warps
*/

bool exec_finish = false;
ofstream output_file;
ofstream memory_file;

int main(int argc, char** argv) {
  //Input Processing
  if (argc != 4) {
    cerr << "Usage: ./harp_emulator [program] [screen_out_file] [memory_file]\n" ;
    exit(1);
  }
  string binary_filename = argv[1];
  string output_filename = argv[2];
  string memroy_filename = argv[3];


  #ifdef OUTPUT_TO_FILE
    output_file.open(output_filename.c_str());
  #endif

  #ifdef MEMORY_OUTPUT
    memory_file.open(memroy_filename.c_str());
  #endif


  // Execution
  core_c core(binary_filename);
  while(!exec_finish)
    core.step();


  #ifdef OUTPUT_TO_FILE
    output_file.close();
  #endif

  #ifdef MEMORY_OUTPUT
    memory_file.close();
  #endif

  return 0;
}