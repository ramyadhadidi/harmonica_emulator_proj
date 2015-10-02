#include "core.h"

core_c::core_c() 
  : m_binary_filename("")
{

}

core_c::core_c(string filename) {
  m_binary_filename = filename;
  m_bin.set_filename(filename);

  SM = new warp_c[SIMD_LANE_NUM];
  for(unsigned int warpId=0; warpId<SIMD_LANE_NUM; warpId++) {
    SM[warpId] = warp_c(&m_bin, warpId);
  }
}

void core_c::step() {
    for(unsigned int i=0; i<SIMD_LANE_NUM; i++)
      SM[i].step();
}