/**
 * @class warp_c
 * @brief each warps contains of an array of threads, also register files are
 *        alocated in here.
 * @file warp.h warp.cpp
 * @author Ramyad Hadidi
 * @data 2015-10
 */

#ifndef WARP_H
#define WARP_H

#include <iostream>
#include <vector>
#include "globals.h"
#include "binReader.h"

using namespace std;

class warp_c {
  /** @brief Since each thread in a warp will changes its state, instruction_c class have access to this class */
  friend class instruction_c;

  public:
    /**
     * Default Constructor
     * Should not be used for creating warps, if used use assignment or copy constructor
     * afterwards
     */
    warp_c();
    /**
     * Copy Constructor
     * @param bin binReader_c pointer, created by core_c
     * @param warpID each warp has an ID which will differciate them from other warps
     * This constructor will reset all register files, get pointer to binary reader
     * for reading data and instruction and reset all pc values
     */
    warp_c(const warp_c &warp, binReader_c* bin=NULL, unsigned int warpId=0);
    warp_c& operator=(const warp_c& warp);
    /**
     * Main Constructor
     * @param bin binReader_c pointer to access instruction and data
     * @param warpId 
     */
    warp_c(binReader_c* bin, unsigned int warpId);

    /**
     *  @biref execute a single instruction from each thread in warp
     *  Executes a single instruction from each thread in warp, will use warp_c::m_pc to determine next 
     */
    void step();

  private:
    unsigned int m_warpId;
    binReader_c *m_bin;

    Addr m_pc[WARP_SIZE];
    Addr m_next_pc[WARP_SIZE];

    /** GPR resiter file */
    Word m_regRF[WARP_SIZE][GPR_REG_NUM];
    /** Predicate resiter file */
    bool m_predRF[WARP_SIZE][PRED_REG_NUM];
};

#endif