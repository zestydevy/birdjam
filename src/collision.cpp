
#include <nusys.h>

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

bool TCollision::startup(
  TFace data[], u32 size
) {
  if (data == nullptr && size != 0) {
    return false;
  }

  sCollFaceAry = data;
  sNumCollFace = size;
  calc();
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

  if (faces == nullptr && limit != 0) {
    return 0;
  }

  u32 count = 0;

  for (u32 i = 0; i < sNumCollFace; ++i) {
    float d = sCollFaceAry[i].calcDist(pt);

    if (d < 0.0F) {
      continue; // ignore backfaces
    }

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
  float record;
  TCollFace const * face = nullptr;

  for (u32 i = 0; i < sNumCollFace; ++i) {
    float d = sCollFaceAry[i].calcDist(pt);

    if (d < 0.0F) {
      continue; // ignore backfaces
    }

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
