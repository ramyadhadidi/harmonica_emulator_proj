#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include "globals.h"
#include "warp.h"

using namespace std;

class core_c {

  public:
    core_c();
    core_c(string filename);

  private:
    string m_binary_filename;
    binReader_c m_bin;

    warp_c* SM;

};

#endif