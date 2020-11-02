
#include <ultra64.h>

#include "heap.hpp"
#include "math.hpp"

// -------------------------------------------------------------------------- //

bool TSine::startup(
  u32 bits, THeap * heap
) {
  if (bits == 0 || bits > 16) {
    return false;
  }

  if (sSinTable != nullptr) {
    return false;
  }

  u32 count = (1 << bits);
  sSinTable = new(heap) float[count];
  sSinShift = (16 - bits);

  constexpr auto kTwoPi = static_cast<float>(M_PI * 2.0);
  auto const factor = (kTwoPi / static_cast<float>(count));

  for (u32 i = 0; i < count; ++i) {
    sSinTable[i] = sinf(static_cast<float>(i) * factor);
  }

  return true;
}

// -------------------------------------------------------------------------- //

void TSine::shutdown() {
  if (sSinTable == nullptr) {
    return;
  }

  delete[] sSinTable;
  sSinTable = nullptr;
  sSinShift = 0;
}

// -------------------------------------------------------------------------- //

float TSine::ssin(s16 x) {
  return sSinTable[static_cast<u16>(x) >> sSinShift];
}

// -------------------------------------------------------------------------- //

float TSine::scos(s16 x) {
  return sSinTable[static_cast<u16>(x + 16384) >> sSinShift];
}

// -------------------------------------------------------------------------- //
