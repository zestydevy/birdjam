
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
#include "util.hpp"

// -------------------------------------------------------------------------- //

TFlockObj * TFlockObj::sFlockObj { nullptr };
TNest * TNest::sNest { nullptr };
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
  if (obj->getObjWeight() > mStrength - (mCarrySize / 2.0f))
    return false;
  if (mHeldNum > 32)
    return false;
  mHeldObjects[mHeldNum++] = obj;
  mCarrySize += obj->getObjWeight();
  return true;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::dropAllObjects(TVec3F target) {
  if (mHeldNum <= 0)
    return false;
  for (int i = 0; i < mHeldNum; i++){
    mHeldObjects[i]->drop(TVec3F(0.0f, 0.0f, 0.0f));    //need to calculate what velocity to land in nest
    mHeldObjects[i]->setPosition(target);
    TNest::getNestObject()->assimilateObject(mHeldObjects[i]);
    incFlock(1, mHeldObjects[i]->getObjWeight() / 2.0f);
  }
  mHeldNum = 0;
  mCarrySize = 0.0f;
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

  TMtx44 mMountRotMtx;
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
  mObjWeight = mData->mass;

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
      mMtxNeedsUpdate = true;
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
  if (!mInCamera)
        return;

  if (mMtxNeedsUpdate)
      updateMtx();

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

void TNestObj::startNesting(){
  mState = EState::NESTING;
}

// -------------------------------------------------------------------------- //

void TNestObj::updateCollider(){}

// -------------------------------------------------------------------------- //

void TNestObj::setCollision(bool set){}

// -------------------------------------------------------------------------- //

void TNestObj::updateMtx()
{
    TObject::updateMtx();
    //TMtx44::transpose(mRotMtx, mIRotMtx);

    if (mState == EState::CARRYING){
      TMtx44 temp1, temp2, temp3, mMountRotMtx;
      mMountRotMtx.identity();
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

void TNestObj::drop(TVec3F v)
{
    mState = EState::DROPPING;
    setCollision(true);

    //restore rotation to pre-pickup
    TMtx44 mMountRotMtx;
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

bool TNestObj::onPickup(
  TCollider * const other
) {
  // we can assume this is the player due to collision masks
  mPlayer = static_cast<TPlayer *>(other);

  if (!TFlockObj::getFlockObj()->grabObject(this)){
    if (!mData->hasMeshCol)
      mPlayer->hitObject(mPosition, mObjType);
    return false;
  }

  if (mObjType == EObjType::BALLOON)
    setMesh(TObject::getMeshGfx(EObjType::BALLOON_DEFLATED));
  
  //Save the rotation before it gets picked up, so we don't need to calculate the hanging angle every frame
  mFMountRotMtx = mFRotMtx;
  mMountRot = getRotation();
  mMountRotY = getRotation().y() - mPlayer->getRotation().y();
  setRotation(TVec3S((s16)0, (s16)0, (s16)0));

  mState = EState::CARRYING;
  return true;
}

// -------------------------------------------------------------------------- //

TNestObjSphere::TNestObjSphere(
  TDynList2 * dl, EObjType type
) : TNestObj { dl, type }
{
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::updateCollider(){
  setCollideCenter(mPosition);
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

  initCollider(TAG_NESTOBJ, TAG_NESTOBJ, TAG_PLAYER, 1);
  setCollideCenter(mPosition);
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

  if (onPickup(other)){
    mMountDist = mObjRadius * getObjScale();
    setCollision(false);
  }
}

// -------------------------------------------------------------------------- //

TNestObjBox::TNestObjBox(
  TDynList2 * dl, EObjType type
) : TNestObj { dl, type }
{
}

// -------------------------------------------------------------------------- //

void TNestObjBox::updateCollider(){
  setCollideCenter(mPosition);
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

  initCollider(TAG_NESTOBJ, TAG_NESTOBJ, TAG_PLAYER, 1);
  setCollideCenter(mPosition);
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

  if (onPickup(other)){
    mMountDist = getCollideSize().y() * 2.0f * getObjScale();
    setCollision(false);
  }
}

// -------------------------------------------------------------------------- //

TNest::TNest(
  TDynList2 * dl
) :
  TObject { dl }
{
  initCollider(TAG_NEST, 0, TAG_NESTOBJ, 1);
  setCollideCenter(mPosition + TVec3F(0.0f, -9.0f, 0.0f));
  setCollideRadius(64.0f);
  setCollideHeight(32.0f);

  updateBlkMap();

  mNestArea = new TNestArea(dl, this, mPosition, 64.0f, 5000.0f);

  sNest = this;
}

// -------------------------------------------------------------------------- //

TNest::~TNest()
{
  delete mNestArea;
}

// -------------------------------------------------------------------------- //

TNest * TNest::getNestObject() {
  return sNest;
}

// -------------------------------------------------------------------------- //

void TNest::init() {
  TObject::init();
}

// -------------------------------------------------------------------------- //

void TNest::update() {
  TObject::update();
}

// -------------------------------------------------------------------------- //

void TNest::draw() {
  TObject::draw();
}

void TNest::assimilateObject(TNestObj * obj){
  obj->startNesting();
  mSize += obj->getObjWeight();
}

// -------------------------------------------------------------------------- //
// -----------------Collides with very tall nest area------------------------ //

void TNest::areaCollide(
  TCollider * const other
) {
  TFlockObj::getFlockObj()->dropAllObjects(mPosition);
}

// -------------------------------------------------------------------------- //
// --------------------Collides with the nest itself------------------------- //

void TNest::onCollide(
  TCollider * const other
) {
  
}

// -------------------------------------------------------------------------- //

TNestArea::TNestArea(
  TDynList2 * dl, TNest * nest, TVec3F center, float radius, float height
)
{
  initCollider(TAG_NEST, 0, TAG_PLAYER, 1);
  setCollideCenter(center);
  setCollideRadius(radius);
  setCollideHeight(height);

  updateBlkMap();

  mNest = nest;
}

// -------------------------------------------------------------------------- //

void TNestArea::onCollide(
  TCollider * const other
) {
  mNest->areaCollide(other);
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
