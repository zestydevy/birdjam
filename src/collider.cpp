
#include "collider.hpp"
#include "heap.hpp"
#include "linklist.hpp"
#include "math.hpp"

// -------------------------------------------------------------------------- //

TDoubleLinkList<TCollider> TCollider::sColliderList;

// -------------------------------------------------------------------------- //

TCollider::TCollider() {
  sColliderList.link(sColliderList.end(), &mListNode);
}

// -------------------------------------------------------------------------- //

TCollider::~TCollider() {
  sColliderList.unlink(&mListNode);
  delete[] mHitArray;
}

// -------------------------------------------------------------------------- //

void TCollider::initCollider(
  u32 const tag,
  u32 const send,
  u32 const receive,
  u32 const max_hit,
  THeap * const heap
) {
  mTag = tag;
  mSendMask = send;
  mReceiveMask = receive;
  mMaxHitNum = max_hit;
  delete[] mHitArray;
  mHitArray = new(heap) TCollider * [mMaxHitNum];
  mHitNum = 0;
}

// -------------------------------------------------------------------------- //

void TCollider::calcCollideMinMax(
  TVec3F * const min,
  TVec3F * const max
) const {
  if (min != nullptr) {
    min->set(
      getCollideMinX(),
      getCollideMinY(),
      getCollideMinZ()
    );
  }

  if (max != nullptr) {
    max->set(
      getCollideMaxX(),
      getCollideMaxY(),
      getCollideMaxZ()
    );
  }
}

// -------------------------------------------------------------------------- //

void TCollider::init() {
  sColliderList = TDoubleLinkList<TCollider> {};
}

// -------------------------------------------------------------------------- //

void TCollider::frameBegin() {
  auto node = sColliderList.begin();
  TCollider * collider;

  while (node != nullptr) {
    collider = node->data;
    collider->mHitNum = 0;
    node = node->next;
  }
}

// -------------------------------------------------------------------------- //

void TCollider::frameEnd() {
  TDoubleLinkListNode<TCollider> * first;
  TDoubleLinkListNode<TCollider> * second;
  TCollider * lhs;
  TCollider * rhs;

  first = sColliderList.begin();

  while (first != nullptr) {
    lhs = first->data;
    second = first = first->next;

    if (lhs == nullptr) {
      continue;
    }

    while (second != nullptr) {
      rhs = second->data;
      second = second->next;

      if (rhs == nullptr) {
        continue;
      }

      if (
        ((lhs->mSendMask & rhs->mReceiveMask) == 0) &&
        ((rhs->mSendMask & lhs->mReceiveMask) == 0)
      ) {
        continue;
      }

      if (lhs->onCheckCollide(rhs)) {
        if ((lhs->mReceiveMask & rhs->mSendMask) != 0) {
          lhs->pushCollision(rhs);
        }

        if ((rhs->mReceiveMask & lhs->mSendMask) != 0) {
          rhs->pushCollision(lhs);
        }
      }
    }
  }
}

// -------------------------------------------------------------------------- //

bool TCollider::pushCollision(
  TCollider * const other
) {
  for (u32 i = 0; i < mHitNum; ++i) {
    if (mHitArray[i] == other) {
      return false;
    }
  }

  if (mHitNum >= mMaxHitNum) {
    return false;
  }

  mHitArray[mHitNum++] = other;
  return true;
}

// -------------------------------------------------------------------------- //

ECollideType
TBoxCollider::getCollideType() const {
  return ECollideType::BOX;
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMinX() const {
  return (mCenter.x() - mSize.x() * 0.5F);
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMinY() const {
  return (mCenter.y() - mSize.y() * 0.5F);
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMinZ() const {
  return (mCenter.z() - mSize.z() * 0.5F);
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMaxX() const {
  return (mCenter.x() + mSize.x() * 0.5F);
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMaxY() const {
  return (mCenter.y() + mSize.y() * 0.5F);
}

// -------------------------------------------------------------------------- //

float TBoxCollider::getCollideMaxZ() const {
  return (mCenter.z() + mSize.z() * 0.5F);
}

// -------------------------------------------------------------------------- //

bool TBoxCollider::onCheckCollide(
  TCollider const * const other
) const {
  switch (other->getCollideType()) {
    case ECollideType::BOX: {
      auto box = static_cast<TBoxCollider const *>(other);
      return TCollideUtil::testColliders(this, box);
    }
    case ECollideType::SPHERE: {
      auto sphere = static_cast<TSphereCollider const *>(other);
      return TCollideUtil::testColliders(this, sphere);
    }
    case ECollideType::CYLINDER: {
      auto cylinder = static_cast<TCylinderCollider const *>(other);
      return TCollideUtil::testColliders(this, cylinder);
    }
  }

  return false;
}

// -------------------------------------------------------------------------- //

ECollideType
TSphereCollider::getCollideType() const {
  return ECollideType::SPHERE;
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMinX() const {
  return (mCenter.x() - mRadius);
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMinY() const {
  return (mCenter.y() - mRadius);
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMinZ() const {
  return (mCenter.z() - mRadius);
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMaxX() const {
  return (mCenter.x() + mRadius);
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMaxY() const {
  return (mCenter.y() + mRadius);
}

// -------------------------------------------------------------------------- //

float TSphereCollider::getCollideMaxZ() const {
  return (mCenter.z() + mRadius);
}

// -------------------------------------------------------------------------- //

bool TSphereCollider::onCheckCollide(
  TCollider const * const other
) const {
  switch (other->getCollideType()) {
    case ECollideType::BOX: {
      auto box = static_cast<TBoxCollider const *>(other);
      return TCollideUtil::testColliders(box, this);
    }
    case ECollideType::SPHERE: {
      auto sphere = static_cast<TSphereCollider const *>(other);
      return TCollideUtil::testColliders(this, sphere);
    }
    case ECollideType::CYLINDER: {
      auto cylinder = static_cast<TCylinderCollider const *>(other);
      return TCollideUtil::testColliders(this, cylinder);
    }
  }

  return false;
}

// -------------------------------------------------------------------------- //

ECollideType
TCylinderCollider::getCollideType() const {
  return ECollideType::CYLINDER;
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMinX() const {
  return (mCenter.x() - mRadius);
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMinY() const {
  return (mCenter.y() - mHeight * 0.5F);
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMinZ() const {
  return (mCenter.z() - mRadius);
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMaxX() const {
  return (mCenter.x() + mRadius);
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMaxY() const {
  return (mCenter.y() + mHeight * 0.5F);
}

// -------------------------------------------------------------------------- //

float TCylinderCollider::getCollideMaxZ() const {
  return (mCenter.z() + mRadius);
}

// -------------------------------------------------------------------------- //

bool TCylinderCollider::onCheckCollide(
  TCollider const * const other
) const {
  switch (other->getCollideType()) {
    case ECollideType::BOX: {
      auto box = static_cast<TBoxCollider const *>(other);
      return TCollideUtil::testColliders(box, this);
    }
    case ECollideType::SPHERE: {
      auto sphere = static_cast<TSphereCollider const *>(other);
      return TCollideUtil::testColliders(sphere, this);
    }
    case ECollideType::CYLINDER: {
      auto cylinder = static_cast<TCylinderCollider const *>(other);
      return TCollideUtil::testColliders(this, cylinder);
    }
  }

  return false;
}

// -------------------------------------------------------------------------- //

float TCollideUtil::calcSqrDist(
  TVec2F const & from,
  TVec2F const & to
) {
  TVec2F dist;
  dist.sub(to, from);
  return dist.getSqrLength();
}

// -------------------------------------------------------------------------- //

float TCollideUtil::calcSqrDist(
  TVec3F const & from,
  TVec3F const & to
) {
  TVec3F dist;
  dist.sub(to, from);
  return dist.getSqrLength();
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::doRangesOverlap(
  float const min_a, float const max_a,
  float const min_b, float const max_b
) {
  return (min_b <= max_a && max_b >= min_a);
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testTwoBoxes(
  TVec3F const & min_a, TVec3F const & max_a,
  TVec3F const & min_b, TVec3F const & max_b
) {
  return (
    doRangesOverlap(min_a.x(), max_a.x(), min_b.x(), max_b.x()) &&
    doRangesOverlap(min_a.y(), max_a.y(), min_b.y(), max_b.y()) &&
    doRangesOverlap(min_a.z(), max_a.z(), min_b.z(), max_b.z())
  );
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testBoxSphere2D(
  TVec2F const & min, TVec2F const & max,
  TVec2F const & center, float const radius
) {
  // (Jim Arvo, Graphics Gems 2)
  // find the point in the box closest to center.
  // then check if the point is inside the sphere.
  float d = 0.0F;

  for (u32 i = 0; i < 2; ++i) {
    if (center[i] < min[i]) {
      d += squared(center[i] - min[i]);
    } else if (center[i] > max[i]) {
      d += squared(center[i] - max[i]);
    }
  }

  return (d <= squared(radius));
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testBoxSphere3D(
  TVec3F const & min, TVec3F const & max,
  TVec3F const & center, float const radius
) {
  float d = 0.0F;

  for (u32 i = 0; i < 3; ++i) {
    if (center[i] < min[i]) {
      d += squared(center[i] - min[i]);
    } else if (center[i] > max[i]) {
      d += squared(center[i] - max[i]);
    }
  }

  return (d <= squared(radius));
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testLineLine2D(
  TVec2F const & a0, TVec2F const & b0,
  TVec2F const & a1, TVec2F const & b1,
  TVec2F * pt
) {
  TVec2F ab0, ab1;
  float c0, c1, d;

  ab0.sub(b0, a0);
  ab1.sub(b1, a1);
  c0 = ab0.dot(a0);
  c1 = ab1.dot(a1);
  d = (ab0.y() * ab0.x() - ab1.x() * ab1.y());

  if (TMath<float>::abs(d) < TMath<float>::epsilon()) {
    return false;
  }

  if (pt != nullptr) {
    d = (1.0F / d);

    pt->set(
      ((ab0.x() * c0 - ab1.y() * c1) * d),
      ((ab0.y() * c1 - ab1.x() * c0) * d)
    );
  }

  return true;
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::isPtInBox2D(
  TVec2F const & min,
  TVec2F const & max,
  TVec2F const & pt
) {
  return (
    (min.x() <= pt.x() && pt.x() <= max.x()) &&
    (min.y() <= pt.y() && pt.y() <= max.y())
  );
}

// -------------------------------------------------------------------------- //

float TCollideUtil::distPtLine(
  TVec3F const & a, TVec3F const & b,
  TVec3F const & src, TVec3F * dst
) {
  TVec3F ab, bc;
  float t, d;

  ab.sub(b, a);
  bc.sub(src, ab);
  t = (ab.dot(bc) / ab.getSqrLength());

  if (t <= 0.0F) {
    d = TVec3F::dist(src, a);

    if (dst != nullptr) {
      *dst = a;
    }
  } else if (t >= 1.0F) {
    d = TVec3F::dist(src, b);

    if (dst != nullptr) {
      *dst = b;
    }
  } else {
    TVec3F pt;
    pt.mul(ab, t);
    pt.add(a);

    d = TVec3F::dist(src, pt);

    if (dst != nullptr) {
      *dst = pt;
    }
  }

  return d;
}

// -------------------------------------------------------------------------- //

float TCollideUtil::calcLineSign2D(
  TVec2F const & pt,
  TVec2F const & a,
  TVec2F const & b
) {
  return (
    (pt.x() - b.x()) * ( a.y() - b.y()) -
    ( a.x() - b.x()) * (pt.y() - b.y())
  );
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TBoxCollider const * const lhs,
  TBoxCollider const * const rhs
) {
  TVec3F min_a, max_a, min_b, max_b;
  lhs->calcCollideMinMax(&min_a, &max_a);
  rhs->calcCollideMinMax(&min_b, &max_b);
  return testTwoBoxes(min_a, max_a, min_b, max_b);
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TSphereCollider const * const lhs,
  TSphereCollider const * const rhs
) {
  float const max = TCollideUtil::squared(
    lhs->getCollideRadius() + rhs->getCollideRadius()
  );

  float const dist = TCollideUtil::calcSqrDist(
    lhs->getCollideCenter(), rhs->getCollideCenter()
  );

  return (dist <= max);
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TCylinderCollider const * const lhs,
  TCylinderCollider const * const rhs
) {
  if (!doRangesOverlap(
    lhs->getCollideMinY(), lhs->getCollideMaxY(),
    rhs->getCollideMinY(), rhs->getCollideMaxY()
  )) {
    return false;
  }

  float max, dist;

  max = TCollideUtil::squared(
    lhs->getCollideRadius() +
    rhs->getCollideRadius()
  );

  dist = TCollideUtil::calcSqrDist(
    lhs->getCollideCenter(),
    rhs->getCollideCenter()
  );

  return (dist <= max);
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TBoxCollider const * box,
  TSphereCollider const * sphere
) {
  TVec3F min, max;
  box->calcCollideMinMax(&min, &max);

  return testBoxSphere3D(min, max,
    sphere->getCollideCenter(),
    sphere->getCollideRadius()
  );
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TBoxCollider const * box,
  TCylinderCollider const * cylinder
) {
  TVec3F min, max;
  box->calcCollideMinMax(&min, &max);

  if (!doRangesOverlap(min.y(), max.y(),
    cylinder->getCollideMinY(),
    cylinder->getCollideMaxY()
  )) {
    return false;
  }

  return testBoxSphere2D(min.xz(), max.xz(),
    cylinder->getCollideCenter().xz(),
    cylinder->getCollideRadius()
  );
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TSphereCollider const * sphere,
  TCylinderCollider const * cylinder
) {
  float d, r, m, min_y, max_y;
  TVec2F a, b;
  TVec3F c;

  c = sphere->getCollideCenter();
  a = cylinder->getCollideCenter().xz();
  b = (c.xz() - a);
  d = b.getSqrLength();
  r = squared(cylinder->getCollideRadius());

  if (d > r) {
    b.normalize();
    c.x() = (a.x() + b.x() * cylinder->getCollideRadius());
    c.z() = (a.y() + b.y() * cylinder->getCollideRadius());
  }

  min_y = cylinder->getCollideMinY();
  max_y = cylinder->getCollideMaxY();
  c.y() = clamp(c.y(), min_y, max_y);
  m = (r + squared(sphere->getCollideRadius()));

  return (calcSqrDist(c, sphere->getCollideCenter()) <= m);
}

// -------------------------------------------------------------------------- //
