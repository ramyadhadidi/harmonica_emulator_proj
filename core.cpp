/**
 * @class core_c
 * @brief Core is the main hardware unit tha executes warps
 * @file core.h core.cpp
 * @author Ramyad Hadidi (rhadidi@gatech.edu)
 * @data 2015-10
 */

#include "core.h"
#include "instruction.h"

core_c::core_c() 
  : m_binary_filename("")
{

}

core_c::core_c(string filename) {
  m_binary_filename = filename;
  m_bin.set_filename(filename);

  m_warps = new warp_c[WARP_SIZE];
  for(unsigned int warpId=0; warpId<WARP_SIZE; warpId++) {
    m_warps[warpId] = warp_c(this, &m_bin, warpId);
    m_activeWarpMask[warpId] = false;
  }
  m_activeWarps = 1;
  m_nextActiveWarps = 1;
  m_activeWarpMask[0] = true;
  m_warpSizeChanged = false;
}

void core_c::step() {

  m_warpSizeChanged = false;

  //Execute each Warp
  for(unsigned int warpId=0; warpId<m_activeWarps; warpId++)
    if (m_activeWarpMask[warpId])
      m_warps[warpId].step();

  //Warp Size update (spawn)
  if (m_warpSizeChanged) {
    DEBUG_CORE_PRINTF(("|--> Change of Active Warps from %"PRId64" to %"PRId64"\n", m_activeWarps, m_nextActiveWarps));
    if (m_nextActiveWarps > WARP_SIZE) {
      cerr << "Error: attempt to spawn " << m_nextActiveWarps << " warps\n";
      exit(1);
    }
    m_activeWarps = m_nextActiveWarps;
  }

  //Check for HALT in all warps
  bool is_all_halt = true;
  for(unsigned int warpId=0; warpId<WARP_SIZE; warpId++) {
    if(m_activeWarpMask[warpId])
      is_all_halt = false;
  }
  if(is_all_halt) {
    DEBUG_CORE_PRINTF(("|--> HALT ALL WARPS :: STOP\n"));
    exec_finish = true;
  }

}

/**
 * @class warp_c
 * @brief each warps contains of an array of threads, also register files are
 *        alocated in here.
 * @file warp.h warp.cpp
 * @author Ramyad Hadidi
 * @data 2015-10
 */

warp_c::warp_c() :
  m_core(NULL), m_warpId(0), m_bin(NULL)
{
  for (int i=0; i<SIMD_LANE_NUM; i++) {
    for (int j=0; j<GPR_REG_NUM; j++)
      m_regRF[i][j] = 0;
    for (int j=0; j<PRED_REG_NUM; j++)
      m_predRF[i][j] = 0;
    m_threadMask[i] = true;
  }
  m_pc = 0;
  m_next_pc = 0;
  m_activeThreads = 1;
  m_nextActiveThreads = 1;
}

warp_c::warp_c(const warp_c &warp, core_c *core, binReader_c* bin, unsigned int warpId) {
  if (bin!=NULL) {
    for (int i=0; i<SIMD_LANE_NUM; i++) {
      for (int j=0; j<GPR_REG_NUM; j++)
        m_regRF[i][j] = 0;
      for (int j=0; j<PRED_REG_NUM; j++)
        m_predRF[i][j] = 0;
      m_threadMask[i] = true;
    }
    m_pc = 0;
    m_next_pc = 0;
    m_activeThreads = 1;
    m_nextActiveThreads = 1;

    m_bin = bin;
    m_warpId = warpId;
    m_core = core;
  }
}

warp_c& warp_c::operator=(const warp_c& warp) {
    for (int i=0; i<SIMD_LANE_NUM; i++) {
      for (int j=0; j<GPR_REG_NUM; j++)
        this->m_regRF[i][j] = 0;
      for (int j=0; j<PRED_REG_NUM; j++)
        this->m_predRF[i][j] = 0;
      this->m_activeThreads = warp.m_activeThreads;
      this->m_threadMask[i] = warp.m_threadMask[i];
  }
  this->m_pc = warp.m_pc;
  this->m_next_pc = warp.m_next_pc;
  this->m_bin = warp.m_bin;
  this->m_warpId = warp.m_warpId;
  this->m_core = warp.m_core;

  return *this;
}

warp_c::warp_c(core_c *core, binReader_c* bin, unsigned int warpId) {
  for (int i=0; i<SIMD_LANE_NUM; i++) {
    for (int j=0; j<GPR_REG_NUM; j++)
      m_regRF[i][j] = 0;
    for (int j=0; j<PRED_REG_NUM; j++)
      m_predRF[i][j] = 0;
    m_threadMask[i] = true;
  }
  m_pc = 0;
  m_next_pc = 0;
  m_activeThreads = 1;
  m_nextActiveThreads = 1;

  m_bin = bin;
  m_warpId = warpId;
  m_core = core;
}

void warp_c::step() {
  //Debug
  DEBUG_PC_PRINT((m_pc));
  DEBUG_WARP_PRINTF(("||--> WarpID %u: PC 0x%"PRIx64"\n", m_warpId, m_pc));
  DEBUG_WARP_PRINTF(("||--> WarpID %u: # Active Threads %"PRId64"\n", m_warpId, m_activeThreads));
  DEBUG_WARP_PRINTF(("||--> WarpID %u: Thread Masks\t", m_warpId));
  for (int _threadID=0; _threadID<SIMD_LANE_NUM; _threadID++)
    DEBUG_WARP_PRINTF(("%x ", m_threadMask[_threadID]));
  DEBUG_WARP_PRINTF(("\n"));

  //Reconverge Support: for just pushing and poping one element in stack
  m_splitJoinOnce = false;

  //Since all jump addresses are same, just one change is enough
  m_pc_changed = false;

  //To check if the current inst is memory refrence or not (for memory trace and coalescing)
  m_isMemInst = false;

  //Exectuion
  for (unsigned int threadId=0; threadId<m_activeThreads; threadId++) {
    /// get instruction binary
    Word inst_binary = m_bin->get_inst(m_pc);
    /// create and instance for the instruction (get all instruction's parameters)
    instruction_c inst = instruction_c(inst_binary);
    /// execute it
    inst.execute(*this, threadId);
  }

  //PC change
  if (m_activeThreads != 0) {  
    if (!m_pc_changed)
        m_next_pc = m_pc + STEP_PC;
    //Jump to Same PC (infinite loop :: JMPI -4)
    if (m_pc == m_next_pc)
      exec_finish = true;
    m_pc = m_next_pc;
  }

  // Active Threads
  if (m_activeThreads != m_nextActiveThreads) {
    DEBUG_WARP_PRINTF(("||--> WarpID %u: #Active Threads changed from %"PRId64" to %"PRId64"\n", m_warpId, m_activeThreads, m_nextActiveThreads));
    m_activeThreads = m_nextActiveThreads;
    if(m_nextActiveThreads > SIMD_LANE_NUM) {
      cerr << "Error: attempt to spawn " << m_nextActiveThreads << " threads\n";
      exit(1);
    }
  }

  //Memory Trace
  #ifdef MEMORY_OUTPUT
  if (m_isMemInst) {
    memory_file << (m_isWrite ? 'w' : 'r') << "\t" << "0x" << hex << m_memAddr[0] << dec << endl;
  }
  #endif

  DEBUG_WARP_PRINTF(("\n"));
}