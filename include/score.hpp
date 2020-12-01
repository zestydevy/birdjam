
#ifndef INCLUDE_SCORE_HPP
#define INCLUDE_SCORE_HPP

#include <nusys.h>

#include "collider.hpp"
#include "dynlist.hpp"
#include "math.hpp"
#include "player.hpp"
#include "staticobj.hpp"

class TNestObj;

// -------------------------------------------------------------------------- //

class TFlockObj :
  public TObject
{

  public:

  TFlockObj(TDynList2 * dl);
  virtual ~TFlockObj() override;

  void incFlock(u32 n, float strength);
  float getStrength() const { return mStrength; }

  bool grabObject(TNestObj * obj);
  bool dropAllObjects();

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  static TFlockObj * getFlockObj();

  protected:

  u32 mFlockSize { 0 };
  float mStrength { 1.0F };

  private:

  int mHeldNum { 0 };
  TNestObj * mHeldObjects[32];

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

  void drop();
  TVec3F getMountPoint();

  virtual void updateMtx() override;

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

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
  TObject * mDebugCube { nullptr };

  TMtx44 mIRotMtx{};

  s16 mMountTimer {0};
  s16 mMountRotY {0};
  float mMountDist {0.0f};


  TVec3S mMountRot;
  TMtx44 mMountRotMtx{};
  Mtx mFMountRotMtx{};

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
