
#include <nusys.h>

#include "hud.hpp"
#include "sprite.hpp"
#include "util.hpp"

#include "../models/ovl/sprites/sp_hud.h"

// -------------------------------------------------------------------------- //

#define MAX_SCORE 999999

// -------------------------------------------------------------------------- //

THud * gHud { nullptr };

// -------------------------------------------------------------------------- //

template<typename T>
T Lerp(T p0, T p1, float mu) {
  return (T)((float)p0 * (1.0F - mu) + (float)p1 * mu);
}

// -------------------------------------------------------------------------- //

template<typename T>
T Sinerp(T p0, T p1, float mu) {
  return Lerp<T>(p0, p1, TSine::ssin(TSine::fromDeg(mu * 90.0F)));
}

// -------------------------------------------------------------------------- //

template<typename T>
T Lagrange(T p0, T p1, T p2, float mu) {
  float t0 = ((1.0F - mu) * (1.0F - mu));
  float t1 = (2.0F * (1.0F - mu) * mu);
  float t2 = (mu * mu);

  return (T)((float)p0 * t0 + (float)p1 * t1 + (float)p2 * t2);
}

// -------------------------------------------------------------------------- //

float THudAlarm::get() const {
  if (mAlarm == 0.0F) {
    return 1.0F;
  }

  return (mTime / mAlarm);
}

// -------------------------------------------------------------------------- //

float THudAlarm::get(float a, float b) const {
  if (a >= b) {
    return 0.0F;
  }

  float t = get();

  if (t < a) {
    return 0.0F;
  }

  if (t > b) {
    return 1.0F;
  }

  return ((t - a) / (b - a));
}

// -------------------------------------------------------------------------- //

void THudAlarm::set(float t) {
  if (t < 0.0F) {
    t = 0.0F;
  }

  mTime = 0.0F;
  mAlarm = t;
}

// -------------------------------------------------------------------------- //

bool THudAlarm::update() {
  if (mTime >= mAlarm) {
    return false;
  }

  mTime += kInterval;

  if (mTime >= mAlarm) {
    mTime = mAlarm;
  }

  return off();
}

// -------------------------------------------------------------------------- //

bool THudAlarm::off() const {
  return (mTime >= mAlarm);
}

// -------------------------------------------------------------------------- //

void THudScore::hide() {
  mState = ST_HIDE;
}

// -------------------------------------------------------------------------- //

void THudScore::show() {
  mState = ST_SHOW;
  mStateTimer.set(1.0F);

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }
}

// -------------------------------------------------------------------------- //

void THudScore::lower() {
  mState = ST_LOWER;
  mStateTimer.set(1.0F);
}

// -------------------------------------------------------------------------- //

void THudScore::raise() {
  mState = ST_RAISE;
  mStateTimer.set(0.5F);
}

// -------------------------------------------------------------------------- //

u32 THudScore::getScore() const {
  return mFinScore;
}

// -------------------------------------------------------------------------- //

void THudScore::setScore(u32 pts) {
  if (mState != ST_SHOW) {
    mBounceTime = 1.0F;
  }

  mFinScore = pts;
}

// -------------------------------------------------------------------------- //

void THudScore::init() {
  mSprite[SPR_SCORE].load(hud_score_sprite);
  mSprite[SPR_DOT].load(hud_dot_sprite);
  mSprite[SPR_METRIC].load(hud_ft_sprite);

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    mSprite[SPR_SCORE_0 + i].load(
      THud::getDigitSprite(0)
    );
  }

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_FASTCOPY);
  }
}

// -------------------------------------------------------------------------- //

void THudScore::update() {
  u32 digits[NUM_SCORE_DIGITS];
  s16 digit_y[NUM_SCORE_DIGITS];
  s16 score_y;

  switch (mState) {
    case ST_SHOW: {
      setOnSprite(SPR_SCORE);

      score_y = Lerp<s16>(
        -95, 5, mStateTimer.get(0.0F, 0.6F)
      );

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        float a = (0.0F + 0.08F * (float)i);
        float b = (a + 0.5F);

        digit_y[i] = Lagrange<s16>(
          -40, 70, 34, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_LOWER: {
      setOnSprite(SPR_SCORE);

      score_y = Lerp<s16>(
        -40, 5, mStateTimer.get(0.0F, 0.75F)
      );

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        float a = (0.0F + 0.05F * (float)i);
        float b = (a + 0.6F);

        digit_y[i] = Lagrange<s16>(
          5, 70, 34, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_RAISE: {
      setOnSprite(SPR_SCORE);
      score_y = Lerp<s16>(5, -25, mStateTimer.get());

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = Lerp<s16>(35, 5, mStateTimer.get());
      }

      if (mStateTimer.update()) {
        mState = ST_UP;
      }

      break;
    }
    case ST_DOWN: {
      setOnSprite(SPR_SCORE);
      score_y = 5;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = 34;
      }

      break;
    }
    case ST_UP: {
      setOffSprite(SPR_SCORE);
      score_y = 0;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = 5;
      }

      break;
    }
  }

  if (mState != ST_HIDE) {
    for (u32 i = SPR_SCORE_0; i <= SPR_METRIC; ++i) {
      setOnSprite(i);
    }
  }

  mSprite[SPR_SCORE].setPosition({ (s16)9, score_y });

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    s16 x = (s16)(9 + 20 * i);

    if (i >= NUM_INT_PLACES) {
      x += 9;
    }

    mSprite[SPR_SCORE_0 + i].setPosition(
      { x, digit_y[i] }
    );
  }

  mSprite[SPR_DOT].setPosition({
    (s16)(9 + 20 * NUM_INT_PLACES),
    (s16)(13 + (digit_y[NUM_INT_PLACES - 1] + digit_y[NUM_INT_PLACES]) / 2),
  });

  mSprite[SPR_METRIC].setPosition({
    (s16)(18 + 20 * NUM_SCORE_DIGITS),
    (s16)(10 + digit_y[NUM_SCORE_DIGITS - 1]),
  });

  if (mBounceTime > 0.0F) {
    mBounceTime -= kInterval;

    if (mBounceTime < 0.0F) {
      mBounceTime = 0.0F;
    }
  }

  if ((u32)mCurScore != mFinScore) {
    if (mBounceTime == 0.0F && mState != ST_SHOW) {
      mBounceTime = 1.0F;
    }

    float final = (float)mFinScore;

    if (mCurScore < final) {
      mCurScore += (SCORE_SPEED * kInterval);

      if (mCurScore > final) {
        mCurScore = final;
      }
    } else {
      mCurScore -= (SCORE_SPEED * kInterval);

      if (mCurScore < final) {
        mCurScore = final;
      }
    }
  }

  if (mBounceTime != 0.0F) {
    TVec2S pos;
    s32 ofs;

    ofs = TMath<s32>::abs((s32)(5.0F *
      TSine::ssin(TSine::fromDeg(mBounceTime * 360 * 2))
    ));

    for (u32 i = SPR_SCORE_0; i <= SPR_METRIC; ++i) {
      pos = mSprite[i].getPosition();
      pos.y() += ofs;
      mSprite[i].setPosition(pos);
    }
  }

  THud::splitDigits((u32)mCurScore, digits, NUM_SCORE_DIGITS);

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    mSprite[SPR_SCORE_0 + i].load(
      THud::getDigitSprite(digits[i])
    );
  }
}

// -------------------------------------------------------------------------- //

void THudScore::draw() {
  if (mState == ST_HIDE) {
    return;
  }

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    if (mSpriteMask & (1U << i)) {
      continue;
    }

    mSprite[i].draw();
  }
}

// -------------------------------------------------------------------------- //

void THudTime::hide() {
  mState = ST_HIDE;
}

// -------------------------------------------------------------------------- //

void THudTime::show(u32 min) {
  mState = ST_SHOW_WAIT;
  mStateTimer.set(1.25F);
  flash(min);

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }
}

// -------------------------------------------------------------------------- //

void THudTime::lower() {
  mState = ST_LOWER;
  mStateTimer.set(1.0F);
}

// -------------------------------------------------------------------------- //

void THudTime::raise() {
  mState = ST_RAISE;
  mStateTimer.set(0.5F);
}

// -------------------------------------------------------------------------- //

void THudTime::flash(u32 min) {
  mFlashTime = 3.0F;
  mFlashMin = min;
}

// -------------------------------------------------------------------------- //

void THudTime::init() {
  mSprite[SPR_TIME].load(hud_time_sprite);
  mSprite[SPR_COLON].load(hud_colon_sprite);
  mSprite[SPR_MIN].load(THud::getDigitSprite(0));
  mSprite[SPR_SEC_0].load(THud::getDigitSprite(0));
  mSprite[SPR_SEC_1].load(THud::getDigitSprite(0));

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_FASTCOPY);
  }
}

// -------------------------------------------------------------------------- //

void THudTime::update(
  TTimer const * clock
) {
  s16 digit_y[4]; // [0] min, [1] colon, [2-3] sec 0-1
  s16 time_y, x = 228;
  u32 min, sec;
  float t;

  switch (mState) {
    case ST_LOWER: {
      setOnSprite(SPR_TIME);
      time_y = Lerp<s16>(-40, 5, mStateTimer.get(0.0F, 0.75F));

      for (u32 i = 0; i < 4; ++i) {
        float a = (0.0F + 0.05F * (float)i);
        float b = (a + 0.6F);

        digit_y[i] = Lagrange<s16>(
          5, 70, 34, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_RAISE: {
      setOnSprite(SPR_TIME);
      time_y = Lerp<s16>(5, -25, mStateTimer.get());

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = Lerp<s16>(35, 5, mStateTimer.get());
      }

      if (mStateTimer.update()) {
        mState = ST_UP;
      }

      break;
    }
    case ST_DOWN: {
      setOnSprite(SPR_TIME);
      time_y = 5;

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = 34;
      }

      break;
    }
    case ST_UP: {
      setOffSprite(SPR_TIME);
      time_y = 0;

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = 5;
      }

      break;
    }
    case ST_SHOW_WAIT: {
      setOnSprite(SPR_TIME);
      x = 115;
      time_y = 100;

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = (time_y + 29);
      }

      if (mStateTimer.update()) {
        mState = ST_SHOW_SLIDE;
        mStateTimer.set(1.0F);
      }

      break;
    }
    case ST_SHOW_SLIDE: {
      setOnSprite(SPR_TIME);
      x = Sinerp<s16>(115, 228, mStateTimer.get());
      time_y = Sinerp<s16>(100, 5, mStateTimer.get());

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = (time_y + 29);
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
  }

  mSprite[SPR_TIME].setPosition({ (s16)x, time_y });
  mSprite[SPR_MIN].setPosition({ (s16)(x + 13), digit_y[0] });
  mSprite[SPR_COLON].setPosition({ (s16)(x + 28), digit_y[1] });
  mSprite[SPR_SEC_0].setPosition({ (s16)(x + 44), digit_y[2] });
  mSprite[SPR_SEC_1].setPosition({ (s16)(x + 64), digit_y[3] });

  t = clock->get(&min, &sec);

  if (mFlashTime > 0.0F) {
    if (TMath<float>::mod(mFlashTime, 0.4F) >= 0.2F) {
      setOffSprite(SPR_MIN);
      setOffSprite(SPR_COLON);
      setOffSprite(SPR_SEC_0);
      setOffSprite(SPR_SEC_1);
    } else {
      setOnSprite(SPR_MIN);
      setOnSprite(SPR_COLON);
      setOnSprite(SPR_SEC_0);
      setOnSprite(SPR_SEC_1);
    }

    mFlashTime -= kInterval;

    if (mFlashTime < 0.0F) {
      mFlashTime = 0.0F;
    }

    mSprite[SPR_MIN].load(
      THud::getDigitSprite(mFlashMin)
    );

    mSprite[SPR_SEC_0].load(
      THud::getDigitSprite(0)
    );

    mSprite[SPR_SEC_1].load(
      THud::getDigitSprite(0)
    );
  } else {
    u32 digits[2];

    setOnSprite(SPR_MIN);
    setOnSprite(SPR_SEC_0);
    setOnSprite(SPR_SEC_1);

    if (TMath<float>::mod(t, 1.0F) >= 0.5F) {
      setOffSprite(SPR_COLON);
    } else {
      setOnSprite(SPR_COLON);
    }

    THud::splitDigits(sec, digits, 2);

    mSprite[SPR_MIN].load(
      THud::getDigitSprite(min)
    );

    mSprite[SPR_SEC_0].load(
      THud::getDigitSprite(digits[0])
    );

    mSprite[SPR_SEC_1].load(
      THud::getDigitSprite(digits[1])
    );
  }
}

// -------------------------------------------------------------------------- //

void THudTime::draw() {
  if (mState == ST_HIDE) {
    return;
  }

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    if (mSpriteMask & (1U << i)) {
      continue;
    }

    mSprite[i].draw();
  }
}

// -------------------------------------------------------------------------- //

void THudCountDown::hide() {
  mState = ST_HIDE;
}

// -------------------------------------------------------------------------- //

void THudCountDown::show() {
  mState = ST_READY_IN;
  mStateTimer.set(1.0F);

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }
}

// -------------------------------------------------------------------------- //

void THudCountDown::timeup() {
  mSprite[SPR_HEADER].load(hud_timeup_sprite);
  setOffSprite(SPR_HEADER);

  mState = ST_TIMEUP_IN;
  mStateTimer.set(0.3F);
}

// -------------------------------------------------------------------------- //

void THudCountDown::init() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_FASTCOPY);
  }
}

// -------------------------------------------------------------------------- //

void THudCountDown::update() {
  s16 header_x, header_y = 40;
  s16 digit_x = 120;
  s16 digit_y = 92;

  switch (mState) {
    case ST_READY_IN: {
      setOnSprite(SPR_HEADER);
      setOffSprite(SPR_DIGIT);
      mSprite[SPR_HEADER].load(hud_ready_sprite);

      header_x = Lagrange<s16>(
        -320, 190, 55, mStateTimer.get()
      );

      if (mStateTimer.update()) {
        mState = ST_READY;
        mStateTimer.set(0.4F);
      }

      break;
    }
    case ST_READY: {
      setOffSprite(SPR_DIGIT);
      header_x = 55;

      if (mStateTimer.update()) {
        mSprite[SPR_DIGIT].load(hud_count3_sprite);

        mState = ST_READY_3;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_3: {
      setOnSprite(SPR_DIGIT);
      mSprite[SPR_DIGIT].load(hud_count3_sprite);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count3TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count3TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        mState = ST_READY_2;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_2: {
      setOnSprite(SPR_DIGIT);
      mSprite[SPR_DIGIT].load(hud_count2_sprite);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count2TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count2TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        mState = ST_READY_1;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_1: {
      setOnSprite(SPR_DIGIT);
      mSprite[SPR_DIGIT].load(hud_count1_sprite);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count1TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count1TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        mState = ST_FLY;
        mStateTimer.set(0.4F);
      }

      break;
    }
    case ST_FLY: {
      setOffSprite(SPR_DIGIT);
      mSprite[SPR_HEADER].load(hud_fly_sprite);
      header_x = 100;

      float t = mStateTimer.get(0.0F, 0.3F);
      header_x += (s16)((float)hud_flyTRUEIMAGEW * (1.0 - t) * 0.5F);
      header_y += (s16)((float)hud_flyTRUEIMAGEH * (1.0 - t) * 0.5F);
      mSprite[SPR_HEADER].setScale({ t, t });

      if (mStateTimer.update()) {
        mState = ST_FLY_OUT;
        mStateTimer.set(1.0F);
      }

      break;
    }
    case ST_FLY_OUT: {
      setOffSprite(SPR_DIGIT);

      header_x = Lagrange<s16>(
        100, -100, 500, mStateTimer.get()
      );

      if (mStateTimer.update()) {
        mState = ST_HIDE;
      }

      break;
    }
    case ST_TIMEUP_IN: {
      setOnSprite(SPR_HEADER);
      setOffSprite(SPR_DIGIT);
      header_x = 75;
      header_y = 90;

      float t = mStateTimer.get();
      header_x += (s16)((float)hud_timeupTRUEIMAGEW * (1.0 - t) * 0.5F);
      header_y += (s16)((float)hud_timeupTRUEIMAGEH * (1.0 - t) * 0.5F);
      mSprite[SPR_HEADER].setScale({ t, t });

      if (mStateTimer.update()) {
        mState = ST_TIMEUP_WAIT;
        mStateTimer.set(1.0F);
      }

      break;
    }
    case ST_TIMEUP_WAIT: {
      header_x = 75;
      header_y = 90;
      mSprite[SPR_HEADER].setScale({ 1.0F, 1.0F });

      if (mStateTimer.update()) {
        mState = ST_TIMEUP_OUT;
        mStateTimer.set(1.0F);
      }

      break;
    }
    case ST_TIMEUP_OUT: {
      header_y = 90;

      header_x = Lagrange<s16>(
        75, -120, 500, mStateTimer.get()
      );

      if (mStateTimer.update()) {
        mState = ST_HIDE;
      }

      break;
    }
  }

  mSprite[SPR_HEADER].setPosition({ header_x, header_y });
  mSprite[SPR_DIGIT].setPosition({ digit_x, digit_y });
}

// -------------------------------------------------------------------------- //

void THudCountDown::draw() {
  if (mState == ST_HIDE) {
    return;
  }

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    if (mSpriteMask & (1U << i)) {
      continue;
    }

    mSprite[i].draw();
  }
}

// -------------------------------------------------------------------------- //

void THud::init() {
  mCountDown.init();
  mScore.init();
  mTime.init();
}

// -------------------------------------------------------------------------- //

void THud::update() {
  mCountDown.update();
  mScore.update();
  mTime.update(&mClock);

  switch (mState) {
    case ST_COUNTDOWN: {
      if (mStateTimer.update()) {
        mClock.start((float)(mTimeLimit * 60));
        mTime.show(mTimeLimit);

        mState = ST_TIME_FLASH;
        mStateTimer.set(3.5F);
      }

      break;
    }
    case ST_TIME_FLASH: {
      if (mStateTimer.update()) {
        if (mScoreDown) {
          mScore.raise();
        }

        mTime.raise();
        mState = ST_SHOW;
      }

      break;
    }
    case ST_SCORE: {
      if (mStateTimer.update()) {
        mScore.raise();
        mTime.raise();
        mState = ST_SHOW;
      }

      break;
    }
    case ST_TIME_UP: {
      if (mStateTimer.update()) {
        if (mScoreDown) {
          mScore.lower();
        } else {
          mScoreDown = true;
          mScore.show();
        }

        mTime.lower();
      }

      break;
    }
  }

  if (mState != ST_HIDE && mState != ST_COUNTDOWN) {
    float t;
    u32 before, after;

    mClock.get(&before);
    mClock.update();
    t = mClock.get(&after);

    if (t == 0.0F && mState != ST_TIME_UP) {
      mCountDown.timeup();

      mState = ST_TIME_UP;
      mStateTimer.set(1.0F);
    }

    if (mState == ST_SHOW && after < before) {
      mTime.flash(before);
      mScore.lower();
      mTime.lower();

      mState = ST_TIME_FLASH;
      mStateTimer.set(4.5F);
    }
  }
}

// -------------------------------------------------------------------------- //

void THud::draw() {
  mScore.draw();
  mTime.draw();
  mCountDown.draw();
}

// -------------------------------------------------------------------------- //

u32 THud::getScore() const {
  return mScore.getScore();
}

// -------------------------------------------------------------------------- //

void THud::addScore(u32 pts) {
  u32 score = mScore.getScore();

  if (pts > MAX_SCORE - score) {
    pts = (MAX_SCORE - score);
  }

  if (pts == 0) {
    return;
  }

  if (!mScoreDown && mScore.getScore() == 0) {
    mScoreDown = true;
    mScore.show();

    if (mState == ST_SHOW) {
      mTime.lower();
    }

    mState = ST_SCORE;
    mStateTimer.set(2.5F);
  }

  mScore.setScore(score + pts);
}

// -------------------------------------------------------------------------- //

void THud::subScore(u32 pts) {
  u32 score = mScore.getScore();

  if (pts > score) {
    pts = score;
  }

  if (pts == 0) {
    return;
  }

  mScore.setScore(score - pts);
}

// -------------------------------------------------------------------------- //

void THud::startCountDown(u32 minutes) {
  mTimeLimit = minutes;
  mCountDown.show();
  mScore.hide();
  mTime.hide();

  mState = ST_COUNTDOWN;
  mStateTimer.set(3.8F);
}

// -------------------------------------------------------------------------- //

bool THud::isCountedDown() const {
  switch (mState) {
    case ST_SHOW:
    case ST_TIME_UP:
    case ST_TIME_FLASH: {
      return true;
    }
  }

  return false;
}

// -------------------------------------------------------------------------- //

bool THud::isTimeUp() const {
  if (!isCountedDown()) {
    return false;
  }

  return (mClock.get() == 0.0F);
}

// -------------------------------------------------------------------------- //

void THud::splitDigits(
  u32 value, u32 digits[], u32 count
) {
  for (u32 i = 0; i < count; ++i) {
    digits[count - i - 1] = (value % 10);
    value /= 10;
  }
}

// -------------------------------------------------------------------------- //

Sprite const &
THud::getDigitSprite(u32 digit) {
  static Sprite const * SPRITES[10] = {
    &hud_digit0_sprite, &hud_digit1_sprite,
    &hud_digit2_sprite, &hud_digit3_sprite,
    &hud_digit4_sprite, &hud_digit5_sprite,
    &hud_digit6_sprite, &hud_digit7_sprite,
    &hud_digit8_sprite, &hud_digit9_sprite,
  };

  return *SPRITES[digit % 10];
}

// -------------------------------------------------------------------------- //
