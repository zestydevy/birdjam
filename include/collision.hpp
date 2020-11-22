
#ifndef INCLUDE_COLLISION_HPP
#define INCLUDE_COLLISION_HPP

#include <nusys.h>

#include "math.hpp"

// -------------------------------------------------------------------------- //

class TCollision {

  public:

  struct TFace {

    TVec3F vtx[3];
    TVec3F nrm;
    float d;

    void calc();

    bool isGround() const;
    bool isCeiling() const;
    bool isWall() const;

    float calcDist(TVec3F const & pt) const; // distance to PLANE, not POLYGON
    bool isPtInside(TVec3F const & pt) const;
    void project(TVec3F const & src, TVec3F * dst) const;
    void calcClosestPt(TVec3F const & src, TVec3F * dst) const;

    private:

    static bool calcNrm(
      TVec3F const & v0,
      TVec3F const & v1,
      TVec3F const & v2,
      TVec3F * nrm
    );

  };

  static bool startup(TFace data[], u32 size);
  static void shutdown();

  static void calc();

  static u32 checkRadius(
    TVec3F const & pt, float r,
    TFace const * faces[] = nullptr, u32 limit = 0
  );

  static TFace const * findClosest(
    TVec3F const & pt, float r = 0.0F
  );

  private:

  static TFace * sCollFaceAry;
  static u32 sNumCollFace;

};

// -------------------------------------------------------------------------- //

using TCollFace = TCollision::TFace;

// -------------------------------------------------------------------------- //

#endif
