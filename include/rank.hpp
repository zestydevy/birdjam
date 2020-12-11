
#ifndef INCLUDE_RANK_HPP
#define INCLUDE_RANK_HPP

#include <nusys.h>

#include "staticobj.hpp"

// -------------------------------------------------------------------------- //

enum : u32 {

  TALLY_BALLOONS,
  TALLY_FOOD,
  TALLY_CARDS,
  TALLY_STICKS,
  TALLY_TABLES,
  TALLY_CHAIRS,
  TALLY_NOODLES,
  TALLY_JEWELRY,
  TALLY_POTS,
  TALLY_TOASTERS,
  TALLY_STONES,
  TALLY_TRASH,
  TALLY_MAILBOXES,
  TALLY_LAMPS,
  TALLY_BOARDS,
  TALLY_BALLS,
  TALLY_GOALS,
  TALLY_PLANTS,
  TALLY_BEEHIVES,
  TALLY_CHICKENS,
  TALLY_CATS,
  TALLY_FENCES,
  TALLY_TIRES,
  TALLY_VEHICLES,
  TALLY_STORE_LOGOS,
  TALLY_CITIZENS,

  NUM_TALLY,
  MAX_TALLY = 99

};

// -------------------------------------------------------------------------- //

enum : u32 {

  RANK_A,
  RANK_B,
  RANK_C,
  RANK_D,
  RANK_F,

  NUM_RANKS

};

// -------------------------------------------------------------------------- //

class TRank {

  public:

  TRank() = default;
  ~TRank() = default;

  void reset();
  bool record(EObjType type, u32 count = 1);

  bool set(u32 tally, u8 value);
  u8 get(u32 tally) const;

  static u32 calcRank(u32 score);

  private:

  u8 mTally[NUM_TALLY];

  static bool objectToTally(EObjType, u32 *);

};

// -------------------------------------------------------------------------- //

extern TRank gRank;

// -------------------------------------------------------------------------- //

#endif
