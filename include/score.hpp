
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
  float getCapacity() const { return mCarrySize / 4.0f / mStrength; }
  float maxCarryWeight() const { return mStrength - (mCarrySize / 4.0f); }
  int getPowerLevel();
  float getChainLength();
  void setActive(bool active);

  int getNumObjects() const { return mHeldNum; }
  float getRadius(float min = 0.0f);
  float getObjRadius(int idx);

  bool grabObject(TNestObj * obj);
  bool dropTopObject();
  bool dropAllObjects();
  bool cacheAllObjects();

  bool canGrabObject(float size);

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  static TFlockObj * getFlockObj();
  static bool canDrawHighlightRing(float size);
  static void startHighlightTimer();

  protected:

  int getPowerLevel(float weight);

  u32 mFlockSize { 0 };
  float mStrength { 0.25F };
  float mCarrySize { 0.0F };

  float mPrevLevel{0.0f};

  float mHighlightTimer{0.0f};
  bool mDoHighlight{false};

  private:

  int mHeldNum { 0 };
  TNestObj * mHeldObjects[32];
  bool mEnabled{true};

  static TFlockObj * sFlockObj;

};

// -------------------------------------------------------------------------- //

class TNestObj :
  public TObject
{

  public:

  TNestObj(TDynList2 *, EObjType);
  virtual ~TNestObj() = default;

  EObjType getObjType() const { return mObjType; }
  float getObjWeight() const { return mObjWeight; }
  float getObjScale() const { return (mScale.x() + mScale.y() + mScale.z()) / 3.0f; }

  void drop(TVec3F v);
  TVec3F getMountPoint();

  virtual void updateMtx() override;

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void drawRing();

  virtual void increaseRadius(float threshold) override;

  void startNesting();

  virtual float getHalfHeight();
  virtual float getHalfWidth();
  virtual float getScore();

  const TVec3F & getVelocity() { return mVelocity; } 
  void setVelocity(const TVec3F & vel) { mVelocity = vel; } 

  protected:
  virtual void setCollision(bool set);
  virtual void updateCollider();

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

  TVec3F mVelocity{0.0f, 0.0f, 0.0f};
  TVec3F mRotVel{0.0f, 0.0f, 0.0f}; // doubles as mount point cache to save space and improve framerate when carrying stuff

  TVec3S mMountRot{0, 0, 0};
  Mtx mFMountRotMtx{};

  const TObjectData * mData{nullptr};

  bool onPickup(TCollider *);
};

// -------------------------------------------------------------------------- //

class TNest;
class TNestArea :
  public TObject,
  public TCylinderCollider
{
  public:

  TNestArea(TDynList2 *, TNest * nest);
  virtual ~TNestArea() = default;

  void updateSize(float size);

  virtual void draw() override;

  protected:
  TNest * mNest{nullptr};
  
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
  float getCount() const { return mCount; }
  static TNest * getNestObject();

  static float getTopY();
  static TVec3F getRandomPointInside();

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;

  void areaCollide(TCollider *);

  void assimilateObject(TNestObj * obj);      //Object lands in nest
  void startAssimilateObject(TNestObj * obj); //Object thrown into nest

  protected:
  float mSize { 0.0F };
  int mCount {0};
  TNestArea * mNestArea{nullptr};

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

  virtual float getHalfHeight() override;
  virtual float getHalfWidth() override;
  virtual float getScore() override;

  virtual void increaseRadius(float threshold) override;

  protected:
  virtual void setCollision(bool set) override;
  virtual void updateCollider() override;

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

  virtual float getHalfHeight() override;
  virtual float getHalfWidth() override;
  virtual float getScore() override;

  virtual void increaseRadius(float threshold) override;

  protected:
  virtual void setCollision(bool set) override;
  virtual void updateCollider() override;

  TVec3F mSize{0.0f, 0.0f, 0.0f};

  virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //

#endif
