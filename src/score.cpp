
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

#include "../models/static/dropoff/model_dropoff.h"

// -------------------------------------------------------------------------- //

TFlockObj * TFlockObj::sFlockObj { nullptr };
TNest * TNest::sNest { nullptr };

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
    mHeldObjects[i]->setPosition(gPlayer->getHeldPosition(i) + mHeldObjects[i]->getMountPoint());
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

float TFlockObj::getObjRadius(int idx){
  return mHeldObjects[idx]->getHalfHeight();
}

// -------------------------------------------------------------------------- //

bool TFlockObj::grabObject(TNestObj * obj) {
  if (!gPlayer->canPickupObjects())
    return false;
  if (!canGrabObject(obj->getObjWeight()))
    return false;
  mHeldObjects[mHeldNum++] = obj;
  mCarrySize += obj->getObjWeight();
  return true;
}

// -------------------------------------------------------------------------- //

bool TFlockObj::canGrabObject(float size) {
  return size <= mStrength && mHeldNum < 32;
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
      vy = TMath<float>::sqrt(4 * a * c) + 100.0f + (50.0f * i); //Throw a lot higher because it looks cooler

    TVec3F target = TNest::getRandomPointInside();
    TVec2F dif = target.xz() - mHeldObjects[i]->getPosition().xz();

    float tf = (-vy - TMath<float>::sqrt((vy * vy) - (4 * a * c))) / (2 * a);
    dif /= tf;

    mHeldObjects[i]->drop(TVec3F(dif.x(), vy, dif.y()));    //need to calculate what velocity to land in nest
    TNest::getNestObject()->startAssimilateObject(mHeldObjects[i]);
    incFlock(1, mHeldObjects[i]->getObjWeight() / 2.0f);

    gHud->addScore((mHeldObjects[i]->getScore() * 0.005f));
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
  mDrawDistanceSquared = mData->drawDist * mData->drawDist;

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

float TNestObj::getScore() {
  if (mData->volume > 0)
    return mData->volume;
  return 0.0f;
}

// -------------------------------------------------------------------------- //

void TNestObj::increaseRadius(float threshold){
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

  if (mState == EState::IDLE || mState == EState::NESTING)
    return;

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
        mVelocity.y() = 0.0f;
        setCollision(true);

        TNest::getNestObject()->assimilateObject(this);
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
  updateCollider();
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
  if (mState == EState::NESTING)
  { //hit the player
    TVec3F modifiedCenter = mPosition;
    modifiedCenter.y() = mPlayer->getPosition().y();
    TVec3F point = mPlayer->getPosition() - modifiedCenter;
    point.normalize();
    point *= getHalfWidth();

    if ((point - modifiedCenter).getSqrLength() > (mPlayer->getPosition() - modifiedCenter).getSqrLength())
      point = modifiedCenter;   //keep player from getting stuck inside of objects while flying

    mPlayer->hitObject(modifiedCenter + point, mObjType);
  }
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
    else
      mPlayer->passthroughObject(mObjType);
    
    return false;
  }

  if (mObjType == EObjType::BALLOON)
    setMesh(TObject::getMeshGfx(EObjType::BALLOON_DEFLATED));
  
  //Save the rotation before it gets picked up, so we don't need to calculate the hanging angle every frame
  mFMountRotMtx = mFRotMtx;
  mMountRot = getRotation();
  mMountRotY = getRotation().y() - mPlayer->getRotation().y();
  setRotation(TVec3S((s16)0, (s16)0, (s16)0));

  mPlayer->collectObject(mObjType);

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

void TNestObjSphere::increaseRadius(float threshold){
  if (mState == EState::IDLE && getObjWeight() < threshold){
    setCollideRadius(4.0f * mObjRadius * getObjScale());
    updateBlkMap();
  }
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

float TNestObjSphere::getScore() {
  if (mData->volume > 0)
    return mData->volume;
  return 4 * 3.14f * getCollideRadius() * getCollideRadius();
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

void TNestObjBox::increaseRadius(float threshold){
  if (mState == EState::IDLE && getObjWeight() < threshold){
    setCollideSize(TVec3F(mSize.x() * mScale.x(), mSize.y() * mScale.y(), mSize.z() * mScale.z()) * 8.0f);
    updateBlkMap();
  }
}

// -------------------------------------------------------------------------- //

void TNestObjBox::updateCollider(){
  setCollideCenter(mPosition);
  if (mState == EState::NESTING)
    setCollideSize(TVec3F(mSize.x() * mScale.x(), mSize.x() * mScale.x(), mSize.x() * mScale.x()) * 2.0f);
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

float TNestObjBox::getScore() {
  if (mData->volume > 0)
    return mData->volume;
  return getCollideSize().x() * getCollideSize().y() / 8.0f;
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

  mNestArea = new TNestArea(mDynList, this);
  mNestArea->init();
}

// -------------------------------------------------------------------------- //

void TNest::update() {
  TObject::update();
  if (mNestArea != nullptr)
    mNestArea->update();
}

// -------------------------------------------------------------------------- //

void TNest::draw() {
  TObject::draw();
  if (mNestArea != nullptr)
    mNestArea->draw();
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

void TNest::startAssimilateObject(TNestObj * obj){
  obj->startNesting();
  mSize += obj->getObjWeight();
  mCount++;
}

// -------------------------------------------------------------------------- //

void TNest::assimilateObject(TNestObj * obj){
  setCollideRadius(getCollideRadius() + (obj->getScore() * 0.0001f));
  setCollideHeight(getCollideHeight() + (obj->getScore() * 0.0005f));
  //setCollideCenter(mPosition + TVec3F(0.0f, -9.0f, 0.0f));

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
) :
  TObject { dl }
{
  mNest = nest;

  initCollider(TAG_NEST, 0, TAG_PLAYER, 1);
  setCollideCenter(nest->getPosition() + TVec3F(0.0f, 2500.0f, 0.0f));  // Bottom of collider on top of nest. can't use getTopY here yet.
  setCollideRadius(96.0f);
  setCollideHeight(5000.0f);

  mPosition = nest->getPosition();
  mPosition.y() = mNest->getTopY() + getCollideHeight() / 32.0f;
  mRotation = TVec3S(0,0,0);
  mScale = TVec3F(getCollideRadius() / 213.0f, getCollideHeight() / 213.0f / 32.0f, getCollideRadius() / 213.0f);

  mAlwaysDraw = true;
  setMesh(dropoff_Cylinder_mesh);

  updateBlkMap();
}

// -------------------------------------------------------------------------- //

void TNestArea::updateSize(float size){
  TVec3F center = mNest->getPosition();
  center.y() = mNest->getTopY() + 2500.0f;

  setCollideRadius(96.0f + (size / 4.0f));
  setCollideCenter(center);

  updateBlkMap();

  mPosition = mNest->getPosition();
  mPosition.y() = mNest->getTopY() + getCollideHeight() / 32.0f;
  mRotation = TVec3S(0,0,0);
  mScale = TVec3F(getCollideRadius() / 213.0f, getCollideHeight() / 213.0f / 32.0f, getCollideRadius() / 213.0f);

  mMtxNeedsUpdate = true;
}

// -------------------------------------------------------------------------- //

void TNestArea::onCollide(
  TCollider * const other
) {
  mNest->areaCollide(other);
}

// -------------------------------------------------------------------------- //

void TNestArea::draw(){
  if (TFlockObj::getFlockObj()->getCapacity() > 0.0f && (gPlayer->getPosition().xz() - getPosition().xz()).getLength() > getCollideRadius() * 1.5f)
    TObject::draw();
}

// -------------------------------------------------------------------------- //
