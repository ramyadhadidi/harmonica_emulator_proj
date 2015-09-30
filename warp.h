#ifndef WARP_H
#define WARP_H

#include <iostream>
#include <vector>
#include "globals.h"

using namespace std;

class warp_c {
  public:

  private:
    Word m_pc;
    Word m_next_pc;

    vector<vector<Word> > m_reg;
    vector<vector<bool> > m_pred;

};

#endif