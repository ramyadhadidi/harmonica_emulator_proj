/**
 * @class instruction_c
 * @brief Instruction class that create, extract information and executes instructions
 * @file instruction.cpp instruction.h
 * @author Ramyad Hadidi
 * @data 2015-10
 */


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

  /*
  DEBUG_PRINT(" ");
  DEBUG_PRINT("inst: 0x" << hex << inst << dec);
  DEBUG_PRINT("opCode: " << instTable[m_op].opString << " 0x" << hex << m_op << dec);
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
  //Debug Messages
  DEBUG_PRINTF(("\n"));
  DEBUG_PRINTF(("pc: 0x%"PRIx64" wpID:%u thID:%u\n", warp.m_pc[threadID], warp.m_warpId, threadID));

  if(m_predicated)
    DEBUG_PRINTF(("@p%u\n", m_predReg));

  DEBUG_PC_PRINT(warp.m_pc[threadID]);

  bool pc_changed = false;
  Word memoryAddr;

  //Check for Predicate
  if (m_predicated)
    if(!warp.m_predRF[threadID][m_predReg])
      goto noExecution;

  //Inst Execution
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
      memoryAddr = warp.m_regRF[threadID][m_srcReg[1]] + m_srcImm;  
      if (memoryAddr == ( (1LL << (INST_SIZE_BITS-1))) ) {
        if (warp.m_warpId == 0 && threadID == 0) {
          #ifdef OUTPUT_TO_FILE
            output_file << (char)warp.m_regRF[threadID][m_srcReg[0]];
          #else
            cout << (char)warp.m_regRF[threadID][m_srcReg[0]];
          #endif
        }
      }
      else 
        warp.m_bin->write_data(memoryAddr, warp.m_regRF[threadID][m_srcReg[0]]);
      DEBUG_PRINTF(("ST r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64" (Addr:0x%"PRIx64")\n", \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm, memoryAddr));
      break;
    case LD:
      memoryAddr = warp.m_regRF[threadID][m_srcReg[0]] + m_srcImm;
      warp.m_regRF[threadID][m_destReg] = warp.m_bin->get_data(memoryAddr);
      DEBUG_PRINTF(("LD r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") + 0x%"PRIx64" (Addr:0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm, memoryAddr));
      break;
    //Predicate Manipulation
    case ANDP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] & warp.m_predRF[threadID][m_srcPReg[1]];
      DEBUG_PRINTF(("ANDP p%u[%u](0x%x) p%u[%u](0x%x) p%u[%u](0x%x)\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcPReg[0], threadID, warp.m_predRF[threadID][m_srcPReg[0]], \
                    m_srcPReg[1], threadID, warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case ORP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] | warp.m_predRF[threadID][m_srcPReg[1]]; 
      DEBUG_PRINTF(("ORP p%u[%u](0x%x) p%u[%u](0x%x) p%u[%u](0x%x)\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcPReg[0], threadID, warp.m_predRF[threadID][m_srcPReg[0]], \
                    m_srcPReg[1], threadID, warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case XORP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_predRF[threadID][m_srcPReg[0]] != warp.m_predRF[threadID][m_srcPReg[1]];
      DEBUG_PRINTF(("XORP p%u[%u](0x%x) p%u[%u](0x%x) p%u[%u](0x%x)\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcPReg[0], threadID, warp.m_predRF[threadID][m_srcPReg[0]], \
                    m_srcPReg[1], threadID, warp.m_predRF[threadID][m_srcPReg[1]]));
      break;
    case NOTP:
      warp.m_predRF[threadID][m_destPReg] = !warp.m_predRF[threadID][m_srcPReg[0]];
      DEBUG_PRINTF(("NOTP p%u[%u](0x%x) p%u[%u](0x%x)\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcPReg[0], threadID, warp.m_predRF[threadID][m_srcPReg[0]]));
      break;

    //Value Tests
    case RTOP:
      warp.m_predRF[threadID][m_destPReg] = warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("RTOP p%u[%u](0x%x) r%u[%u](0x%"PRIx64")\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcReg[0], threadID,  warp.m_regRF[threadID][m_srcReg[0]]));
      break; 
    case ISNEG:
      warp.m_predRF[threadID][m_destPReg] = (1ll << (WORD_SIZE_IN_BITS-1)) & warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("ISNEG p%u[%u](0x%x) r%u[%u](0x%"PRIx64")\n", \
                    m_destPReg, threadID, warp.m_predRF[threadID][m_destPReg], \
                    m_srcReg[0], threadID, (long)warp.m_regRF[threadID][m_srcReg[0]]));
      break;
    case ISZERO:
      warp.m_predRF[threadID][m_destPReg] = !warp.m_regRF[threadID][m_srcReg[0]];
      DEBUG_PRINTF(("ISZERO p[%u][%u](0x%x) r[%u][%d](0x%"PRIx64")\n", \
                    threadID, m_destPReg, warp.m_predRF[threadID][m_destPReg], \
                    threadID, m_srcReg[0], warp.m_regRF[threadID][m_srcReg[0]]));
      break;

    //Imm Arith/Logic
    case ADDI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] + m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("ADDI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case SUBI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] - m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("SUBI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case MULI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] * m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("MULI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case DIVI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] / m_srcImm;
      DEBUG_PRINTF(("DIVI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case MODI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] % m_srcImm;
      DEBUG_PRINTF(("MODI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case SHRI:
      warp.m_regRF[threadID][m_destReg] = Word_s(warp.m_regRF[threadID][m_srcReg[0]]) >> m_srcImm;
      DEBUG_PRINTF(("SHRI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case SHLI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] << m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("SHLI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case ANDI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] & m_srcImm;
      DEBUG_PRINTF(("ANDI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case ORI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] | m_srcImm;
      DEBUG_PRINTF(("ORI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break; 
    case XORI:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] ^ m_srcImm;
      DEBUG_PRINTF(("XORI r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm));
      break;
    case LDI:
      warp.m_regRF[threadID][m_destReg] = m_srcImm;
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("LDI r%u[%u](0x%"PRIx64") 0x%"PRIx64"\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcImm));
      break;

    //Reg Arith/Logic
    case ADD:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] + warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("ADD r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case SUB:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] - warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("SUB r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case MUL:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] * warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("MUL r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case DIV:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] / warp.m_regRF[threadID][m_srcReg[1]];
      DEBUG_PRINTF(("DIV r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case SHL:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] << warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("SHL r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case SHR:
      warp.m_regRF[threadID][m_destReg] = Word_s(warp.m_regRF[threadID][m_srcReg[0]]) >> warp.m_regRF[threadID][m_srcReg[1]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("SHR r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case MOD:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] % warp.m_regRF[threadID][m_srcReg[1]];
      DEBUG_PRINTF(("MOD r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case AND:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] & warp.m_regRF[threadID][m_srcReg[1]];
      DEBUG_PRINTF(("AND r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case OR:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] | warp.m_regRF[threadID][m_srcReg[1]];
      DEBUG_PRINTF(("OR r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case XOR:
      warp.m_regRF[threadID][m_destReg] = warp.m_regRF[threadID][m_srcReg[0]] ^ warp.m_regRF[threadID][m_srcReg[1]];
      DEBUG_PRINTF(("XOR r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]]));
      break;
    case NEG:
      warp.m_regRF[threadID][m_destReg] = -(Word_s)warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("NEG r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]]));
      break;
    case NOT:
      warp.m_regRF[threadID][m_destReg] = ~(Word_s)warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] &= (pow2(WORD_SIZE_IN_BITS) - 1 );
      DEBUG_PRINTF(("NOT r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]]));
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
      warp.m_next_pc[threadID] = warp.m_pc[threadID] + STEP_PC + m_srcImm;
      pc_changed = true;
      DEBUG_PRINTF(("JMPI 0x%"PRIx64" (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_srcImm, warp.m_pc[threadID], warp.m_next_pc[threadID]));
      break;
    case JMPR:
      warp.m_next_pc[threadID] = warp.m_regRF[threadID][m_srcReg[0]];
      pc_changed = true;
      DEBUG_PRINTF(("JMPR r%u[%u](0x%"PRIx64") (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    warp.m_pc[threadID], warp.m_next_pc[threadID]));
      break;
    case JALI:
      warp.m_regRF[threadID][m_destReg] = warp.m_pc[threadID] + STEP_PC;
      warp.m_next_pc[threadID] = warp.m_pc[threadID] + STEP_PC + m_srcImm;
      pc_changed = true;
      DEBUG_PRINTF(("JALI r%u[%u](0x%"PRIx64") 0x%"PRIx64" (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcImm, warp.m_pc[threadID], warp.m_next_pc[threadID]));
      break;
    case JALR:
      warp.m_regRF[threadID][m_destReg] = warp.m_pc[threadID];
      warp.m_next_pc[threadID] = warp.m_regRF[threadID][m_srcReg[0]];
      pc_changed = true;
      DEBUG_PRINTF(("JALR r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    warp.m_pc[threadID], warp.m_next_pc[threadID]));
      break;

    //SIMD Control
    case CLONE:
      for (int i=0; i<GPR_REG_NUM; i++)
        warp.m_regRF[m_srcReg[0]][i] = warp.m_regRF[threadID][i];
      printf("CLONE %u\n", m_srcReg[0]);
      break;
    case JALIS:
      warp.m_nextActiveThreads = warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] = warp.m_pc[threadID] + STEP_PC;
      warp.m_next_pc[threadID] = warp.m_pc[threadID] + STEP_PC + m_srcImm;
      pc_changed = true;
      printf("JALIS r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") 0x%"PRIx64" (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcImm, warp.m_pc[threadID], warp.m_next_pc[threadID]);
      if(threadID != 0)
        cerr << "JALIS executed by thread %u" << threadID << "at pc: " << hex << warp.m_pc[threadID] << "\n";
      break;
    case JALRS:
      warp.m_nextActiveThreads = warp.m_regRF[threadID][m_srcReg[0]];
      warp.m_regRF[threadID][m_destReg] = warp.m_pc[threadID];
      warp.m_next_pc[threadID] = warp.m_regRF[threadID][m_srcReg[1]];
      pc_changed = true;
      printf("JALRS r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") r%u[%u](0x%"PRIx64") (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_destReg, threadID, warp.m_regRF[threadID][m_destReg], \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    m_srcReg[1], threadID, warp.m_regRF[threadID][m_srcReg[1]], \
                    warp.m_pc[threadID], warp.m_next_pc[threadID]);
      if(threadID != 0)
        cerr << "JALRS executed by thread %u" << threadID << "at pc: " << hex << warp.m_pc[threadID] << "\n";
      break;
    case JMPRT:
      warp.m_nextActiveThreads = 1;
      warp.m_next_pc[threadID] = warp.m_pc[threadID] + warp.m_regRF[threadID][m_srcReg[0]];
      pc_changed = true;
      printf("JMPRT r%u[%u](0x%"PRIx64") (pc=0x%"PRIx64" next_pc=0x%"PRIx64")\n", \
                    m_srcReg[0], threadID, warp.m_regRF[threadID][m_srcReg[0]], \
                    warp.m_pc[threadID], warp.m_next_pc[threadID]);
      if(threadID != 0)
        cerr << "JMPRT executed by thread %u" << threadID << "at pc: " << hex << warp.m_pc[threadID] << "\n";
      break;
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

  noExecution:

  //Update PC
  if (!pc_changed)
    warp.m_next_pc[threadID] = warp.m_pc[threadID] + STEP_PC;

  //Jump to Same PC (infinite loop :: JMPI -4)
  if (warp.m_pc[threadID] == warp.m_next_pc[threadID])
    exec_finish = true;

  warp.m_pc[threadID] = warp.m_next_pc[threadID];

  //Debug Register Stats
  DEBUG_PRINT("Register States:")
  for(int i=0; i<GPR_REG_NUM; i++)
    DEBUG_PRINTF(("\tr%u %"PRIx64"\n", i, warp.m_regRF[threadID][i]));
  DEBUG_PRINT("Predicate Register States:")
  DEBUG_PRINTF(("\t"));
  for(int i=0; i<PRED_REG_NUM; i++)
    DEBUG_PRINTF(("%x", warp.m_predRF[threadID][i]));
  DEBUG_PRINTF(("\n"));
  DEBUG_PRINTF(("# Active Threads: %"PRId64"\n", warp.m_activeThreads));
  if(warp.m_activeThreads != warp.m_nextActiveThreads)
    DEBUG_PRINTF(("# Next Active Threads: %"PRId64"\n", warp.m_nextActiveThreads));
}