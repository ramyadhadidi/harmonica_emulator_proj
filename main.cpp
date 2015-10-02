#include <cstdlib>
#include <sstream>
#include <vector>
#include <queue>

#include "globals.h"
#include "util.h"
#include "core.h"

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

bool exec_finish = false;
ofstream output_file;

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: ./harp_emulator program output_generated\n" ;
    exit(1);
  }
  string binary_filename = argv[1];
  string output_filename = argv[2];

  #ifdef OUTPUT_TO_FILE
    output_file.open(output_filename.c_str());
  #endif


  core_c core(binary_filename);
  while(!exec_finish)
    core.step();


  #ifdef OUTPUT_TO_FILE
    output_file.close();
  #endif

  /*
  while(!exe_end) {
    cout << PC << endl;
    instruction_c(bin.get_inst(PC));
    //cout << hex << bin.get_inst(PC) << endl;
    PC += STEP_PC;
    if (PC>100)
      exe_end = true;
  }
  */
  return 0;
}