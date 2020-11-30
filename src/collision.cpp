
#include <nusys.h>

#include "collider.hpp"
#include "collision.hpp"
#include "heap.hpp"
#include "math.hpp"

// -------------------------------------------------------------------------- //

TCollFace * TCollision::sCollFaceAry { nullptr };
u32 TCollision::sNumCollFace { 0 };

TCollPacket * TCollision::sCollPktAry { nullptr };
u32 TCollision::sMaxNumCollPkt { 0 };
u32 TCollision::sNumCollPkt { 0 };

float TCollision::sBlkMapSz { 0.0F };
TCollPacket ** TCollision::sBlkMap { nullptr };
u32 TCollision::sNumBlkMap { 0 };

// -------------------------------------------------------------------------- //

void TCollFace::calc() {
  TVec3F a, b;
  a.sub(vtx[1], vtx[0]);
  b.sub(vtx[2], vtx[0]);
  nrm.cross(a, b);
  nrm.normalize();
  d = nrm.dot(vtx[0]);
}

// -------------------------------------------------------------------------- //

bool TCollFace::isGround() const {
  return (nrm.y() >= 0.1F);
}

// -------------------------------------------------------------------------- //

float TCollFace::minX() const {
  float x = vtx[0].x();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].x() < x) {
      x = vtx[i].x();
    }
  }

  return x;
}

// -------------------------------------------------------------------------- //

float TCollFace::maxX() const {
  float x = vtx[0].x();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].x() > x) {
      x = vtx[i].x();
    }
  }

  return x;
}

// -------------------------------------------------------------------------- //

float TCollFace::minY() const {
  float y = vtx[0].y();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].y() < y) {
      y = vtx[i].y();
    }
  }

  return y;
}

// -------------------------------------------------------------------------- //

float TCollFace::maxY() const {
  float y = vtx[0].y();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].y() > y) {
      y = vtx[i].y();
    }
  }

  return y;
}

// -------------------------------------------------------------------------- //

float TCollFace::minZ() const {
  float z = vtx[0].z();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].z() < z) {
      z = vtx[i].z();
    }
  }

  return z;
}

// -------------------------------------------------------------------------- //

float TCollFace::maxZ() const {
  float z = vtx[0].z();

  for (u32 i = 1; i < 3; ++i) {
    if (vtx[i].z() > z) {
      z = vtx[i].z();
    }
  }

  return z;
}

// -------------------------------------------------------------------------- //

bool TCollFace::isXZInside(
  TVec2F const & pt
) const {
  float a, b, c;

  a = TCollideUtil::calcLineSign2D(pt, vtx[0].xz(), vtx[1].xz());
  b = TCollideUtil::calcLineSign2D(pt, vtx[1].xz(), vtx[2].xz());
  c = TCollideUtil::calcLineSign2D(pt, vtx[2].xz(), vtx[0].xz());

  if (
    ((a < 0.0F) || (b < 0.0F) || (c < 0.0F)) &&
    ((a > 0.0F) || (b > 0.0F) || (c > 0.0F))
  ) {
    return false;
  }

  return true;
}

// -------------------------------------------------------------------------- //

bool TCollFace::isXYZInside(
  TVec3F const & pt
) const {
  TVec3F a, b, c;
  TVec3F x, y, z;

  a.sub(vtx[0], pt);
  b.sub(vtx[1], pt);
  c.sub(vtx[2], pt);

  x.cross(b, c);
  y.cross(c, a);
  z.cross(a, b);

  return (x.dot(y) >= 0.0F && x.dot(z) >= 0.0F);
}

// -------------------------------------------------------------------------- //

float TCollFace::calcYAt(
  TVec2F const & xz
) const {
  if (nrm.y() == 0.0F) {
    return 0.0F;
  }

  return ((d - nrm.x() * xz.x() - nrm.z() * xz.y()) / nrm.y());
}

// -------------------------------------------------------------------------- //

float TCollFace::calcDist(
  TVec3F const & pt
) const {
  TVec3F ab;
  ab.sub(pt, vtx[0]);
  return nrm.dot(ab);
}

// -------------------------------------------------------------------------- //

void TCollFace::project(
  TVec3F const & src, TVec3F * dst
) const {
  TVec3F v;
  v.mul(nrm, (nrm.dot(src) - d));
  dst->sub(src, v);
}

// -------------------------------------------------------------------------- //

void TCollFace::calcClosestPt(
  TVec3F const & src, TVec3F * dst
) const {
  TVec3F pt;
  project(src, &pt);

  if (isXYZInside(pt)) {
    *dst = pt;
    return;
  }

  TVec3F p;
  float record, d;

  for (u32 i = 0; i < 3; ++i) {
    d = TCollideUtil::distPtLine(
      vtx[i], vtx[(i + 1) % 3], src, &p
    );

    if (i == 0 || d < record) {
      record = d;
      *dst = p;
    }
  }
}

// -------------------------------------------------------------------------- //

bool TCollision::startup(
  TFace data[], u32 size, THeap * heap,
  u32 num_pkt, u16 num_blk, float blk_sz
) {
  if (data == nullptr && size != 0) {
    return false;
  }

  if (num_pkt < size) {
    return false;
  }

  if (num_blk == 0 || blk_sz <= 0.0F) {
    return false;
  }

  sCollFaceAry = data;
  sNumCollFace = size;

  sCollPktAry = new(heap) TPacket[num_pkt];
  sMaxNumCollPkt = num_pkt;
  sNumCollPkt = 0;

  if (sCollPktAry == nullptr) {
    shutdown();
    return false;
  }

  sBlkMap = new(heap) TPacket * [num_blk * num_blk];
  sNumBlkMap = num_blk;
  sBlkMapSz = blk_sz;

  if (sBlkMap == nullptr) {
    shutdown();
    return false;
  }

  if (!calc()) {
    shutdown();
    return false;
  }

  return true;
}

// -------------------------------------------------------------------------- //

void TCollision::shutdown() {
  sCollFaceAry = nullptr;
  sNumCollFace = 0;

  delete[] sCollPktAry;
  sCollPktAry = nullptr;
  sMaxNumCollPkt = 0;
  sNumCollPkt = 0;

  delete[] sBlkMap;
  sBlkMap = nullptr;
  sBlkMapSz = 0.0F;
  sNumBlkMap = 0;
}

// -------------------------------------------------------------------------- //

bool TCollision::calc() {
  sNumCollPkt = 0;

  for (u32 i = 0; i < (sNumBlkMap * sNumBlkMap); ++i) {
    sBlkMap[i] = nullptr;
  }

  u32 l, b, r, t;
  TPacket * pkt;

  for (u32 i = 0; i < sNumCollFace; ++i) {
    sCollFaceAry[i].calc();
    getFaceBlk(&sCollFaceAry[i], &l, &b, &r, &t);

    for (u32 y = b; y <= t; ++y) {
      for (u32 x = l; x <= r; ++x) {
        if (!isFaceInBlk(&sCollFaceAry[i], x, y)) {
          continue;
        }

        pkt = fetchPkt();

        if (pkt == nullptr) {
          return false;
        }

        pkt->face = &sCollFaceAry[i];
        pkt->next = sBlkMap[y * sNumBlkMap + x];
        sBlkMap[y * sNumBlkMap + x] = pkt;
      }
    }
  }

  return true;
}

// -------------------------------------------------------------------------- //

u32 TCollision::checkRadius(
  TVec3F const & pt, float rd,
  TFace const * faces[], u32 limit
) {
  if (rd <= 0.0F) {
    return 0;
  }

  u32 l, b, r, t;
  getSphereBlk(pt, rd, &l, &b, &r, &t);

  rd *= rd;

  if (faces == nullptr && limit != 0) {
    return 0;
  }

  TPacket const * pkt;
  TFace const * face;
  u32 count = 0;
  TVec3F p;
  float d;

  for (u32 y = b; y <= t; ++y) {
    for (u32 x = l; x <= r; ++x) {
      pkt = sBlkMap[y * sNumBlkMap + x];

      while (pkt != nullptr) {
        face = pkt->face;
        pkt = pkt->next;
        d = face->calcDist(pt);

        if (d < 0.0F) {
          continue; // ignore backfaces
        }

        face->calcClosestPt(pt, &p);
        d = TVec3F::distSqr(p, pt);

        if (d > rd) {
          continue;
        }

        if (count < limit) {
          faces[count] = face;
        }

        ++count;
      }
    }
  }

  for (u32 i = 0; i < sNumCollFace; ++i) {
  }

  return count;
}

// -------------------------------------------------------------------------- //

TCollFace const *
TCollision::findClosest(
  TVec3F const & pt, float rd
) {
  TFace const * closest = nullptr;
  float record, d;
  TVec3F p;

  u32 l, b, r, t;
  getSphereBlk(pt, rd, &l, &b, &r, &t);

  if (rd > 0.0F) {
    rd *= rd;
  }

  TPacket const * pkt;
  TFace const * face;

  for (u32 y = b; y <= t; ++y) {
    for (u32 x = l; x <= r; ++x) {
      pkt = sBlkMap[y * sNumBlkMap + x];

      while (pkt != nullptr) {
        face = pkt->face;
        pkt = pkt->next;

        d = face->calcDist(pt);

        if (d < 0.0F) {
          continue; // ignore backfaces
        }

        face->calcClosestPt(pt, &p);
        d = TVec3F::distSqr(pt, p);

        if (rd > 0.0F && d > rd) {
          continue;
        }

        if (closest == nullptr || d < record) {
          closest = face;
          record = d;
        }
      }
    }
  }

  return closest;
}

// -------------------------------------------------------------------------- //

TCollFace const *
TCollision::findGroundBelow(
  TVec3F const & pt, float bias, float limit
) {
  TFace const * gr = nullptr;
  TVec2F xz = pt.xz();
  float py = (pt.y() + bias);
  float record;

  u32 l, b, r, t;
  TFace const * face;
  TPacket const * pkt;
  getSphereBlk(pt, 0.0F, &l, &b, &r, &t);

  for (u32 y = b; y <= t; ++y) {
    for (u32 x = l; x <= r; ++x) {
      pkt = sBlkMap[y * sNumBlkMap + x];

      while (pkt != nullptr) {
        face = pkt->face;
        pkt = pkt->next;

        if (!face->isGround()) {
          continue;
        }

        if (py < face->minY()) {
          continue;
        }

        if (!face->isXZInside(xz)) {
          continue;
        }

        float y = face->calcYAt(xz);

        if (py < y) {
          continue;
        }

        if (limit > 0.0F && TMath<float>::abs(py - y) > limit) {
          continue;
        }

        if (gr == nullptr || y > record) {
          record = y;
          gr = face;
        }
      }
    }
  }

  return gr;
}

// -------------------------------------------------------------------------- //

TCollPacket *
TCollision::fetchPkt() {
  if (sNumCollPkt == sMaxNumCollPkt) {
    return nullptr;
  }

  return &sCollPktAry[sNumCollPkt++];
}

// -------------------------------------------------------------------------- //

void TCollision::getBlkBox(
  u32 x, u32 y,
  float * min_x, float * min_z,
  float * max_x, float * max_z
) {
  if (min_x != nullptr) {
    *min_x = (sBlkMapSz * (float)x);
  }

  if (max_x != nullptr) {
    *max_x = (sBlkMapSz * (float)(x + 1));
  }

  if (min_z != nullptr) {
    *min_z = (sBlkMapSz * (float)y);
  }

  if (max_z != nullptr) {
    *max_z = (sBlkMapSz * (float)(y + 1));
  }
}

// -------------------------------------------------------------------------- //

void TCollision::getSphereBlk(
  TVec3F const & pt, float rd,
  u32 * l, u32 * b, u32 * r, u32 * t
) {
  float half = ((float)sNumBlkMap * sBlkMapSz * 0.5F);
  float i_sz = (1.0F / sBlkMapSz);

  if (rd < 0.0F) {
    rd = 0.0F;
  }

  if (l != nullptr) {
    *l = calcBlkIdx((pt.x() - rd), half, i_sz);
  }

  if (r != nullptr) {
    *r = calcBlkIdx((pt.x() + rd), half, i_sz);
  }

  if (b != nullptr) {
    *b = calcBlkIdx((pt.z() - rd), half, i_sz);
  }

  if (t != nullptr) {
    *t = calcBlkIdx((pt.z() + rd), half, i_sz);
  }
}

// -------------------------------------------------------------------------- //

bool TCollision::isSphereInBlk(
  TVec3F const & pt, float rd, u32 x, u32 y
) {
  TVec2F min, max;
  getBlkBox(x, y, &min.x(), &min.y(), &max.x(), &max.y());
  return TCollideUtil::testBoxSphere2D(min, max, pt.xz(), rd);
}

// -------------------------------------------------------------------------- //

void TCollision::getFaceBlk(
  TFace const * face,
  u32 * l, u32 * b, u32 * r, u32 * t
) {
  float half = ((float)sNumBlkMap * sBlkMapSz * 0.5F);
  float i_sz = (1.0F / sBlkMapSz);

  if (l != nullptr) {
    *l = calcBlkIdx(face->minX(), half, i_sz);
  }

  if (r != nullptr) {
    *r = calcBlkIdx(face->maxX(), half, i_sz);
  }

  if (b != nullptr) {
    *b = calcBlkIdx(face->minZ(), half, i_sz);
  }

  if (t != nullptr) {
    *t = calcBlkIdx(face->maxZ(), half, i_sz);
  }
}

// -------------------------------------------------------------------------- //

bool TCollision::isFaceInBlk(
  TFace const * face, u32 x, u32 y
) {
  TVec2F min, max;
  TVec2F bl, br, tl, tr;
  TVec2F a, b, c;

  getBlkBox(x, y, &min.x(), &min.y(), &max.x(), &max.y());

  // test A: any of the vertices are inside the block
  for (u32 i = 0; i < 3; ++i) {
    if (TCollideUtil::isPtInBox2D(
      min, max, face->vtx[i].xz()
    )) {
      return true;
    }
  }

  // test B: any of the corners are inside the triangle
  bl.set(min.x(), min.y());
  br.set(max.x(), min.y());
  tl.set(min.x(), max.y());
  tr.set(max.x(), max.y());

  if (
    face->isXZInside(bl) || face->isXZInside(br) ||
    face->isXZInside(tl) || face->isXZInside(tr)
  ) {
    return true;
  }

  // test C: any of the lines intersect
  a = face->vtx[0].xz();
  b = face->vtx[1].xz();
  c = face->vtx[2].xz();

  if (
    TCollideUtil::testLineLine2D(bl, br, a, b) ||
    TCollideUtil::testLineLine2D(bl, tl, a, b) ||
    TCollideUtil::testLineLine2D(tl, tr, a, b) ||
    TCollideUtil::testLineLine2D(br, tr, a, b) ||

    TCollideUtil::testLineLine2D(bl, br, b, c) ||
    TCollideUtil::testLineLine2D(bl, tl, b, c) ||
    TCollideUtil::testLineLine2D(tl, tr, b, c) ||
    TCollideUtil::testLineLine2D(br, tr, b, c) ||

    TCollideUtil::testLineLine2D(bl, br, c, a) ||
    TCollideUtil::testLineLine2D(bl, tl, c, a) ||
    TCollideUtil::testLineLine2D(tl, tr, c, a) ||
    TCollideUtil::testLineLine2D(br, tr, c, a)
  ) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

u32 TCollision::calcBlkIdx(
  float x, float half, float i_sz
) {
  auto max = (s32)(sNumBlkMap - 1);
  auto idx = (s32)((half + x) * i_sz);
  return (u32)TMath<s32>::clamp(idx, 0, max);
}

// -------------------------------------------------------------------------- //
