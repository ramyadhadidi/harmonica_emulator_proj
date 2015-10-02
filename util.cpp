#include "util.h"

binReader_c::binReader_c() : 
   m_fileName("") {}

binReader_c::binReader_c(string fileName) : 
   m_fileName(fileName) {
    m_bin.open(m_fileName.c_str(), ios::in|ios::binary);

    read_all();
  }

void binReader_c::set_filename(string fileName) {
  m_fileName = fileName;
  m_bin.open(m_fileName.c_str(), ios::in|ios::binary);

  read_all();
}

void binReader_c::read_all() {
  streampos size;
  char * memblock;

  if (m_bin.is_open()) {
    m_bin.seekg (0, ios::end);
    size = m_bin.tellg();
    memblock = new char [size];
    m_bin.seekg (0, ios::beg);
    m_bin.read (memblock, size);
    m_bin.close();

    for (int i=0; i<size; i++)
      binary_stream.push_back((Byte)memblock[i]);
  }
  else {
    cerr << "Unable to open binary File" << endl;
    exit(1);
  }
}

Word binReader_c::get_inst(Addr PC) {
  if (PC+WORD_SIZE_IN_BYTE-1 > binary_stream.size()) {
    cerr << "PC out of memory" << endl;
    exit(1);
  }

  Word output = 0;
  for (int i=0; i<WORD_SIZE_IN_BYTE; i++)
    output += binary_stream[PC+i] * pow(256, i);

  return output;
}

Word binReader_c::get_data(Addr dataAddr) {
  if (dataAddr+WORD_SIZE_IN_BYTE-1 > binary_stream.size()) {
    exit(1);
  }

  Word output = 0;
  for (int i=0; i<WORD_SIZE_IN_BYTE; i++) {
    output += binary_stream[dataAddr+i] * pow(256, i);
  }

  DEBUG_PRINT("Read Data[" << hex << dataAddr << "] = " << hex << output << dec);
  return output;
}

Byte binReader_c::get_byte(Addr addr) {
  if (addr > binary_stream.size()) {
    cerr << "Addressing out of memory" << endl;
    exit(1);
  }

  return binary_stream[addr];
}

void binReader_c::write_data(Addr dataAddr, Word data) {
  Word original_data = data;
  if (dataAddr+WORD_SIZE_IN_BYTE-1 > binary_stream.size()) {
    cerr << "dataAddr out of memory (Write Data)" << endl;
    exit(1);
  }

  for (int i=0; i<WORD_SIZE_IN_BYTE; i++) {
    Word partial_data = data & (pow2(8)-1);
    binary_stream[dataAddr + i] = (Byte)partial_data;
    data = data >> 8;
  }

  DEBUG_PRINT("Write Data[" << hex << dataAddr << "] = " << hex << original_data << dec);
}

