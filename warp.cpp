#include "warp.h"
#include "instruction.h"

warp_c::warp_c() :
  m_bin(NULL)
{
  for (int i=0; i<WARP_SIZE; i++) {
    m_pc[i] = 0;
    m_next_pc[i] = 0;
  }
}

warp_c::warp_c(const warp_c &warp, binReader_c* bin) {
  if (bin!=NULL) {
    for (int i=0; i<WARP_SIZE; i++) {
      m_pc[i] = 0;
      m_next_pc[i] = 0;
      for (int j=0; j<GPR_REG_NUM; j++)
        m_regRF[i][j] = 0;
      for (int j=0; j<PRED_REG_NUM; j++)
        m_predRF[i][j] = 0;
    }

    m_bin = bin;
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
  }

  this->m_bin = warp.m_bin;

  return *this;
}

warp_c::warp_c(binReader_c* bin) {
  for (int i=0; i<WARP_SIZE; i++) {
    m_pc[i] = 0;
    m_next_pc[i] = 0;
    for (int j=0; j<GPR_REG_NUM; j++)
      m_regRF[i][j] = 0;
    for (int j=0; j<PRED_REG_NUM; j++)
      m_predRF[i][j] = 0;
  }

  m_bin = bin;
}

void warp_c::step() {
  for (int threadId=0; threadId<WARP_SIZE; threadId++) {
    instruction_c inst = instruction_c(m_bin->get_inst(m_pc[threadId]));
    inst.execute(*this, threadId);
    m_pc[threadId] += STEP_PC;

    if(exec_finish) {
      cout << "ME" << endl;
      exit(1);
    }
  }
}