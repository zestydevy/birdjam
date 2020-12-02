
#include <nusys.h>

#include "collider.hpp"
#include "collision.hpp"
#include "dynlist.hpp"
#include "math.hpp"
#include "player.hpp"
#include "score.hpp"
#include "staticobj.hpp"
#include "util.hpp"

// -------------------------------------------------------------------------- //

TFlockObj * TFlockObj::sFlockObj { nullptr };
TTimer TTimer::sInstance;

// -------------------------------------------------------------------------- //

TFlockObj::TFlockObj(TDynList2 * dl) :
  TObject { dl }
{
  if (sFlockObj == nullptr) {
    sFlockObj = this;
  }
}

// -------------------------------------------------------------------------- //

TFlockObj::~TFlockObj() {
  if (sFlockObj == this) {
    sFlockObj = nullptr;
  }
}

// -------------------------------------------------------------------------- //

void TFlockObj::incFlock(u32 n, float strength) {
  mFlockSize += n;
  mStrength += strength;
}

// -------------------------------------------------------------------------- //

TNestObj::TNestObj(
  TDynList2 * dl, EObjType type
) :
  TObject { dl },
  mObjType { type }
{
  mData = &TObject::getNestObjectInfo(type);
}

// -------------------------------------------------------------------------- //

void TNestObj::init() {
  TObject::init();

  float scale = (mScale.x() + mScale.y() + mScale.z()) / 3.0f;

  setMesh(mData->mesh);
  mObjRadius = mData->sizex;
  mObjWeight = scale * mObjRadius * mData->mass;

  initCollider(TAG_NESTOBJ, 0, TAG_PLAYER, 1);
  setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
  setCollideRadius(mObjRadius * scale);
}

// -------------------------------------------------------------------------- //

void TNestObj::update() {
  TObject::update();

  switch (mState) {
    case EState::CARRYING: {
      mPosition = mPlayer->mHeldPos;
      updateMtx();
      break;
    }
    case EState::DROPPING: {
      TCollFace const * gr;
      mPosition.y() -= 1.0F;

      gr = TCollision::findGroundBelow(
        mPosition, getCollideRadius()
      );

      if (gr != nullptr) {
        mPosition.y() = (gr->calcYAt(
          mPosition.xz()) + getCollideRadius()
        );

        mReceiveMask = TAG_PLAYER; // turn on collision
        mState = EState::IDLE;
      }
      updateMtx();

      break;
    }
  }
}

// -------------------------------------------------------------------------- //

void TNestObj::updateMtx()
{
    TObject::updateMtx();
    setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
}

// -------------------------------------------------------------------------- //

void TNestObj::onCollide(
  TCollider * const other
) {
  if (mPlayer != nullptr) {
    return; // how did this happen?
  }

  // we can assume this is the player due to collision masks
  mPlayer = static_cast<TPlayer *>(other);
  mState = EState::CARRYING;
  mReceiveMask = 0; // turn off collision
}

// -------------------------------------------------------------------------- //

void TTimer::start(u32 seconds) {
  mTime = (float)seconds;
}

// -------------------------------------------------------------------------- //

bool TTimer::update() {
  if (mTime == 0.0F) {
    return true;
  }

  mTime -= kInterval; // 30 Hz

  if (mTime < 0.0F) {
    mTime = 0.0F;
  }

  return false;
}

// -------------------------------------------------------------------------- //

float TTimer::get(u32 * min, u32 * sec, u32 * ms) const {
  if (min != nullptr) {
    *min = (u32)(mTime / SEC_PER_MIN);
  }

  if (sec != nullptr) {
    *sec = ((u32)mTime % SEC_PER_MIN);
  }

  if (ms != nullptr) {
    *ms = ((u32)(mTime * MS_PER_SEC) % MS_PER_SEC);
  }

  return mTime;
}

// -------------------------------------------------------------------------- //
