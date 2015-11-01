/**
 * @class core_c
 * @brief Core is the main hardware unit tha executes warps
 * @file core.h core.cpp
 * @author Ramyad Hadidi (rhadidi@gatech.edu)
 * @data 2015-10
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include "globals.h"
#include "warp.h"

using namespace std;

/**
 * @brief core_c class is the main hardward unit 
 * Each core consist of multiple warps @see warp_c    
 */
class core_c {

  public:
    core_c();
    /**
     *  @param filename binary file name
     *  The constructor will open the binary file and pass the pointer to 
     *  its classes @see warp_c @see binaryReader_c.
     */
    core_c(string filename);
    /**
     *  This function execute the core for one step, which means a single step
     *  for warps and in each warp a single step for all threads.
     */
    void step();

  private:
    string m_binary_filename;
    binReader_c m_bin;

    warp_c* m_warps;

    /**ActiveSM**/
    bool m_activeWarp[SIMD_LANE_NUM];

};

#endif