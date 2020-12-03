
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
  float getSize() const { return mCarrySize; }

  bool grabObject(TNestObj * obj);
  bool dropTopObject();
  bool dropAllObjects();

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  static TFlockObj * getFlockObj();

  protected:

  u32 mFlockSize { 0 };
  float mStrength { 0.25F };
  float mCarrySize { 0.0F };

  private:

  int mHeldNum { 0 };
  TNestObj * mHeldObjects[32];

  static TFlockObj * sFlockObj;

};

// -------------------------------------------------------------------------- //

class TNestObj :
  public TObject
{

  public:

  TNestObj(TDynList2 *, EObjType);
  virtual ~TNestObj() = default;

  float getObjWeight() const { return mObjWeight; }
  float getObjScale() const { return (mScale.x() + mScale.y() + mScale.z()) / 3.0f; }

  void drop(TVec3F v);
  TVec3F getMountPoint();

  virtual void updateMtx() override;

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  void startNesting();

  protected:
  virtual void setCollision(bool set);
  virtual void updateCollider();
  virtual float getHalfHeight();

  enum class EState {

    IDLE,
    CARRYING,
    DROPPING,
    STASHING,
    NESTING,

  };

  float mObjWeight { 0.0F };
  TPlayer * mPlayer { nullptr };
  EObjType mObjType { EObjType::INVALID };
  EState mState { EState::IDLE };

  s16 mMountTimer {0};
  s16 mMountRotY {0};
  float mMountDist {0.0f};

  TVec3F mVelocity;
  TVec3F mRotVel;

  TVec3S mMountRot;
  Mtx mFMountRotMtx{};

  const TObjectData * mData{nullptr};

  bool onPickup(TCollider *);
};

// -------------------------------------------------------------------------- //

class TNest;
class TNestArea :
  public TCylinderCollider
{
  public:

  TNestArea(TDynList2 *, TNest * nest);
  virtual ~TNestArea() = default;

  void updateSize(float size);

  protected:
  TNest * mNest;
  
  virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //

class TNest :
  public TObject,
  public TCylinderCollider
{
  public:

  TNest(TDynList2 *);
  virtual ~TNest();

  float getSize() const { return mSize; }
  static TNest * getNestObject();

  static float getTopY();
  static TVec3F getRandomPointInside();

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  void areaCollide(TCollider *);


  void assimilateObject(TNestObj * obj);

  protected:
  float mSize { 0.0F };
  TNestArea * mNestArea;

  static TNest * sNest;

  virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //

class TNestObjSphere :
  public TNestObj,
  public TSphereCollider
{

  public:

  TNestObjSphere(TDynList2 *, EObjType);
  virtual ~TNestObjSphere() = default;

  virtual void init() override;

  protected:
  virtual void setCollision(bool set) override;
  virtual void updateCollider() override;
  virtual float getHalfHeight() override;

  float mObjRadius { 0.0F };

  virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //

class TNestObjBox :
  public TNestObj,
  public TBoxCollider
{

  public:

  TNestObjBox(TDynList2 *, EObjType);
  virtual ~TNestObjBox() = default;

  virtual void init() override;

  protected:
  virtual void setCollision(bool set) override;
  virtual void updateCollider() override;
  virtual float getHalfHeight() override;

  TVec3F mSize;

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
