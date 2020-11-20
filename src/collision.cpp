
#include <nusys.h>

#include "collider.hpp"
#include "collision.hpp"
#include "math.hpp"

// -------------------------------------------------------------------------- //

TCollFace * TCollision::sCollFaceAry { nullptr };
u32 TCollision::sNumCollFace { 0 };

// -------------------------------------------------------------------------- //

void TCollFace::calc() {
  TVec3F a, b;
  a.sub(v1, v0);
  b.sub(v2, v0);
  nrm.cross(a, b);
  nrm.normalize();

  TVec3F v;
  v.mul(nrm, -nrm.dot(v0));
  d = v.getLength();
}

// -------------------------------------------------------------------------- //

bool TCollFace::isGround() const {
  return (nrm.y() >= 0.1F);
}

// -------------------------------------------------------------------------- //

bool TCollFace::isCeiling() const {
  return (nrm.y() <= -0.1F);
}

// -------------------------------------------------------------------------- //

bool TCollFace::isWall() const {
  return (TMath<float>::abs(nrm.y()) <= 0.1F);
}

// -------------------------------------------------------------------------- //

float TCollFace::calcDist(
  TVec3F const & pt
) const {
  return (d + nrm.dot(pt));
}

// -------------------------------------------------------------------------- //

bool TCollFace::isPtInside(
  TVec3F const & pt
) const {
  TVec3F a, b, c;
  TVec3F x, y, z;

  a.sub(v0, pt);
  b.sub(v1, pt);
  c.sub(v2, pt);

  x.cross(b, c);
  y.cross(c, a);
  z.cross(a, b);

  return (x.dot(y) >= 0.0F && x.dot(z) >= 0.0F);
}

// -------------------------------------------------------------------------- //

void TCollFace::project(
  TVec3F const & src, TVec3F * dst
) const {
  TVec3F v;
  v.mul(nrm, (nrm.dot(src) - d));
  dst->sub(v);
}

// -------------------------------------------------------------------------- //

void TCollFace::calcClosestPt(
  TVec3F const & src, TVec3F * dst
) const {
  TVec3F pt;
  project(src, &pt);

  if (isPtInside(pt)) {
    *dst = pt;
    return;
  }

  TVec3F p;
  float record, d;

  for (u32 i = 0; i < 3; ++i) {
    d = TCollideUtil::distPtLine(getVtx(i), getVtx((i + 1) % 3), src, &p);

    if (i == 0 || d < record) {
      record = d;
      *dst = p;
    }
  }
}

// -------------------------------------------------------------------------- //

bool TCollision::startup(
  TFace data[], u32 size
) {
  if (data == nullptr && size != 0) {
    return false;
  }

  sCollFaceAry = data;
  sNumCollFace = size;
  calc();

  return true;
}

// -------------------------------------------------------------------------- //

void TCollision::shutdown() {
  sCollFaceAry = nullptr;
  sNumCollFace = 0;
}

// -------------------------------------------------------------------------- //

void TCollision::calc() {
  for (u32 i = 0; i < sNumCollFace; ++i) {
    sCollFaceAry[i].calc();
  }
}

// -------------------------------------------------------------------------- //

u32 TCollision::checkRadius(
  TVec3F const & pt, float r,
  TFace const * faces[], u32 limit
) {
  if (r <= 0.0F) {
    return 0;
  }

  r *= r;

  if (faces == nullptr && limit != 0) {
    return 0;
  }

  float d;
  TVec3F p;
  u32 count = 0;

  for (u32 i = 0; i < sNumCollFace; ++i) {
    d = sCollFaceAry[i].calcDist(pt);

    if (d < 0.0F) {
      continue; // ignore backfaces
    }

    sCollFaceAry[i].calcClosestPt(pt, &p);
    d = TVec3F::distSqr(p, pt);

    if (d > r) {
      continue;
    }

    if (count < limit) {
      faces[count] = &sCollFaceAry[i];
    }

    ++count;
  }

  return count;
}

// -------------------------------------------------------------------------- //

TCollFace const *
TCollision::findClosest(
  TVec3F const & pt, float r
) {
  TCollFace const * face = nullptr;
  float record, d;
  TVec3F p;

  if (r > 0.0F) {
    r *= r;
  }

  for (u32 i = 0; i < sNumCollFace; ++i) {
    d = sCollFaceAry[i].calcDist(pt);

    if (d < 0.0F) {
      continue; // ignore backfaces
    }

    sCollFaceAry[i].calcClosestPt(pt, &p);
    d = TVec3F::distSqr(pt, p);

    if (r > 0.0F && d > r) {
      continue;
    }

    if (face == nullptr || d < record) {
      face = &sCollFaceAry[i];
      record = d;
    }
  }

  return face;
}

// -------------------------------------------------------------------------- //
