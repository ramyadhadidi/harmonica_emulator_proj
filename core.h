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
#include <vector>
#include "globals.h"
#include "binReader.h"

using namespace std;

class warp_c;

/**
 * @brief core_c class is the main hardward unit 
 * Each core consist of multiple warps @see warp_c    
 */
class core_c {
  friend class warp_c;
  friend class instruction_c;

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
    bool m_activeWarp[WARP_SIZE];

    /**Barriers**/
    map<Word, set<warp_c *> > bar;
};

/**
 * @class warp_c
 * @brief each warps contains of an array of threads, also register files are
 *        alocated in here.
 * @file warp.h warp.cpp
 * @author Ramyad Hadidi
 * @data 2015-10
 */

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
    warp_c(const warp_c &warp, core_c *core=NULL, binReader_c* bin=NULL, unsigned int warpId=0);
    warp_c& operator=(const warp_c& warp);
    /**
     * Main Constructor
     * @param bin binReader_c pointer to access instruction and data
     * @param warpId 
     */
    warp_c(core_c *core, binReader_c* bin, unsigned int warpId);

    /**
     *  @biref execute a single instruction from each thread in warp
     *  Executes a single instruction from each thread in warp, will use warp_c::m_pc to determine next 
     */
    void step();

  private:
    core_c *m_core;

    unsigned int m_warpId;
    binReader_c *m_bin;

    Addr m_pc;
    Addr m_next_pc;
    bool m_pc_changed;

    /** GPR resiter file */
    Word m_regRF[SIMD_LANE_NUM][GPR_REG_NUM];
    /** Predicate resiter file */
    bool m_predRF[SIMD_LANE_NUM][PRED_REG_NUM];

    /**ActiveThreads**/
    Size m_activeThreads;
    Size m_shadowActiveThreads;         //For implementing barriers
    Size m_nextActiveThreads;
};

#endif