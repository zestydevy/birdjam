
#include <nusys.h>

#include "staticobj.hpp"
#include "rank.hpp"

// -------------------------------------------------------------------------- //

TRank gRank;

// -------------------------------------------------------------------------- //

void TRank::reset() {
  for (u32 i = 0; i < NUM_TALLY; ++i) {
    mTally[i] = 0;
  }

  // test
  mTally[TALLY_BALLOONS] = 13;
  mTally[TALLY_CATS] = 9;
  mTally[TALLY_CITIZENS] = 3;
}

// -------------------------------------------------------------------------- //

bool TRank::record(
  EObjType type, u32 count
) {
  u32 tally;

  if (!objectToTally(type, &tally)) {
    return false;
  }

  u8 value = mTally[tally];

  if (count > MAX_TALLY - value) {
    return false;
  }

  mTally[tally] = (u8)(value + count);
  return true;
}

// -------------------------------------------------------------------------- //

bool TRank::set(
  u32 tally, u8 value
) {
  if (tally >= NUM_TALLY || value > MAX_TALLY) {
    return false;
  }

  mTally[tally] = value;
  return true;
}

// -------------------------------------------------------------------------- //

u8 TRank::get(u32 tally) const {
  if (tally >= NUM_TALLY) {
    return 0;
  }

  return mTally[tally];
}

// -------------------------------------------------------------------------- //

u32 TRank::calcRank(u32 score) {
  if (score >= 57500)
    return RANK_A;
  else if (score >= 40000)
    return RANK_B;
  else if (score >= 20000)
    return RANK_C;
  else if (score >= 10000)
    return RANK_D;
  else
    return RANK_F;
}

// -------------------------------------------------------------------------- //

bool TRank::objectToTally(
  EObjType type, u32 * tally
) {
  u32 value;

  switch (type) {
    case EObjType::BALLOON:
    case EObjType::BALLOON_DEFLATED: {
      value = TALLY_BALLOONS;
      break;
    }
    case EObjType::BEER:
    case EObjType::MELON:
    case EObjType::APPLE: {
      value = TALLY_FOOD;
      break;
    }
    case EObjType::CARD: {
      value = TALLY_CARDS;
      break;
    }
    case EObjType::STICK: {
      value = TALLY_STICKS;
      break;
    }
    case EObjType::TABLE:
    case EObjType::LUNCHTABLE: {
      value = TALLY_TABLES;
      break;
    }
    case EObjType::CHAIR: {
      value = TALLY_CHAIRS;
      break;
    }
    case EObjType::NOODLE: {
      value = TALLY_NOODLES;
      break;
    }
    case EObjType::BILLS:
    case EObjType::NECKLACE:
    case EObjType::RING: {
      value = TALLY_JEWELRY;
      break;
    }
    case EObjType::POT: {
      value = TALLY_POTS;
      break;
    }
    case EObjType::TOASTER: {
      value = TALLY_TOASTERS;
      break;
    }
    case EObjType::STEPPINGSTONE: {
      value = TALLY_STONES;
      break;
    }
    case EObjType::TRASHCAN:
    case EObjType::TRASHCAN2: {
      value = TALLY_TRASH;
      break;
    }
    case EObjType::MAILBOX: {
      value = TALLY_MAILBOXES;
      break;
    }
    case EObjType::LAMP: {
      value = TALLY_LAMPS;
      break;
    }
    case EObjType::PLANK: {
      value = TALLY_BOARDS;
      break;
    }
    case EObjType::SOCCER: {
      value = TALLY_BALLS;
      break;
    }
    case EObjType::GOAL: {
      value = TALLY_GOALS;
      break;
    }
    case EObjType::TRUNK:
    case EObjType::LEAVES:
    case EObjType::BRANCH:
    case EObjType::BUSH: {
      value = TALLY_PLANTS;
      break;
    }
    case EObjType::BEEHIVE: {
      value = TALLY_BEEHIVES;
      break;
    }
    case EObjType::CHICKEN: {
      value = TALLY_CHICKENS;
      break;
    }
    case EObjType::CAT: {
      value = TALLY_CATS;
      break;
    }
    case EObjType::FENCE: {
      value = TALLY_FENCES;
      break;
    }
    case EObjType::TIRE: {
      value = TALLY_TIRES;
      break;
    }
    case EObjType::CAR: {
      value = TALLY_VEHICLES;
      break;
    }
    case EObjType::LOGO:
    case EObjType::STORE_E:
    case EObjType::STORE_B: {
      value = TALLY_STORE_LOGOS;
      break;
    }
    case EObjType::CRITIC:
    case EObjType::AVGN:
    case EObjType::WOMAN:
    case EObjType::CHILD: {
      value = TALLY_CITIZENS;
      break;
    }
    default: {
      return false;
    }
  }

  if (tally != nullptr) {
    *tally = value;
  }

  return true;
}

// -------------------------------------------------------------------------- //
