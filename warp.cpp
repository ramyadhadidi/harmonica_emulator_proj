/**
 * @class warp_c
 * @brief each warps contains of an array of threads, also register files are
 *        alocated in here.
 * @file warp.h warp.cpp
 * @author Ramyad Hadidi
 * @data 2015-10
 */

#include "warp.h"
#include "instruction.h"

warp_c::warp_c() :
  m_warpId(0), m_bin(NULL)
{
  for (int i=0; i<WARP_SIZE; i++) {
    m_pc[i] = 0;
    m_next_pc[i] = 0;
  }
  m_activeThreads = 1;
  m_nextActiveThreads = 1;
}

warp_c::warp_c(const warp_c &warp, binReader_c* bin, unsigned int warpId) {
  if (bin!=NULL) {
    for (int i=0; i<WARP_SIZE; i++) {
      m_pc[i] = 0;
      m_next_pc[i] = 0;
      for (int j=0; j<GPR_REG_NUM; j++)
        m_regRF[i][j] = 0;
      for (int j=0; j<PRED_REG_NUM; j++)
        m_predRF[i][j] = 0;
    }
    m_activeThreads = 1;
    m_nextActiveThreads = 1;

    m_bin = bin;
    m_warpId = warpId;
  }
}

warp_c& warp_c::operator=(const warp_c& warp) {
    for (int i=0; i<WARP_SIZE; i++) {
      this->m_pc[i] = 0;
      this->m_next_pc[i] = 0;
      for (int j=0; j<GPR_REG_NUM; j++)
        this->m_regRF[i][j] = 0;
      for (int j=0; j<PRED_REG_NUM; j++)
        this->m_predRF[i][j] = 0;
      this->m_activeThreads = warp.m_activeThreads;
  }

  this->m_bin = warp.m_bin;
  this->m_warpId = warp.m_warpId;

  return *this;
}

warp_c::warp_c(binReader_c* bin, unsigned int warpId) {
  for (int i=0; i<WARP_SIZE; i++) {
    m_pc[i] = 0;
    m_next_pc[i] = 0;
    for (int j=0; j<GPR_REG_NUM; j++)
      m_regRF[i][j] = 0;
    for (int j=0; j<PRED_REG_NUM; j++)
      m_predRF[i][j] = 0;
  }
  m_activeThreads = 1;
  m_nextActiveThreads = 1;

  m_bin = bin;
  m_warpId = warpId;
}

void warp_c::step() {
  for (unsigned int threadId=0; threadId<m_activeThreads; threadId++) {
    /// get instruction binary
    Word inst_binary = m_bin->get_inst(m_pc[threadId]);
    /// create and instance for the instruction (get all instruction's parameters)
    instruction_c inst = instruction_c(inst_binary);
    /// execute it
    inst.execute(*this, threadId);
  }

  if (m_activeThreads != m_nextActiveThreads) {
    DEBUG_WARP_PRINTF(("warpID %u ActiveThreads changed from %"PRId64" to %"PRId64"\n", m_warpId, m_activeThreads, m_nextActiveThreads));
    m_activeThreads = m_nextActiveThreads;
    if (m_nextActiveThreads > WARP_SIZE) {
      cerr << "Error: attempt to spawn " << m_nextActiveThreads << " threads\n";
      exit(1);
    }
  }
}