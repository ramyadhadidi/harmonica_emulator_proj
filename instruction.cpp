#include "instruction.h"

instruction_c::instTableEntry instruction_c::instTable[] = {
  //str        cflow  relad  allsrc priv   argcl       argcstr          itype
  {"nop",      false, false, false, false, AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"di",       false, false, false, true,  AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"ei",       false, false, false, true,  AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"tlbadd",   false, false, true,  true,  AC_3REGSRC,  "AC_3REGSRC",   ITYPE_NULL    },
  {"tlbflush", false, false, false, true,  AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"neg",      false, false, false, false, AC_2REG,     "AC_2REG",      ITYPE_INTBASIC},
  {"not",      false, false, false, false, AC_2REG,     "AC_2REG",      ITYPE_INTBASIC},
  {"and",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"or",       false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"xor",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"add",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"sub",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"mul",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTMUL  },
  {"div",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTDIV  },
  {"mod",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTDIV  },
  {"shl",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"shr",      false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_INTBASIC},
  {"andi",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"ori",      false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"xori",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"addi",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"subi",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"muli",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTMUL  },
  {"divi",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTDIV  },
  {"modi",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTDIV  },
  {"shli",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"shri",     false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_INTBASIC},
  {"jali",     true,  true,  false, false, AC_2IMM,     "AC_2IMM",      ITYPE_CALL    },
  {"jalr",     true,  false, false, false, AC_2REG,     "AC_2REG",      ITYPE_CALL    },
  {"jmpi",     true,  true,  true,  false, AC_1IMM,     "AC_1IMM",      ITYPE_BR      },
  {"jmpr",     true,  false, true,  false, AC_1REG,     "AC_1REG",      ITYPE_RET     },
  {"clone",    true,  false, false, false, AC_1REG,     "AC_1REG",      ITYPE_NULL    },
  {"jalis",    true,  true,  false, false, AC_3IMM,     "AC_3IMM",      ITYPE_CALL    },
  {"jalrs",    true,  false, false, false, AC_3REG,     "AC_3REG",      ITYPE_CALL    },
  {"jmprt",    true,  false, true,  false, AC_1REG,     "AC_1REG",      ITYPE_RET     },
  {"ld",       false, false, false, false, AC_3IMM,     "AC_3IMM",      ITYPE_NULL    },
  {"st",       false, false, true,  false, AC_3IMMSRC,  "AC_3IMMSRC",   ITYPE_NULL    },
  {"ldi",      false, false, false, false, AC_2IMM,     "AC_2IMM",      ITYPE_NULL    },
  {"rtop",     false, false, false, false, AC_PREG_REG, "AC_PREG_REG",  ITYPE_NULL    },
  {"andp",     false, false, false, false, AC_3PREG,    "AC_3PREG",     ITYPE_INTBASIC},
  {"orp",      false, false, false, false, AC_3PREG,    "AC_3PREG",     ITYPE_INTBASIC},
  {"xorp",     false, false, false, false, AC_3PREG,    "AC_3PREG",     ITYPE_INTBASIC},
  {"notp",     false, false, false, false, AC_2PREG,    "AC_2PREG",     ITYPE_INTBASIC},
  {"isneg",    false, false, false, false, AC_PREG_REG, "AC_PREG_REG",  ITYPE_INTBASIC},
  {"iszero",   false, false, false, false, AC_PREG_REG, "AC_PREG_REG",  ITYPE_INTBASIC},
  {"halt",     false, false, false, false, AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"trap",     true,  false, false, false, AC_NONE,     "AC_NONE",      ITYPE_TRAP    },
  {"jmpru",    false, false, false, true,  AC_1REG,     "AC_1REG",      ITYPE_RET     },
  {"skep",     false, false, false, true,  AC_1REG,     "AC_1REG",      ITYPE_NULL    },
  {"reti",     true,  false, false, true,  AC_NONE,     "AC_NONE",      ITYPE_RET     },
  {"tlbrm",    false, false, false, true,  AC_1REG,     "AC_1REG",      ITYPE_NULL    },
  {"itof",     false, false, false, false, AC_2REG,     "AC_2REG",      ITYPE_FPBASIC },
  {"ftoi",     false, false, false, false, AC_2REG,     "AC_2REG",      ITYPE_FPBASIC },
  {"fadd",     false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_FPBASIC },
  {"fsub",     false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_FPBASIC },
  {"fmul",     false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_FPMUL   },
  {"fdiv",     false, false, false, false, AC_3REG,     "AC_3REG",      ITYPE_FPDIV   },
  {"fneg",     false, false, false, false, AC_2REG,     "AC_2REG",      ITYPE_FPBASIC },
  {"wspawn",   false, false, true,  false, AC_3REG,     "AC_3REG",      ITYPE_NULL    },
  {"split",    false, false, true,  false, AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"join",     false, false, true,  false, AC_NONE,     "AC_NONE",      ITYPE_NULL    },
  {"bar",      false, false, true,  false, AC_2REGSRC,  "AC_2REGSRC",   ITYPE_NULL    },
  {NULL,false,false,false,false,AC_NONE,NULL,ITYPE_NULL}/////// End of table.
};

instruction_c::instruction_c(Word inst) :
  m_predicated(false), m_destReg(0), m_destPReg(0),
  m_nRsrc(0), m_nPsrc(0), m_immsrcPresent(false), m_srcImm(0)
  {
  //Shared Fields
  int current_right_shift = 0;

  current_right_shift = INST_SIZE_BITS-1;
  setPredicated(( inst >> current_right_shift ) & 1LL);
  current_right_shift -= PRED_REG_BIT;
  setPredReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
  current_right_shift -= 6;
  setOpCode(static_cast<Opcode> ( ( inst >> current_right_shift ) & (pow2(6)-1LL) ));

  //Individual Fields
  switch (instTable[m_op].argClass) {
    case AC_NONE:
      break;

    case AC_2REG:
      current_right_shift -= GPR_REG_BIT;
      setDestReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;

    case AC_2IMM:
      current_right_shift -= GPR_REG_BIT;
      setDestReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      setImmSrc(inst & ( pow2(current_right_shift) - 1 ));
      break;

    case AC_3REG:
      current_right_shift -= GPR_REG_BIT;
      setDestReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;

    case AC_3PREG: 
      current_right_shift -= PRED_REG_BIT;
      setDestPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      current_right_shift -= PRED_REG_BIT;
      setSrcPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      current_right_shift -= PRED_REG_BIT;
      setSrcPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      break;

    case AC_3IMM:
      current_right_shift -= GPR_REG_BIT;
      setDestReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      setImmSrc(inst & ( pow2(current_right_shift) - 1 ));
      break;

    case AC_3REGSRC:
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;

    case AC_1IMM:
      setImmSrc(inst & ( pow2(current_right_shift) - 1 ));
      break;

    case AC_1REG:
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;

    case AC_3IMMSRC:
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      setImmSrc(inst & ( pow2(current_right_shift) - 1 ));
      break;

    case AC_PREG_REG:
      current_right_shift -= PRED_REG_BIT;
      setDestPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;
    case AC_2PREG:
      current_right_shift -= PRED_REG_BIT;
      setDestPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      current_right_shift -= PRED_REG_BIT;
      setSrcPReg(( inst  >> current_right_shift ) & (PRED_REG_NUM-1LL));
      break;
    case AC_2REGSRC:
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      current_right_shift -= GPR_REG_BIT;
      setSrcReg(( inst  >> current_right_shift ) & (GPR_REG_NUM-1LL));
      break;
    default:
      cerr << "Unknown argument class." << endl;
  }


  DEBUG_PRINT("inst: " << hex << inst << dec);
  DEBUG_PRINT("pred: " << m_predicated);
  DEBUG_PRINT("pReg: " << m_predReg);
  DEBUG_PRINT("opCode: " << instTable[m_op].opString << " 0x" << hex << m_op << dec);
  DEBUG_PRINT("argClass: " << instTable[m_op].argClassString);
  DEBUG_PRINT("---------------")
  DEBUG_PRINT("Rdest: " << m_destReg);
  DEBUG_PRINT("Pdest: " << m_destPReg);
  DEBUG_PRINT("nRsrc: " << m_nRsrc);
  DEBUG_PRINT("nPsrc: " << m_nPsrc);
  DEBUG_PRINT("Rsrc 0 1 2: " << m_srcReg[0] << " " << m_srcReg[1] << " "  << m_srcReg[2]);
  DEBUG_PRINT("Psrc 0 1 2: " << m_srcPReg[0] << " " << m_srcPReg[1] << " "  << m_srcPReg[2]);
  DEBUG_PRINT("immSrc: " << hex << m_srcImm << dec);
  DEBUG_PRINT("\n");
}