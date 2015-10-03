/**
 * @class instruction_c
 * @brief Instruction class that create, extract information and executes instructions
 * @file instruction.cpp instruction.h
 * @author Ramyad Hadidi
 * @data 2015-10
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include "globals.h"
#include "warp.h"

using namespace std;

class instruction_c {
  friend class warp_c;

  public:
    /**
     * @brief opcodes enum, sorted so each opcode represented in enum
     */
    enum Opcode { 
      NOP,          DI,           EI, 
      TLBADD,       TLBFLUSH,     NEG, 
      NOT,          AND,          OR, 
      XOR,          ADD,          SUB, 
      MUL,          DIV,          MOD, 
      SHL,          SHR,          ANDI, 
      ORI,          XORI,         ADDI, 
      SUBI,         MULI,         DIVI, 
      MODI,         SHLI,         SHRI,
      JALI,         JALR,         JMPI, 
      JMPR,         CLONE,        JALIS, 
      JALRS,        JMPRT,        LD, 
      ST,           LDI,          RTOP, 
      ANDP,         ORP,          XORP, 
      NOTP,         ISNEG,        ISZERO, 
      HALT,         TRAP,         JMPRU, 
      SKEP,         RETI,         TLBRM,
      ITOF,         FTOI,         FADD, 
      FSUB,         FMUL,         FDIV, 
      FNEG,         WSPAWN,       SPLIT, 
      JOIN,         BAR 
    };

    /**
     *  @brief argument class type of instructions. It is used to extract instruction info
     */
    enum argClassType {
      AC_NONE, 
      AC_2REG, 
      AC_2IMM, 
      AC_3REG,
      AC_3PREG, 
      AC_3IMM, 
      AC_3REGSRC, 
      AC_1IMM, 
      AC_1REG, 
      AC_3IMMSRC, 
      AC_PREG_REG, 
      AC_2PREG, 
      AC_2REGSRC
    };

    /**
     *  @brief instType enum shows the type of operation each instruction does
     */
    enum instType {
        ITYPE_NULL, ITYPE_INTBASIC, ITYPE_INTMUL, ITYPE_INTDIV, ITYPE_STACK, ITYPE_BR, 
        ITYPE_CALL, ITYPE_RET, ITYPE_TRAP, ITYPE_FPBASIC, ITYPE_FPMUL, ITYPE_FPDIV
    };

    /**
     * @biref main refrence for extraction instruction information
     */
    static struct instTableEntry {
      const char *opString;
      bool controlFlow;
      bool relAddress;
      bool allSrcArgs;
      bool privileged;
      argClassType argClass;
      const char *argClassString;
      instType iType;
    } instTable[];

  public:
    /**
     * Create an insturction and extract its information and
     * sets private vaiables
     */
    instruction_c(Word inst);

    /**
     *  Executes the instruction and changes the states
     *  @param warp mother warp caller, this function will change that warp regsiter and pc values
     *  @param threadID 
     */
    void execute(warp_c &warp, unsigned int threadID);

  private:
    bool m_predicated;
    RegNum m_predReg;
    Opcode m_op;

    RegNum m_destReg;
    RegNum m_destPReg;

    int m_nRsrc;
    int m_nPsrc;
    RegNum m_srcReg[MAX_REG_SOURCES];
    RegNum m_srcPReg[MAX_PREG_SOURCES];

    bool m_immsrcPresent;
    Word m_srcImm;

  private:
    void setPredicated(bool predicated) { m_predicated = predicated; }
    void setPredReg(RegNum predReg) { m_predReg = predReg; }
    void setOpCode(Opcode op) { m_op = op; }
    void setDestReg(RegNum destReg) { m_destReg = destReg; }
    void setDestPReg(RegNum destPReg) { m_destPReg = destPReg; }
    void setSrcReg(RegNum srcReg) { m_srcReg[m_nRsrc++] = srcReg; }
    void setSrcPReg(RegNum srcPReg) { m_srcPReg[m_nPsrc++] = srcPReg; }
    void setImmSrc(Word srcImm) { m_immsrcPresent = true; m_srcImm = srcImm; }

    /**
     *  @biref Sign Extention
     *  @parm s input
     *  @param last_bit last bit of the s that is considered data (unsigend)
     */
    Word signExt(Word s, Word last_bit);
};

#endif