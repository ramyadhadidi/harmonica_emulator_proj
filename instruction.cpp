#include "instruction.h"

instruction_c::instruction_c(Word inst) {
  m_predicated = inst & (1LL << (INST_SIZE_BITS-1));
  m_predReg = ( inst & ((PRED_REG_NUM-1LL) << (INST_SIZE_BITS-1-PRED_REG_BIT)) ) >> (INST_SIZE_BITS-1-PRED_REG_BIT);
  Word baa = ( inst & ((pow2(6)-1LL) << (INST_SIZE_BITS-1-PRED_REG_BIT-6)) ) >> (INST_SIZE_BITS-1-PRED_REG_BIT-6);
  DEBUG_PRINT("test: " << hex << (((pow2(6)-1LL) << (INST_SIZE_BITS-1-PRED_REG_BIT-6)) ));

  DEBUG_PRINT("inst: " << hex << inst << dec);
  DEBUG_PRINT("pred: " << m_predicated);
  DEBUG_PRINT("pReg: " << m_predReg);
  DEBUG_PRINT("opCo: " << hex << baa << dec);
  DEBUG_PRINT("\n");
}