
#ifndef INCLUDE_COLLIDER_HPP
#define INCLUDE_COLLIDER_HPP

#include <nusys.h>

#include "heap.hpp"
#include "linklist.hpp"
#include "math.hpp"

// -------------------------------------------------------------------------- //

enum class ECollideType {

  BOX,
  SPHERE,
  CYLINDER

};

// -------------------------------------------------------------------------- //

class TCollider {

  public:

  TCollider();
  virtual ~TCollider();

  void initCollider(
    u32 tag, u32 send, u32 receive,
    u32 max_hit, THeap * = nullptr
  );

  virtual ECollideType getCollideType() const = 0;
  u32 getCollideTag() const { return mTag; }

  TVec3F const & getCollideCenter() const { return mCenter; }
  void setCollideCenter(TVec3F const & pt) { mCenter = pt; }

  virtual float getCollideMinX() const = 0;
  virtual float getCollideMinY() const = 0;
  virtual float getCollideMinZ() const = 0;
  virtual float getCollideMaxX() const = 0;
  virtual float getCollideMaxY() const = 0;
  virtual float getCollideMaxZ() const = 0;
  void calcCollideMinMax(TVec3F *, TVec3F *) const;

  static void frameBegin(); // resets collider state
  static void frameEnd(); // tests colliders, calls onCollide

  protected:

  TVec3F mCenter { 0.0F, 0.0F, 0.0F };

  virtual void onCollide(TCollider *) = 0;
  virtual bool onCheckCollide(TCollider const *) const = 0;

  private:

  static TDoubleLinkList<TCollider> sColliderList;
  TDoubleLinkListNode<TCollider> mListNode { this };
  TCollider ** mHitArray { nullptr };
  u32 mMaxHitNum { 0 };
  u32 mHitNum { 0 };
  u32 mSendMask { 0 };
  u32 mReceiveMask { 0 };
  u32 mTag { 0 };

  bool pushCollision(TCollider *);

};

// -------------------------------------------------------------------------- //

class TBoxCollider :
  public TCollider
{

  public:

  TBoxCollider() = default;
  virtual ~TBoxCollider() = default;

  virtual ECollideType getCollideType() const override;

  TVec3F const & getCollideSize() const { return mSize; }
  void setCollideSize(TVec3F const & sz) { mSize = sz; }

  virtual float getCollideMinX() const override;
  virtual float getCollideMinY() const override;
  virtual float getCollideMinZ() const override;
  virtual float getCollideMaxX() const override;
  virtual float getCollideMaxY() const override;
  virtual float getCollideMaxZ() const override;

  protected:

  virtual bool onCheckCollide(TCollider const *) const override;

  private:

  TVec3F mSize { 0.0F, 0.0F, 0.0F };

};

// -------------------------------------------------------------------------- //

class TSphereCollider :
  public TCollider
{

  public:

  TSphereCollider() = default;
  virtual ~TSphereCollider() = default;

  virtual ECollideType getCollideType() const override;

  float getCollideRadius() const { return mRadius; }
  void setCollideRadius(float r) { mRadius = r; }

  virtual float getCollideMinX() const override;
  virtual float getCollideMinY() const override;
  virtual float getCollideMinZ() const override;
  virtual float getCollideMaxX() const override;
  virtual float getCollideMaxY() const override;
  virtual float getCollideMaxZ() const override;

  protected:

  virtual bool onCheckCollide(TCollider const *) const override;

  private:

  float mRadius { 0.0F };

};

// -------------------------------------------------------------------------- //

class TCylinderCollider :
  public TCollider
{

  public:

  TCylinderCollider() = default;
  virtual ~TCylinderCollider() = default;

  virtual ECollideType getCollideType() const override;

  float getCollideHeight() const { return mHeight; }
  void setCollideHeight(float ht) { mHeight = ht; }

  float getCollideRadius() const { return mRadius; }
  void setCollideRadius(float r) { mRadius = r; }

  virtual float getCollideMinX() const override;
  virtual float getCollideMinY() const override;
  virtual float getCollideMinZ() const override;
  virtual float getCollideMaxX() const override;
  virtual float getCollideMaxY() const override;
  virtual float getCollideMaxZ() const override;

  protected:

  virtual bool onCheckCollide(TCollider const *) const override;

  private:

  float mHeight { 0.0F };
  float mRadius { 0.0F };

};

// -------------------------------------------------------------------------- //

struct TCollideUtil {

  template<typename T>
  static inline T squared(T x) { return (x * x); }

  static float calcSqrDist(TVec3F const & from, TVec3F const & to);
  static bool doRangesOverlap(float a0, float b0, float a1, float b1);

  static bool testTwoBoxes(
    TVec3F const & min_a, TVec3F const & max_a,
    TVec3F const & min_b, TVec3F const & max_b
  );

  static bool testBoxSphere2D(
    TVec2F const & min, TVec2F const & max,
    TVec2F const & center, float radius
  );

  static bool testBoxSphere3D(
    TVec3F const & min, TVec3F const & max,
    TVec3F const & center, float radius
  );

  static float distPtLine(
    TVec3F const & pt,
    TVec3F const & p0,
    TVec3F const & p1
  );

  static float distPtPoly(
    TVec3F const & pt,
    TVec3F const & v0,
    TVec3F const & v1,
    TVec3F const & v2
  );

  static bool testColliders(
    TBoxCollider const *,
    TBoxCollider const *
  );

  static bool testColliders(
    TSphereCollider const *,
    TSphereCollider const *
  );

  static bool testColliders(
    TCylinderCollider const *,
    TCylinderCollider const *
  );

  static bool testColliders(
    TBoxCollider const *,
    TSphereCollider const *
  );

  static bool testColliders(
    TBoxCollider const *,
    TCylinderCollider const *
  );

  static bool testColliders(
    TSphereCollider const *,
    TCylinderCollider const *
  );

};

// -------------------------------------------------------------------------- //

#endif
