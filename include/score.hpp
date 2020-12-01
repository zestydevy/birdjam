
#ifndef INCLUDE_SCORE_HPP
#define INCLUDE_SCORE_HPP

#include <nusys.h>

#include "collider.hpp"
#include "dynlist.hpp"
#include "math.hpp"
#include "player.hpp"
#include "staticobj.hpp"

// -------------------------------------------------------------------------- //

class TFlockObj :
  public TObject
{

  public:

  TFlockObj(TDynList2 * dl);
  virtual ~TFlockObj() override;

  void incFlock(u32 n, float strength);
  float getStrength() const { return mStrength; }

  static TFlockObj * getFlockObj();

  protected:

  u32 mFlockSize { 0 };
  float mStrength { 1.0F };

  private:

  static TFlockObj * sFlockObj;

};

// -------------------------------------------------------------------------- //

class TNestObj :
  public TObject,
  public TSphereCollider
{

  public:

  TNestObj(TDynList2 *, EObjType);
  virtual ~TNestObj() = default;

  float getObjWeight() const { return mObjWeight; }

  virtual void updateMtx() override;

  virtual void init() override;
  virtual void update() override;

  protected:

  enum class EState {

    IDLE,
    CARRYING,
    DROPPING,
    NESTING,

  };

  float mObjWeight { 0.0F };
  float mObjRadius { 0.0F };
  TPlayer * mPlayer { nullptr };
  EObjType mObjType { EObjType::INVALID };
  EState mState { EState::IDLE };

  const TObjectData * mData{nullptr};

  virtual void onCollide(TCollider *) override;

};

// -------------------------------------------------------------------------- //

#define SEC_PER_MIN  60
#define MS_PER_SEC   1000

class TTimer {

  public:

  TTimer() = default;

  void start(u32 seconds);
  bool update(); // returns true if 0:00:00

  // returns float seconds
  float get(
    u32 * min = nullptr,
    u32 * sec = nullptr,
    u32 * ms = nullptr
  ) const;

  static TTimer * getInstance() {
    return &sInstance;
  }

  private:

  static TTimer sInstance;

  float mTime { 0.0F };

};

// -------------------------------------------------------------------------- //

#endif
