#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "globals.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Binary Reader
//////////////////////////////////////////////////////////////////////////

class binReader_c {
  public:
    binReader_c();
    binReader_c(string fileName);
    void set_filename(string fileName);
    Word get_inst(Addr PC);
    Word get_data(Addr dataAddr);
    void write_data(Addr dataAddr, Word data);
    Byte get_byte(Addr addr);

  private:
    void read_all();

  private:
    string m_fileName;
    ifstream m_bin;
    vector<Byte> binary_stream;
};

#endif