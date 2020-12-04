
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

float TFlockObj::getRadius(float min){
  float r = min;
  for (int i = 0; i < mHeldNum; i++)
  {
    float objrad = mHeldObjects[i]->getHalfHeight();
    if (objrad > r)
      r = objrad;
  }
  return r;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::grabObject(TNestObj * obj) {
  if (!gPlayer->canPickupObjects())
    return false;
  if (obj->getObjWeight() > mStrength - (mCarrySize / 4.0f))
    return false;
  if (mHeldNum > 32)
    return false;
  mHeldObjects[mHeldNum++] = obj;
  mCarrySize += obj->getObjWeight();
  return true;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::dropTopObject() {
  if (mHeldNum <= 0)
    return false;

  mHeldObjects[mHeldNum - 1]->drop(TVec3F(0.0f, (float)RAND(1000) / 10.0f, 0.0f));    //need to calculate what velocity to land in nest
                                                                                     //no lateral velocity so we don't need to do collision checks
  mCarrySize -= mHeldObjects[mHeldNum - 1]->getObjWeight();
  mHeldNum--;

  if (mHeldNum == 0)  //rounding errors
    mCarrySize = 0.0f;

  return true;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::dropAllObjects() {
  if (mHeldNum <= 0)
    return false;

  for (int i = 0; i < mHeldNum; i++){
    //Calculate the speed to throw the object so that it lands in the nest
    float yf = TNest::getTopY();
    float y0 = mHeldObjects[i]->getPosition().y();
    float vy = (100.0f + (50.0f * i));

    float c = y0 - yf;
    float a = -98.0f;

    if (y0 < yf)
      vy = TMath<float>::sqrt(4 * a * c) + 0.1f;

    TVec3F target = TNest::getRandomPointInside();
    TVec2F dif = target.xz() - mHeldObjects[i]->getPosition().xz();

    float tf = (-vy - TMath<float>::sqrt((vy * vy) - (4 * a * c))) / (2 * a);
    dif /= tf;

    mHeldObjects[i]->drop(TVec3F(dif.x(), vy, dif.y()));    //need to calculate what velocity to land in nest
    TNest::getNestObject()->assimilateObject(mHeldObjects[i]);
    incFlock(1, mHeldObjects[i]->getObjWeight());
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

float TNestObj::getHalfWidth() {
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

  float y = 0.0f;
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

      mVelocity.y() -= 196.0f * kInterval;  //gravity
      mPosition += mVelocity * kInterval;   //velocity
      mRotation += mRotVel * kInterval;     //rotational velocity

      gr = TCollision::findGroundBelow(
        mPosition, getHalfHeight()
      );

      if (gr != nullptr) {
        y = (gr->calcYAt(
          mPosition.xz()) + getHalfHeight()
        );

        if (mVelocity.y() < 0.0f && mPosition.y() < y){  //hit the nest
          setCollision(true);
          mState = EState::IDLE;
        }
      }
      mMtxNeedsUpdate = true;
      break;
    }
    case EState::STASHING: {
      mVelocity.y() -= 196.0f * kInterval;  //gravity
      mPosition += mVelocity * kInterval;   //velocity
      mRotation += TVec3S(TSine::fromDeg(mRotVel.x()), TSine::fromDeg(mRotVel.y()), TSine::fromDeg(mRotVel.z()));     //rotational velocity

      if (mVelocity.y() < 0.0f && mPosition.y() < TNest::getTopY()){  //hit the nest
        mState = EState::NESTING;
        setCollision(true);
      }

      mMtxNeedsUpdate = true;
      break;
    }
  }
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
  mState = EState::STASHING;
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

    mRotVel = TVec3F((float)RAND(200) - 100.0f, (float)RAND(200) - 100.0f, (float)RAND(200) - 100.0f) * kInterval;

    mVelocity = v;
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
  if (mState != EState::IDLE)
    return false;

  // we can assume this is the player due to collision masks
  mPlayer = static_cast<TPlayer *>(other);

  if (!TFlockObj::getFlockObj()->grabObject(this)){
    TVec3F modifiedCenter = mPosition;
    modifiedCenter.y() = mPlayer->getPosition().y();
    TVec3F point = mPlayer->getPosition() - modifiedCenter;
    point.normalize();
    point *= getHalfWidth();

    if (!mData->hasMeshCol)
      mPlayer->hitObject(modifiedCenter + point, mObjType);
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
  updateBlkMap();
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::setCollision(bool set){
  if (set){
    mSendMask = TAG_NESTOBJ; // turn on collision
    updateCollider();
  }
  else
    mSendMask = 0;
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

float TNestObjSphere::getHalfWidth() {
  return getCollideRadius();
}

// -------------------------------------------------------------------------- //

void TNestObjSphere::onCollide(
  TCollider * const other
) {
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
  updateBlkMap();
}

// -------------------------------------------------------------------------- //

void TNestObjBox::setCollision(bool set){
  if (set){
    mSendMask = TAG_NESTOBJ; // turn on collision
    updateCollider();
  }
  else
    mSendMask = 0;
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

float TNestObjBox::getHalfWidth() {
  return getCollideSize().x() / 2.0f;
}

// -------------------------------------------------------------------------- //

void TNestObjBox::onCollide(
  TCollider * const other
) {
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

  mNestArea = new TNestArea(dl, this);

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

// -------------------------------------------------------------------------- //

TVec3F TNest::getRandomPointInside(){
  float y = getTopY();
  TVec2F circle = TVec2F((float)(RAND(2000) - 1000), (float)(RAND(2000) - 1000));
  circle.normalize();
  circle *= sNest->getCollideRadius() * (float)RAND(1000) / 1000.0f;
  return sNest->getPosition() + TVec3F(circle.x(), (sNest->getCollideHeight() / 2.0f), circle.y());
}

// -------------------------------------------------------------------------- //

float TNest::getTopY(){
  return sNest->getPosition().y() + (sNest->getCollideHeight() / 2.0f);
}

// -------------------------------------------------------------------------- //

void TNest::assimilateObject(TNestObj * obj){
  obj->startNesting();
  mSize += obj->getObjWeight();

  setCollideRadius(64.0f + (mSize));
  setCollideHeight(32.0f + (4.0f * mSize));
  setCollideCenter(mPosition + TVec3F(0.0f, -9.0f, 0.0f));

  mNestArea->updateSize(mSize);
}

// -------------------------------------------------------------------------- //
// -----------------Collides with very tall nest area------------------------ //

void TNest::areaCollide(
  TCollider * const other
) {
  TFlockObj::getFlockObj()->dropAllObjects();
}

// -------------------------------------------------------------------------- //
// --------------------Collides with the nest itself------------------------- //

void TNest::onCollide(
  TCollider * const other
) {
  
}

// -------------------------------------------------------------------------- //

TNestArea::TNestArea(
  TDynList2 * dl, TNest * nest
)
{
  initCollider(TAG_NEST, 0, TAG_PLAYER, 1);
  setCollideCenter(nest->getPosition() + TVec3F(0.0f, 2580.0f, 0.0f));  // Bottom of collider on top of nest. can't use getTopY here yet.
  setCollideRadius(96.0f);
  setCollideHeight(5000.0f);

  updateBlkMap();

  mNest = nest;
}

// -------------------------------------------------------------------------- //

void TNestArea::updateSize(float size){
  TVec3F center = mNest->getPosition();
  center.y() = mNest->getTopY() + 2500.0f + 64.0f;

  setCollideRadius(96.0f + (size));
  setCollideCenter(center);

  updateBlkMap();
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
