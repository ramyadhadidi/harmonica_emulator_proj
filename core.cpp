#include "core.h"

core_c::core_c() 
  : m_binary_filename("")
{

}

core_c::core_c(string filename) {
  m_binary_filename = filename;
  m_bin.set_filename(filename);

  SM = new warp_c[SIMD_LANE_NUM];
  for(int i=0; i<SIMD_LANE_NUM; i++) {
    SM[i] = warp_c(&m_bin);
  }

  while(1)
    SM[0].step();
}