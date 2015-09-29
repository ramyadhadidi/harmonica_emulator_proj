#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "globals.h"
#include "util.h"
#include "instruction.h"

using namespace std;

/* 4w8/8/1/1 to 8w/64/64/64/64 */
/*
  4 bytes register and addresses
  word based inst encoding (64bit)
  # general purpose register
  # predicate registers
  # SIMD lane
  # warps
*/

bool exe_end = false;

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: ./harp_emulator program output_generated\n" ;
    exit(1);
  }

  binReader_c bin(argv[1]);
  while(!exe_end) { 
    instruction_c(bin.get_inst());
    //cout << bin.get_inst();
    //exe_end = true;
  }
  return 0;
}