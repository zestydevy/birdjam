
#include <nusys.h>
#include <math.h>

#include "collider.hpp"
#include "collision.hpp"
#include "dynlist.hpp"
#include "game.hpp"
#include "math.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "score.hpp"
#include "staticobj.hpp"

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

TFlockObj * TFlockObj::getFlockObj(){
  return sFlockObj;
}

// -------------------------------------------------------------------------- //

void TFlockObj::incFlock(u32 n, float strength) {
  mFlockSize += n;
  mStrength += strength;
}

// -------------------------------------------------------------------------- //

void TFlockObj::init() {
  TObject::init();
}

// -------------------------------------------------------------------------- //

void TFlockObj::update() {
  TObject::update();
  for (int i = 0; i < mHeldNum; i++)
    mHeldObjects[i]->setPosition(gPlayer->mHeldPos + mHeldObjects[i]->getMountPoint());
}

// -------------------------------------------------------------------------- //

void TFlockObj::draw() {
  TObject::draw();
}

// -------------------------------------------------------------------------- //

bool TFlockObj::grabObject(TNestObj * obj) {
  if (mHeldNum > 32)
    return false;
  mHeldObjects[mHeldNum++] = obj;
  return true;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::dropAllObjects() {
  if (mHeldNum <= 0)
    return false;
  for (int i = 0; i < mHeldNum; i++)
    mHeldObjects[i]->drop();
  mHeldNum = 0;
  return true;
}

// -------------------------------------------------------------------------- //

TNestObj::TNestObj(
  TDynList2 * dl, EObjType type
) :
  TObject { dl },
  mObjType { type }
{
  mData = &TObject::getNestObjectInfo(type);

  mMountRotMtx.identity();
  TMtx44::floatToFixed(mMountRotMtx, mFMountRotMtx);
}

// -------------------------------------------------------------------------- //

float TNestObj::getHalfHeight() {
  return 0.0f;
}

// -------------------------------------------------------------------------- //

void TNestObj::init() {
  TObject::init();

  setMesh(mData->mesh);
  mObjWeight = getObjScale() * mData->mass;

  // mDebugCube = new TObject { mDynList };
  // mDebugCube->init();
  // mDebugCube->setMesh(TObject::getMeshGfx(EObjType::DEBUG_CUBE));
}

// -------------------------------------------------------------------------- //

void TNestObj::update() {
  TObject::update();

  TVec3S speedRot {0.0f, 0.0f, 0.0f};
  TVec3S rot = getRotation();
  TVec3F v = gPlayer->getVelocity();
  switch (mState) {
    case EState::CARRYING: {
      //Calculate hanging angle
      speedRot = TVec3S(
                    TSine::atan2(v.z(), 4.0f),
                    (s16)0,
                    TSine::atan2(-v.x(), 4.0f));

      //Set rotation before hanging angle is applied
      mMountRot.set((s16)mMountRot.x(), (s16)(mMountRotY + mPlayer->getRotation().y() + (TSine::ssin(mMountTimer) * TSine::fromDeg(7.0f))), (s16)mMountRot.z());

      //Sway timer
      mMountTimer += 200;

      //Set hanging angle
      setRotation(speedRot);

      //mPosition = mPlayer->mHeldPos;
      //updateMtx();
      break;
    }
    case EState::DROPPING: {
      TCollFace const * gr;
      mPosition.y() -= 1.0F;

      gr = TCollision::findGroundBelow(
        mPosition, getHalfHeight()
      );

      if (gr != nullptr) {
        mPosition.y() = (gr->calcYAt(
          mPosition.xz()) + getHalfHeight()
        );

        setCollision(true);
        mState = EState::IDLE;
      }
      updateMtx();

      break;
    }
  }

  // mDebugCube->setPosition(getCollideCenter());

  // mDebugCube->setScale({
  //   (getCollideRadius() * 0.004F),
  //   (getCollideRadius() * 0.004F),
  //   (getCollideRadius() * 0.004F),
  // });
}

// -------------------------------------------------------------------------- //

void TNestObj::draw() {
  gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFPosMtx),
      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
  gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMountRotMtx),  //pre-hanging angle
      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
      
  if (mMesh != nullptr) {
      gSPDisplayList(mDynList->pushDL(), mMesh);
  }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);

  // if (gPlayer->getBlkMap() == getBlkMap()) {
  //   mDebugCube->draw();
  // }
}

// -------------------------------------------------------------------------- //

void TNestObj::updateCollider(){}

// -------------------------------------------------------------------------- //

void TNestObj::setCollision(bool set){}

// -------------------------------------------------------------------------- //

void TNestObj::updateMtx()
{
    TObject::updateMtx();
    TMtx44::transpose(mRotMtx, mIRotMtx);

    if (mState == EState::CARRYING){
      TMtx44 temp1, temp2, temp3;
      temp1.rotateAxisX(mMountRot.x());
      temp2.rotateAxisY(mMountRot.y());
      temp3.rotateAxisZ(mMountRot.z());
      TMtx44::concat(temp2, temp1, mMountRotMtx);
      TMtx44::concat(mMountRotMtx, temp3, mMountRotMtx);
      TMtx44::floatToFixed(mMountRotMtx, mFMountRotMtx);
    }

    updateCollider();
}

// -------------------------------------------------------------------------- //

void TNestObj::drop()
{
    mState = EState::DROPPING;

    //restore rotation to pre-pickup
    mMountRotMtx.identity();
    TMtx44::floatToFixed(mMountRotMtx, mFMountRotMtx);
    setRotation(mMountRot);
}


// -------------------------------------------------------------------------- //

TVec3F TNestObj::getMountPoint()
{
  return mRotMtx.mul(TVec3F(0.0f, -mMountDist, 0.0f));
}

// -------------------------------------------------------------------------- //

void TNestObj::onPickup(
  TCollider * const other
) {
  if (mPlayer != nullptr) {
    return; // how did this happen?
  }

  // we can assume this is the player due to collision masks
  mPlayer = static_cast<TPlayer *>(other);


  //Save the rotation before it gets picked up, so we don't need to calculate the hanging angle every frame
  mFMountRotMtx = mFRotMtx;
  mMountRot = getRotation();
  mMountRotY = getRotation().y() - mPlayer->getRotation().y();
  setRotation(TVec3S((s16)0, (s16)0, (s16)0));

  TFlockObj::getFlockObj()->grabObject(this);

  mState = EState::CARRYING;
}

// -------------------------------------------------------------------------- //

TNestObjSphere::TNestObjSphere(
  TDynList2 * dl, EObjType type
) : TNestObj { dl, type }
{
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::updateCollider(){
  setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::setCollision(bool set){
  if (set)
    mReceiveMask = TAG_PLAYER; // turn on collision
  else
    mReceiveMask = 0;
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::init() {
  TNestObj::init();

  mObjRadius = mData->sizex;

  initCollider(TAG_NESTOBJ, 0, TAG_PLAYER, 1);
  setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
  setCollideRadius(mObjRadius * getObjScale());

  updateBlkMap();
}

// -------------------------------------------------------------------------- //

float TNestObjSphere::getHalfHeight() {
  return getCollideRadius();
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::onCollide(
  TCollider * const other
) {
  if (mPlayer != nullptr) {
    return; // how did this happen?
  }

  onPickup(other);

  mMountDist = mObjRadius * getObjScale();
  setCollision(false);
}

// -------------------------------------------------------------------------- //

TNestObjBox::TNestObjBox(
  TDynList2 * dl, EObjType type
) : TNestObj { dl, type }
{
}

// -------------------------------------------------------------------------- //

void TNestObjBox::updateCollider(){
  setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
}

// -------------------------------------------------------------------------- //

void TNestObjBox::setCollision(bool set){
  if (set)
    mReceiveMask = TAG_PLAYER; // turn on collision
  else
    mReceiveMask = 0;
}

// -------------------------------------------------------------------------- //

void TNestObjBox::init() {
  TNestObj::init();

  mSize = TVec3F(mData->sizex, mData->sizey, mData->sizez);

  initCollider(TAG_NESTOBJ, 0, TAG_PLAYER, 1);
  setCollideCenter(mPosition + mRotMtx.mul(mScaleMtx.mul(TVec3F(mData->offsetx, mData->offsety, mData->offsetz))));
  setCollideSize(TVec3F(mSize.x() * mScale.x(), mSize.y() * mScale.y(), mSize.z() * mScale.z()) * 2.0f);

  updateBlkMap();
}

// -------------------------------------------------------------------------- //

float TNestObjBox::getHalfHeight() {
  return getCollideSize().y() / 2.0f;
}

// -------------------------------------------------------------------------- //

void TNestObjBox::onCollide(
  TCollider * const other
) {
  if (mPlayer != nullptr) {
    return; // how did this happen?
  }

  onPickup(other);

  mMountDist = getCollideSize().y() * 2.0f * getObjScale();
  setCollision(false);
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

  mTime -= (1.0F / 60.0F); // 60Hz

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
