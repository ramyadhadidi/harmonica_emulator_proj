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

Word instruction_c::signExt(Word s, Word last_bit) {
  if (s >> (last_bit-1))
    s |= ~(pow2(last_bit)-1);
  return s;
}

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
      setImmSrc(signExt((inst & ( pow2(current_right_shift) - 1 )), current_right_shift));
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
      setImmSrc(signExt((inst & ( pow2(current_right_shift) - 1 )), current_right_shift));
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
      setImmSrc(signExt((inst & ( pow2(current_right_shift) - 1 )), current_right_shift));
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
      setImmSrc(signExt((inst & ( pow2(current_right_shift) - 1 )), current_right_shift));
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


  DEBUG_PRINT(" ");
  DEBUG_PRINT("inst: 0x" << hex << inst << dec);
  DEBUG_PRINT("opCode: " << instTable[m_op].opString << " 0x" << hex << m_op << dec);
  /*
  DEBUG_PRINT("pred: " << m_predicated);
  DEBUG_PRINT("pReg: " << m_predReg);
  DEBUG_PRINT("argClass: " << instTable[m_op].argClassString);
  DEBUG_PRINT("---------------")
  DEBUG_PRINT("Rdest: " << m_destReg);
  DEBUG_PRINT("Pdest: " << m_destPReg);
  DEBUG_PRINT("nRsrc: " << m_nRsrc);
  DEBUG_PRINT("nPsrc: " << m_nPsrc);
  DEBUG_PRINT("Rsrc 0 1 2: " << m_srcReg[0] << " " << m_srcReg[1] << " "  << m_srcReg[2]);
  DEBUG_PRINT("Psrc 0 1 2: " << m_srcPReg[0] << " " << m_srcPReg[1] << " "  << m_srcPReg[2]);
  DEBUG_PRINT("immSrc: 0x" << hex << m_srcImm << dec);
  */
}

void instruction_c::execute(warp_c &warp, unsigned int threadID) {
  //Check for Predicate
  if (m_predicated)
    if(!warp.m_predRF[threadID][m_predReg])
      return;


  Word memoryAddr;
  switch(m_op) {
    //Trivial
    case NOP: 
      break;

    //Privileged
    case DI:
    case EI:
    case SKEP:
    case TLBADD:
    case TLBRM:
    case TLBFLUSH:
    case JMPRU:
    case RETI:
      cout << "Unsupported instruction in this version " << instTable[m_op].opString << endl;
      break;

    case HALT:
      exec_finish = true;
      cout << "Received HALT" << endl;
      break;

    //Memory
    case ST:
      break;
    case LD:
      memoryAddr = warp.m_regRF[threadID][m_srcReg[0]] + m_srcImm;
      warp.m_regRF[threadID][m_destReg] = warp.m_bin->get_data(memoryAddr);
      DEBUG_PRINTF(("r[%u][%u](%lu) = LD[r[%u][%u](%lu) + Imm(%lu)](%lu)\n", \
                    threadID, m_destReg, warp.m_regRF[threadID][m_destReg], \
                    threadID, m_srcReg[0], warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm, memoryAddr));
      break;
    //Predicate Manipulation
    case ANDP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] & warp.m_predRF[threadID][m_srcPReg[1]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) = p[%u][%u](0x%x) & p[%u][%u](0x%x)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcPReg[0], warp.m_predRF[threadID][m_srcPReg[0]], \
                    threadID, m_srcPReg[1], warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case ORP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] | warp.m_predRF[threadID][m_srcPReg[1]]; 
      DEBUG_PRINTF(("p[%u][%u](0x%x) = p[%u][%u](0x%x) | p[%u][%u](0x%x)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcPReg[0], warp.m_predRF[threadID][m_srcPReg[0]], \
                    threadID, m_srcPReg[1], warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case XORP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] != warp.m_predRF[threadID][m_srcPReg[1]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) = p[%u][%u](0x%x) ^ p[%u][%u](0x%x)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcPReg[0], warp.m_predRF[threadID][m_srcPReg[0]], \
                    threadID, m_srcPReg[1], warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case NOTP:
      warp.m_predRF[threadID][m_destPReg] = !warp.m_predRF[threadID][m_srcPReg[0]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) = !p[%u][%u](0x%x)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcPReg[0], warp.m_predRF[threadID][m_srcPReg[0]]));
      break;

    //Value Tests
    case RTOP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) = !r[%u][%d](%lu)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcReg[0], warp.m_regRF[threadID][m_srcReg[0]]));
      break; 
    case ISNEG:
      warp.m_predRF[threadID][m_destPReg] = (1ll << (WORD_SIZE_IN_BITS-1)) & warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) ISNEG r[%u][%d](%ld)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcReg[0], (long)warp.m_regRF[threadID][m_srcReg[0]]));
      break;
    case ISZERO:
      warp.m_predRF[threadID][m_destPReg] = !warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("p[%u][%u](0x%x) ISZERO r[%u][%d](%lu)\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcReg[0], warp.m_regRF[threadID][m_srcReg[0]]));
      break;

    //Imm Arith/Logic
    case ADDI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] + m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("r[%u][%u](%lu) = r[%u][%u](%lu) + Imm(%lu)\n", \
                    threadID, m_destReg, warp.m_regRF[threadID][m_destReg], \
                    threadID, m_srcReg[0], warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case SUBI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] - m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case MULI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] * m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case DIVI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] / m_srcImm;
      break;
    case MODI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] % m_srcImm;
      break;
    case SHRI:
      warp.m_regRF[threadID][m_destReg] = Word_s(warp.m_regRF[threadID][m_srcReg[0]]) >> m_srcImm;
      break;
    case SHLI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] << m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case ANDI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] & m_srcImm;
      break;
    case ORI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] | m_srcImm;
      break; 
    case XORI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] ^ m_srcImm;
      break;
    case LDI:
      warp.m_regRF[threadID][m_destReg] = m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("r[%u][%u](%lu) = Imm(%lu)\n", \
                    threadID, m_destReg, warp.m_regRF[threadID][m_destReg], \
                    m_srcImm));
      break;

    //Reg Arith/Logic
    case ADD:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] + warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case SUB:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] - warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case MUL:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] * warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case DIV:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] / warp.m_regRF[threadID][m_srcReg[1]];
      break;
    case SHL:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] << warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case SHR:
      warp.m_regRF[threadID][m_destReg] = Word_s(warp.m_regRF[threadID][m_srcReg[0]]) >> warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case MOD:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] % warp.m_regRF[threadID][m_srcReg[1]];
      break;
    case AND:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] & warp.m_regRF[threadID][m_srcReg[1]];
      break;
    case OR:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] | warp.m_regRF[threadID][m_srcReg[1]];
      break;
    case XOR:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] ^ warp.m_regRF[threadID][m_srcReg[1]];
      break;
    case NEG:
      warp.m_regRF[threadID][m_destReg] = -(Word_s)warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;
    case NOT:
      warp.m_regRF[threadID][m_destReg] = ~(Word_s)warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      break;

    //Floating Point
    case ITOF:
    case FTOI:
    case FNEG:
    case FADD:
    case FSUB:
    case FMUL: 
    case FDIV:
      cout << "Unsupported instruction in this version " << instTable[m_op].opString << endl;
      break;

    //Contorl Flow
    case JMPI:
    case JMPR:
    case JALI:
    case JALR:
      
      break;

    //SIMD Control
    case CLONE:
    case JALIS:
    case JALRS:
    case JMPRT:
    case SPLIT:
    case JOIN:
      cout << "Unsupported instruction in this version " << instTable[m_op].opString << endl;
      break;

    //Warp Control
    case WSPAWN:
    case BAR:
      cout << "Unsupported instruction in this version " << instTable[m_op].opString << endl;
      break;
    
    //User/Ker Interaction
    case TRAP:
      cout << "Unsupported instruction in this version " << instTable[m_op].opString << endl;
      break;
    
    default:
      cerr << "Unsupported instruction opcode: 0x" << hex << m_op << dec << endl;
      exit(1);
  }

  //Update PC
}