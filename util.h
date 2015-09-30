#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

#include "globals.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Binary Reader
//////////////////////////////////////////////////////////////////////////

class binReader_c {
  public:
    binReader_c(string fileName);
    Word get_inst(Addr PC);
    Byte get_byte(Addr addr);

  private:
    void read_all();

  private:
    string m_fileName;
    ifstream m_bin;
    vector<Byte> binary_stream;
};

#endif