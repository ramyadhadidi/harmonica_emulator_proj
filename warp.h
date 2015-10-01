#ifndef WARP_H
#define WARP_H

#include <iostream>
#include "globals.h"
#include "util.h"

using namespace std;

class warp_c {
  friend class instruction_c;

  public:
    warp_c();
    warp_c(const warp_c &warp, binReader_c* bin=NULL);
    warp_c& operator=(const warp_c& warp);
    warp_c(binReader_c* bin);

    void step();

  private:
    binReader_c *m_bin;

    Addr m_pc[WARP_SIZE];
    Addr m_next_pc[WARP_SIZE];

    Word m_reg[WARP_SIZE][GPR_REG_NUM];
    bool m_pred[WARP_SIZE][PRED_REG_NUM];
};

#endif