
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

void TBoxCollider::calcCollideMinMax(
  TVec3F * const min,
  TVec3F * const max
) const {
  TVec3F half;
  half.mul(mSize, 0.5F);

  if (min != nullptr) {
    min->sub(mCenter, half);
  }

  if (max != nullptr) {
    max->add(mCenter, half);
  }
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
  float min_a, max_a, min_b, max_b;
  min_a = lhs->getCollideCenter().y();
  max_a = (min_a + lhs->getCollideHeight());
  min_b = rhs->getCollideCenter().y();
  max_b = (min_b + rhs->getCollideHeight());

  if (!doRangesOverlap(min_a, max_a, min_b, max_b)) {
    return false;
  }

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
  TBoxCollider const *,
  TSphereCollider const *
) {
  return false; // TODO
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TBoxCollider const *,
  TCylinderCollider const *
) {
  return false; // TODO
}

// -------------------------------------------------------------------------- //

bool TCollideUtil::testColliders(
  TSphereCollider const *,
  TCylinderCollider const *
) {
  return false; // TODO
}

// -------------------------------------------------------------------------- //
