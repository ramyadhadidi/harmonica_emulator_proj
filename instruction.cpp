#include "instruction.h"

instruction_c::instTableEntry instruction_c::instTable[] = {
  //str        cflow  relad  allsrc priv   argcl        itype
  {"nop",      false, false, false, false, AC_NONE,     ITYPE_NULL    },
  {"di",       false, false, false, true,  AC_NONE,     ITYPE_NULL    },
  {"ei",       false, false, false, true,  AC_NONE,     ITYPE_NULL    },
  {"tlbadd",   false, false, true,  true,  AC_3REGSRC,  ITYPE_NULL    },
  {"tlbflush", false, false, false, true,  AC_NONE,     ITYPE_NULL    },
  {"neg",      false, false, false, false, AC_2REG,     ITYPE_INTBASIC},
  {"not",      false, false, false, false, AC_2REG,     ITYPE_INTBASIC},
  {"and",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"or",       false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"xor",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"add",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"sub",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"mul",      false, false, false, false, AC_3REG,     ITYPE_INTMUL  },
  {"div",      false, false, false, false, AC_3REG,     ITYPE_INTDIV  },
  {"mod",      false, false, false, false, AC_3REG,     ITYPE_INTDIV  },
  {"shl",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"shr",      false, false, false, false, AC_3REG,     ITYPE_INTBASIC},
  {"andi",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"ori",      false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"xori",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"addi",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"subi",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"muli",     false, false, false, false, AC_3IMM,     ITYPE_INTMUL  },
  {"divi",     false, false, false, false, AC_3IMM,     ITYPE_INTDIV  },
  {"modi",     false, false, false, false, AC_3IMM,     ITYPE_INTDIV  },
  {"shli",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"shri",     false, false, false, false, AC_3IMM,     ITYPE_INTBASIC},
  {"jali",     true,  true,  false, false, AC_2IMM,     ITYPE_CALL    },
  {"jalr",     true,  false, false, false, AC_2REG,     ITYPE_CALL    },
  {"jmpi",     true,  true,  true,  false, AC_1IMM,     ITYPE_BR      },
  {"jmpr",     true,  false, true,  false, AC_1REG,     ITYPE_RET     },
  {"clone",    true,  false, false, false, AC_1REG,     ITYPE_NULL    },
  {"jalis",    true,  true,  false, false, AC_3IMM,     ITYPE_CALL    },
  {"jalrs",    true,  false, false, false, AC_3REG,     ITYPE_CALL    },
  {"jmprt",    true,  false, true,  false, AC_1REG,     ITYPE_RET     },
  {"ld",       false, false, false, false, AC_3IMM,     ITYPE_NULL    },
  {"st",       false, false, true,  false, AC_3IMMSRC,  ITYPE_NULL    },
  {"ldi",      false, false, false, false, AC_2IMM,     ITYPE_NULL    },
  {"rtop",     false, false, false, false, AC_PREG_REG, ITYPE_NULL    },
  {"andp",     false, false, false, false, AC_3PREG,    ITYPE_INTBASIC},
  {"orp",      false, false, false, false, AC_3PREG,    ITYPE_INTBASIC},
  {"xorp",     false, false, false, false, AC_3PREG,    ITYPE_INTBASIC},
  {"notp",     false, false, false, false, AC_2PREG,    ITYPE_INTBASIC},
  {"isneg",    false, false, false, false, AC_PREG_REG, ITYPE_INTBASIC},
  {"iszero",   false, false, false, false, AC_PREG_REG, ITYPE_INTBASIC},
  {"halt",     false, false, false, false, AC_NONE,     ITYPE_NULL    },
  {"trap",     true,  false, false, false, AC_NONE,     ITYPE_TRAP    },
  {"jmpru",    false, false, false, true,  AC_1REG,     ITYPE_RET     },
  {"skep",     false, false, false, true,  AC_1REG,     ITYPE_NULL    },
  {"reti",     true,  false, false, true,  AC_NONE,     ITYPE_RET     },
  {"tlbrm",    false, false, false, true,  AC_1REG,     ITYPE_NULL    },
  {"itof",     false, false, false, false, AC_2REG,     ITYPE_FPBASIC },
  {"ftoi",     false, false, false, false, AC_2REG,     ITYPE_FPBASIC },
  {"fadd",     false, false, false, false, AC_3REG,     ITYPE_FPBASIC },
  {"fsub",     false, false, false, false, AC_3REG,     ITYPE_FPBASIC },
  {"fmul",     false, false, false, false, AC_3REG,     ITYPE_FPMUL   },
  {"fdiv",     false, false, false, false, AC_3REG,     ITYPE_FPDIV   },
  {"fneg",     false, false, false, false, AC_2REG,     ITYPE_FPBASIC },
  {"wspawn",   false, false, true,  false, AC_3REG,     ITYPE_NULL    },
  {"split",    false, false, true,  false, AC_NONE,     ITYPE_NULL    },
  {"join",     false, false, true,  false, AC_NONE,     ITYPE_NULL    },
  {"bar",      false, false, true,  false, AC_2REGSRC,  ITYPE_NULL    },
  {NULL,false,false,false,false,AC_NONE,ITYPE_NULL}/////// End of table.
};

instruction_c::instruction_c(Word inst) {
  m_predicated = ( inst >> (INST_SIZE_BITS-1) ) & 1LL;
  m_predReg = ( inst  >> (INST_SIZE_BITS-1-PRED_REG_BIT) ) & (PRED_REG_NUM-1LL);
  m_op = static_cast<Opcode> ( ( inst >> (INST_SIZE_BITS-1-PRED_REG_BIT-6) ) & (pow2(6)-1LL) );

  DEBUG_PRINT("inst: " << hex << inst << dec);
  DEBUG_PRINT("pred: " << m_predicated);
  DEBUG_PRINT("pReg: " << m_predReg);
  DEBUG_PRINT("opCode: " << hex << m_op << dec);
  DEBUG_PRINT("\n");
}