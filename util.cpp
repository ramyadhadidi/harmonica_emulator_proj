#include "util.h"

//////////////////////////////////////////////////////////////////////////
// Binary Reader
//////////////////////////////////////////////////////////////////////////

binReader_c::binReader_c(string  fileName) : 
   m_fileName(fileName) {
    m_bin.open(m_fileName.c_str(), ios::in|ios::binary);

    read_all();
  }

void binReader_c::read_all() {
  streampos size;
  char * memblock;

  if (m_bin.is_open()) {
    memblock = new char [size];
    m_bin.seekg (0, ios::end);
    size = m_bin.tellg();
    m_bin.seekg (0, ios::beg);
    memblock = new char [size];
    m_bin.read (memblock, size);
    m_bin.close();

    for (int i=0; i<size; i++)
      if (memblock[i]!=' ' && memblock[i]!='\n')
        binary_stream.push(memblock[i]);
  }
  else {
    cerr << "Unable to open binary File\n";
    exit(1);
  }
}

Word binReader_c::get_inst() {
  string inst = "";
  for (int i=0; i < INST_SIZE_BITS/4; i++) {
    if (!binary_stream.empty()) { 
      inst = inst +  binary_stream.front();
      binary_stream.pop();
    }
    else {
      cerr << "Reach to end of the File\n";
      exit(1);
    }
  }

  stringstream ss;
  ss << hex << inst;
  Word inst_int;
  ss >> inst_int;
  return inst_int;
}

//////////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////////

