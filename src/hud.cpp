
#include <nusys.h>

#include "audio.hpp"
#include "hud.hpp"
#include "menu.hpp"
#include "pad.hpp"
#include "rank.hpp"
#include "segment.h"
#include "sprite.hpp"
#include "util.hpp"

#include "../models/ovl/sprites/sp_countdown.h"
#include "../models/ovl/sprites/sp_hud.h"
#include "../models/ovl/sprites/sp_ranka.h"
#include "../models/ovl/sprites/sp_rankb.h"
#include "../models/ovl/sprites/sp_rankc.h"
#include "../models/ovl/sprites/sp_rankd.h"
#include "../models/ovl/sprites/sp_rankf.h"
#include "../models/ovl/sprites/sp_result.h"
#include "../models/static/sprites/black_sprite.h"

// -------------------------------------------------------------------------- //

#define MAX_SCORE 99999

// -------------------------------------------------------------------------- //

THud * gHud { nullptr };

THudResults::TRankInfo
THudResults::sRankInfo[NUM_RANKS];

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
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
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
        -95, 16, mStateTimer.get(0.0F, 0.6F)
      );

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        float a = (0.0F + 0.08F * (float)i);
        float b = (a + 0.5F);

        digit_y[i] = Lagrange<s16>(
          -25, 81, 45, mStateTimer.get(a, b)
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
        -25, 16, mStateTimer.get(0.0F, 0.75F)
      );

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        float a = (0.0F + 0.05F * (float)i);
        float b = (a + 0.6F);

        digit_y[i] = Lagrange<s16>(
          5, 81, 45, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_RAISE: {
      setOnSprite(SPR_SCORE);
      score_y = Lerp<s16>(16, -25, mStateTimer.get());

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = Lerp<s16>(46, 16, mStateTimer.get());
      }

      if (mStateTimer.update()) {
        mState = ST_UP;
      }

      break;
    }
    case ST_DOWN: {
      setOnSprite(SPR_SCORE);
      score_y = 16;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = 45;
      }

      break;
    }
    case ST_UP: {
      setOffSprite(SPR_SCORE);
      score_y = 0;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        digit_y[i] = 16;
      }

      break;
    }
  }

  if (mState != ST_HIDE) {
    for (u32 i = SPR_SCORE_0; i <= SPR_METRIC; ++i) {
      setOnSprite(i);
    }
  }

  mSprite[SPR_SCORE].setPosition({ (s16)16, score_y });

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    s16 x = (s16)(16 + 20 * i);

    if (i >= NUM_INT_PLACES) {
      x += 9;
    }

    mSprite[SPR_SCORE_0 + i].setPosition(
      { x, digit_y[i] }
    );
  }

  mSprite[SPR_DOT].setPosition({
    (s16)(16 + 20 * NUM_INT_PLACES),
    (s16)(13 + (digit_y[NUM_INT_PLACES - 1] + digit_y[NUM_INT_PLACES]) / 2),
  });

  mSprite[SPR_METRIC].setPosition({
    (s16)(25 + 20 * NUM_SCORE_DIGITS),
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

void THudTime::scram() {
  mState = ST_SCRAM;
  mStateTimer.set(1.0F);
}

// -------------------------------------------------------------------------- //

void THudTime::init() {
  mSprite[SPR_TIME].load(hud_time_sprite);
  mSprite[SPR_COLON].load(hud_colon_sprite);
  mSprite[SPR_MIN].load(THud::getDigitSprite(0));
  mSprite[SPR_SEC_0].load(THud::getDigitSprite(0));
  mSprite[SPR_SEC_1].load(THud::getDigitSprite(0));

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
  }
}

// -------------------------------------------------------------------------- //

void THudTime::update(
  TTimer const * clock
) {
  s16 digit_y[4]; // [0] min, [1] colon, [2-3] sec 0-1
  s16 time_y, x = 220;
  u32 min, sec;
  float t;

  switch (mState) {
    case ST_LOWER: {
      setOnSprite(SPR_TIME);
      time_y = Lerp<s16>(-25, 16, mStateTimer.get(0.0F, 0.75F));

      for (u32 i = 0; i < 4; ++i) {
        float a = (0.0F + 0.05F * (float)i);
        float b = (a + 0.6F);

        digit_y[i] = Lagrange<s16>(
          5, 70, 45, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_RAISE: {
      setOnSprite(SPR_TIME);
      time_y = Lerp<s16>(16, -25, mStateTimer.get());

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = Lerp<s16>(45, 16, mStateTimer.get());
      }

      if (mStateTimer.update()) {
        mState = ST_UP;
      }

      break;
    }
    case ST_DOWN: {
      setOnSprite(SPR_TIME);
      time_y = 16;

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = 45;
      }

      break;
    }
    case ST_UP: {
      setOffSprite(SPR_TIME);
      time_y = 0;

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = 16;
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
      x = Sinerp<s16>(115, 220, mStateTimer.get());
      time_y = Sinerp<s16>(100, 16, mStateTimer.get());

      for (u32 i = 0; i < 4; ++i) {
        digit_y[i] = (time_y + 29);
      }

      if (mStateTimer.update()) {
        mState = ST_DOWN;
      }

      break;
    }
    case ST_SCRAM: {
      setOffSprite(SPR_TIME);
      time_y = 0;

      for (u32 i = 0; i < 4; ++i) {
        float a = (0.0F + 0.1F * (float)i);
        float b = (a + 0.5F);

        digit_y[i] = Lagrange<s16>(
          16, 66, -90, mStateTimer.get(a, b)
        );
      }

      if (mStateTimer.update()) {
        mState = ST_HIDE;
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

void THudExit::hide() {
  mState = ST_HIDE;
}

// -------------------------------------------------------------------------- //

void THudExit::show() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }

  mState = ST_SHOW;
  mStateTimer = 0.0F;
}

// -------------------------------------------------------------------------- //

void THudExit::init() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
    setOffSprite(i);
  }

  mSprite[SPR_BUTTON].load(hud_start_sprite);
  mSprite[SPR_TEXT].load(hud_exit_sprite);
  mSprite[SPR_TEXT].setPosition({ 47, 204 });
}

// -------------------------------------------------------------------------- //

void THudExit::update() {
  switch (mState) {
    case ST_SHOW: {
      setOnSprite(SPR_BUTTON);
      s16 x, y, w, h;
      float t;

      w = (s16)(hud_startTRUEIMAGEW / 2);
      h = (s16)(hud_startTRUEIMAGEH / 2);

      t = (0.6F + 0.1F * TSine::ssin(
        TSine::fromDeg((mStateTimer + 0.5F) * 360.0F)
      ));

      x = (28 - (s16)((float)w * t));
      y = (211 - (s16)((float)h * t));
      mSprite[SPR_BUTTON].setPosition({ x, y });
      mSprite[SPR_BUTTON].setScale({ t, t });

      if (TMath<float>::mod(mStateTimer, 0.5F) >= 0.25F) {
        setOnSprite(SPR_TEXT);
      } else {
        setOffSprite(SPR_TEXT);
      }

      mStateTimer += kInterval;
      break;
    }
  }
}

// -------------------------------------------------------------------------- //

void THudExit::draw() {
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

void THudCountDown::show() {
  mState = ST_FLASH_OUT;
  mStateTimer.set(0.5F);
}

// -------------------------------------------------------------------------- //

void THudCountDown::timeup() {
  TUtil::toMemory(
    _countdown_ovlSegmentStart,
    _result_ovlSegmentRomStart, (s32)(
      _result_ovlSegmentRomEnd -
      _result_ovlSegmentRomStart
    )
  );

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }

  mSprite[SPR_HEADER].load(hud_timeup_sprite);

  mState = ST_TIMEUP_IN;
  mStateTimer.set(0.3F);
}

// -------------------------------------------------------------------------- //

void THudCountDown::fade(float secs) {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }

  mState = ST_FADE_IN;
  mStateTimer.set(secs);
}

// -------------------------------------------------------------------------- //

void THudCountDown::init() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
    setOffSprite(i);
  }

  TUtil::toMemory(
    _countdown_ovlSegmentStart,
    _countdown_ovlSegmentRomStart, (s32)(
      _countdown_ovlSegmentRomEnd -
      _countdown_ovlSegmentRomStart
    )
  );

  setOnSprite(SPR_FLASH);
  mSprite[SPR_FLASH].load(black_sprite);
  mSprite[SPR_FLASH].setScale({ 10.0F, 7.5F });
  mSprite[SPR_HEADER].load(hud_ready_sprite);
}

// -------------------------------------------------------------------------- //

void THudCountDown::update() {
  s16 header_x, header_y = 40;
  s16 digit_x = 120;
  s16 digit_y = 92;

  switch (mState) {
    case ST_FLASH_OUT: {
      u8 a;

      a = Lerp<u8>(255, 0, mStateTimer.get());
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        TAudio::playSound(SFX_WOOSH);
        setOffSprite(SPR_FLASH);

        mState = ST_READY_IN;
        mStateTimer.set(0.7F);
      }

      break;
    }
    case ST_READY_IN: {
      setOnSprite(SPR_HEADER);
      setOffSprite(SPR_DIGIT);

      header_x = Lagrange<s16>(
        -320, 190, 55, mStateTimer.get()
      );

      if (mStateTimer.update()) {
        mState = ST_READY;
        mStateTimer.set(0.25F);
      }

      break;
    }
    case ST_READY: {
      setOffSprite(SPR_DIGIT);
      header_x = 55;

      if (mStateTimer.update()) {
        mSprite[SPR_DIGIT].load(hud_count3_sprite);
        TAudio::playSound(SFX_COUNTDOWN_NUMBER);

        mState = ST_READY_3;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_3: {
      setOnSprite(SPR_DIGIT);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count3TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count3TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        mSprite[SPR_DIGIT].load(hud_count2_sprite);
        TAudio::playSound(SFX_COUNTDOWN_NUMBER);

        mState = ST_READY_2;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_2: {
      setOnSprite(SPR_DIGIT);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count2TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count2TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        mSprite[SPR_DIGIT].load(hud_count1_sprite);
        TAudio::playSound(SFX_COUNTDOWN_NUMBER);

        mState = ST_READY_1;
        mStateTimer.set(0.66F);
      }

      break;
    }
    case ST_READY_1: {
      setOnSprite(SPR_DIGIT);
      header_x = 55;

      float t = mStateTimer.get(0.0F, 0.2F);
      float s = (1.0F + TSine::ssin(TSine::fromDeg(t * 180.0F)) * 0.35F);
      digit_x -= (s16)((float)hud_count1TRUEIMAGEW * (s - 1.0F) * 0.5F);
      digit_y -= (s16)((float)hud_count1TRUEIMAGEH * (s - 1.0F) * 0.5F);
      mSprite[SPR_DIGIT].setScale({ s, s });

      if (mStateTimer.update()) {
        setOffSprite(SPR_HEADER);
        mSprite[SPR_HEADER].load(hud_fly_sprite);
        TAudio::playSound(SFX_COUNTDOWN_GO);

        mState = ST_FLY;
        mStateTimer.set(0.35F);
      }

      break;
    }
    case ST_FLY: {
      setOnSprite(SPR_HEADER);
      setOffSprite(SPR_DIGIT);
      header_x = 100;

      float t = mStateTimer.get(0.0F, 0.3F);
      header_x += (s16)((float)hud_flyTRUEIMAGEW * (1.0 - t) * 0.5F);
      header_y += (s16)((float)hud_flyTRUEIMAGEH * (1.0 - t) * 0.5F);
      mSprite[SPR_HEADER].setScale({ t, t });

      if (mStateTimer.update()) {
        TAudio::playSound(SFX_WOOSH);

        mState = ST_FLY_OUT;
        mStateTimer.set(0.75F);
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
        mStateTimer.set(0.75F);
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
    case ST_FADE_IN: {
      setOnSprite(SPR_FLASH);

      u8 a;

      a = Lerp<u8>(0, 255, mStateTimer.get());
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        mSprite[SPR_FLASH].setColor({ 255, 255, 255, 255 });
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

void THudResults::hide() {
  mState = ST_HIDE;
  mResultState = EResultState::IN;
}

// -------------------------------------------------------------------------- //

void THudResults::show() {
  mResultState = EResultState::IN;
  mState = ST_RESULTS_IN;
  mStateTimer.set(0.85F);

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    setOffSprite(i);
  }

  mSprite[SPR_RESULTS].load(result_text_sprite);
  mSprite[SPR_BIRD].load(result_bird_sprite);
  mNumTally = 0;

  for (u32 i = 0; i < NUM_DISP_TALLY; ++i) {
    auto y = (s16)(80 + 20 * i);

    mSprite[SPR_TALLY0_TITLE + 3 * i].load(result_balloon_sprite);
    mSprite[SPR_TALLY0_TITLE + 3 * i].setPosition({ (s16)42, y });

    mSprite[SPR_TALLY0_DIGIT0 + 3 * i].load(result_digit0_sprite);
    mSprite[SPR_TALLY0_DIGIT0 + 3 * i].setPosition({ (s16)190, y });

    mSprite[SPR_TALLY0_DIGIT1 + 3 * i].load(result_digit0_sprite);
    mSprite[SPR_TALLY0_DIGIT1 + 3 * i].setPosition({ (s16)201, y });
  }

  TAudio::playSound(SFX_WOOSH);
}

// -------------------------------------------------------------------------- //

void THudResults::init(u32 rank) {
  mRank = rank;

  sRankInfo[RANK_A] = {
    &result_birda_sprite, { 85, -78 },
    &result_ranka_sprite, { 265, 11 },
    { result_rankaTRUEIMAGEW, result_rankaTRUEIMAGEH },
    &result_stara_sprite, { 245, -13 },
    { result_staraTRUEIMAGEW, result_staraTRUEIMAGEH },
    _ranka_ovlSegmentRomStart,
    (s32)(_ranka_ovlSegmentRomEnd - _ranka_ovlSegmentRomStart),
  };

  sRankInfo[RANK_B] = {
    &result_birdb_sprite, { 104, -85 },
    &result_rankb_sprite, { 267, 11 },
    { result_rankbTRUEIMAGEW, result_rankbTRUEIMAGEH },
    &result_starb_sprite, { 244, -10 },
    { result_starbTRUEIMAGEW, result_starbTRUEIMAGEH },
    _rankb_ovlSegmentRomStart,
    (s32)(_rankb_ovlSegmentRomEnd - _rankb_ovlSegmentRomStart),
  };

  sRankInfo[RANK_C] = {
    &result_birdc_sprite, { 86, -74 },
    &result_rankc_sprite, { 267, 11 },
    { result_rankcTRUEIMAGEW, result_rankcTRUEIMAGEH },
    &result_starc_sprite, { 244, -6 },
    { result_starcTRUEIMAGEW, result_starcTRUEIMAGEH },
    _rankc_ovlSegmentRomStart,
    (s32)(_rankc_ovlSegmentRomEnd - _rankc_ovlSegmentRomStart),
  };

  sRankInfo[RANK_D] = {
    &result_birdd_sprite, { 89, -55 },
    &result_rankd_sprite, { 267, 11 },
    { result_rankdTRUEIMAGEW, result_rankdTRUEIMAGEH },
    &result_stard_sprite, { 254, 5 },
    { result_stardTRUEIMAGEW, result_stardTRUEIMAGEH },
    _rankd_ovlSegmentRomStart,
    (s32)(_rankd_ovlSegmentRomEnd - _rankd_ovlSegmentRomStart),
  };

  sRankInfo[RANK_F] = {
    &result_birdf_sprite, { 72, -24 },
    &result_rankf_sprite, { 271, 11 },
    { result_rankfTRUEIMAGEW, result_rankfTRUEIMAGEH },
    nullptr, { 0, 0 }, { 0, 0 },
    _rankf_ovlSegmentRomStart,
    (s32)(_rankf_ovlSegmentRomEnd - _rankf_ovlSegmentRomStart),
  };

  TUtil::toMemory(
    _ranka_ovlSegmentStart,
    sRankInfo[rank].rom_src,
    sRankInfo[rank].rom_sz
  );

  mSprite[SPR_RESULTS].load(result_text_sprite);
  mSprite[SPR_BIRD].load(result_bird_sprite);
  mSprite[SPR_RANK].load(result_rank_sprite);
  mSprite[SPR_RANK_0].load(*sRankInfo[rank].rank_spr);

  if (sRankInfo[rank].star_spr != nullptr) {
    mSprite[SPR_STAR].load(*sRankInfo[rank].star_spr);
  }

  mSprite[SPR_TALLY_UP].load(result_up_sprite);
  mSprite[SPR_TALLY_UP].setPosition({ 18, 77 });
  mSprite[SPR_TALLY_DOWN].load(result_down_sprite);
  mSprite[SPR_TALLY_DOWN].setPosition({ 18, 157 });

  mMaxNumTally = 0;
  mNumTally = 0;
  mTallyOfs = 0;

  for (u8 i = 0; i < NUM_TALLY; ++i) {
    if (gRank.get(i) == 0) {
      continue;
    }

    mTally[mMaxNumTally++] = i;
  }

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
    setOffSprite(i);
  }
}

// -------------------------------------------------------------------------- //

void THudResults::update(TPad const * pad) {
  s16 result_x = 134, rank_x = 0;
  TVec2S bird_ofs { 92, -74 };
  TVec2S rank0_pos { 0, 0 };
  TVec2S star_pos { 0, 0 };

  if (mState != ST_HIDE) {
    u32 count = TMath<u32>::min(NUM_DISP_TALLY, mNumTally);
    u32 tally, value;
    u32 digits[2];

    for (u32 i = 0; i < count; ++i) {
      tally = mTally[mNumTally - (mTallyOfs + i) - 1];
      value = gRank.get(tally);

      THud::splitDigits(value, digits, 2);

      setOnSprite(SPR_TALLY0_TITLE + 3 * i);
      setOnSprite(SPR_TALLY0_DIGIT1 + 3 * i);

      mSprite[SPR_TALLY0_TITLE + 3 * i].load(
        getTallySprite(tally)
      );

      mSprite[SPR_TALLY0_DIGIT1 + 3 * i].load(
        getDigitSprite(digits[1])
      );

      if (digits[0] != 0) {
        setOnSprite(SPR_TALLY0_DIGIT0 + 3 * i);

        mSprite[SPR_TALLY0_DIGIT0 + 3 * i].load(
          getDigitSprite(digits[0])
        );
      } else {
        setOffSprite(SPR_TALLY0_DIGIT0 + 3 * i);
      }
    }
  }

  switch (mState) {
    case ST_RESULTS_IN: {
      setOnSprite(SPR_RESULTS);
      setOnSprite(SPR_BIRD);
      result_x = Sinerp<s16>(350, 134, mStateTimer.get());

      if (mStateTimer.update()) {
        mState = ST_RESULTS_WAIT;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_RESULTS_WAIT: {
      if (mStateTimer.update()) {
        TAudio::playSound(SFX_WOOSH);
        mState = ST_TALLY;
      }

      break;
    }
    case ST_TALLY: {
      s16 x, y;
      float t;

      x = Sinerp<s16>(-200, 42, mStateTimer.get(0.0F, 0.65F));
      y = mSprite[SPR_TALLY0_TITLE].getPosition().y();
      mSprite[SPR_TALLY0_TITLE].setPosition({ x, y });

      t = Lagrange<float>(0.0F, 3.0F, 1.0F, mStateTimer.get(0.0F, 0.65F));
      x = (s16)(190 + (float)result_digit0TRUEIMAGEW * (1.0F - t) * 0.5F);
      y = (s16)( 80 + (float)result_digit0TRUEIMAGEH * (1.0F - t) * 0.5F);

      mSprite[SPR_TALLY0_DIGIT0].setPosition({ x, y });
      mSprite[SPR_TALLY0_DIGIT1].setPosition({ (s16)(x + 11), y });
      mSprite[SPR_TALLY0_DIGIT0].setScale({ t, t });
      mSprite[SPR_TALLY0_DIGIT1].setScale({ t, t });

      for (u32 i = 1; i < NUM_DISP_TALLY; ++i) {
        auto y0 = (s16)(80 + 20 * (i - 1));
        auto y1 = (s16)(80 + 20 * i);
        y = Sinerp<s16>(y0, y1, mStateTimer.get(0.0F, 0.3F));

        mSprite[SPR_TALLY0_TITLE  + 3 * i].setPosition({ (s16)42,  y });
        mSprite[SPR_TALLY0_DIGIT0 + 3 * i].setPosition({ (s16)190, y });
        mSprite[SPR_TALLY0_DIGIT1 + 3 * i].setPosition({ (s16)201, y });
      }

      mStateTimer.update();

      if (mStateTimer.off()) {
        mSprite[SPR_TALLY0_DIGIT0].setPosition({ 190, 80 });
        mSprite[SPR_TALLY0_DIGIT1].setPosition({ 201, 80 });
        mSprite[SPR_TALLY0_DIGIT0].setScale({ 1.0F, 1.0F });
        mSprite[SPR_TALLY0_DIGIT1].setScale({ 1.0F, 1.0F });

        if (mNumTally == mMaxNumTally) {
          mState = ST_TALLY_WAIT;
          mStateTimer.set(0.1F);
        } else {
          ++mNumTally;
          TAudio::playSound(SFX_WOOSH);
          TAudio::playSound(SFX_POP);
          mStateTimer.set(0.5F);
        }
      }

      break;
    }
    case ST_TALLY_WAIT: {
      if (mStateTimer.update()) {
        TAudio::playSound(SFX_WOOSH);

        mState = ST_RANK_IN;
        mStateTimer.set(0.8F);
      }

      break;
    }
    case ST_RANK_IN: {
      setOnSprite(SPR_RANK);
      rank_x = Sinerp<s16>(480, 147, mStateTimer.get());

      if (mStateTimer.update()) {
        TAudio::playSound(SFX_STAMP);

        mState = ST_RANK_STAR;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_RANK_STAR: {
      if (sRankInfo[mRank].star_spr != nullptr) {
        setOnSprite(SPR_STAR);
      }

      setOnSprite(SPR_RANK_0);
      rank_x = 147;

      star_pos = sRankInfo[mRank].star_pos;
      rank0_pos = sRankInfo[mRank].rank_pos;

      float t0 = mStateTimer.get(0.0F, 0.5F);

      float t1 = Lagrange<float>(0.0F, 2.5F, 1.0F,
        mStateTimer.get(0.2F, 1.0F)
      );

      star_pos.x() += (s16)(
        (float)sRankInfo[mRank].star_sz.x() * (1.0F - t0) * 0.5F
      );

      star_pos.y() += (s16)(
        (float)sRankInfo[mRank].star_sz.y() * (1.0F - t0) * 0.5F
      );

      rank0_pos.x() += (s16)(
        (float)sRankInfo[mRank].rank_sz.x() * (1.0F - t1) * 0.5F
      );

      rank0_pos.y() += (s16)(
        (float)sRankInfo[mRank].rank_sz.y() * (1.0F - t1) * 0.5F
      );

      mSprite[SPR_STAR].setScale({ t0, t0 });
      mSprite[SPR_RANK_0].setScale({ t1, t1 });

      if (mStateTimer.update()) {
        mResultState = EResultState::WAIT;
        mState = ST_RANK_WAIT;
      }

      break;
    }
    case ST_RANK_WAIT: {
      mSprite[SPR_BIRD].load(*sRankInfo[mRank].bird_spr);
      bird_ofs = sRankInfo[mRank].bird_ofs;
      star_pos = sRankInfo[mRank].star_pos;
      rank0_pos = sRankInfo[mRank].rank_pos;
      rank_x = 147;

      mWaveTimer += kInterval;

      float t0 = (1.0F + TSine::ssin(TSine::fromDeg(
        mWaveTimer * 400.0F
      )) * 0.15F);

      float t1 = (1.0F + TSine::ssin(TSine::fromDeg(
        mWaveTimer * 400.0F + 90.0F
      )) * 0.15F);

      star_pos.x() += (s16)(
        (float)sRankInfo[mRank].star_sz.x() * (1.0F - t0) * 0.5F
      );

      star_pos.y() += (s16)(
        (float)sRankInfo[mRank].star_sz.y() * (1.0F - t0) * 0.5F
      );

      rank0_pos.x() += (s16)(
        (float)sRankInfo[mRank].rank_sz.x() * (1.0F - t1) * 0.5F
      );

      rank0_pos.y() += (s16)(
        (float)sRankInfo[mRank].rank_sz.y() * (1.0F - t1) * 0.5F
      );

      mSprite[SPR_STAR].setScale({ t0, t0 });
      mSprite[SPR_RANK_0].setScale({ t1, t1 });
      mStateTimer.update();

      if (pad->isPressed((EButton)(
        EButton::START | EButton::A | EButton::B
      ))) {
        mResultState = EResultState::OUT;
      }

      break;
    }
  }

  if (
    (mResultState == EResultState::WAIT) &&
    (mMaxNumTally > NUM_DISP_TALLY)
  ) {
    int dir = 0;

    if (isPressUp(pad)) {
      ++dir;
    }

    if (isPressDown(pad)) {
      --dir;
    }

    if (dir != 0) {
      bool move = false;

      if (mMenuDir != dir) {
        mMenuTimer = 0.0F;
        move = true;
      } else {
        mMenuTimer += kInterval;

        if (mMenuTimer >= 0.2F) {
          mMenuTimer -= 0.2F;
          move = true;
        }
      }

      if (move) {
        if (dir > 0 && mTallyOfs > 0) {
          --mTallyOfs;
        } else if (dir < 0 && mTallyOfs < (mMaxNumTally - NUM_DISP_TALLY)) {
          ++mTallyOfs;
        }
      }

      mMenuDir = dir;
    } else {
      mMenuTimer = 0.0F;
      mMenuDir = 0;
    }

    if (mTallyOfs == 0) {
      setOffSprite(SPR_TALLY_UP);
    } else {
      setOnSprite(SPR_TALLY_UP);
    }

    if (mTallyOfs == mMaxNumTally - NUM_DISP_TALLY) {
      setOffSprite(SPR_TALLY_DOWN);
    } else {
      setOnSprite(SPR_TALLY_DOWN);
    }
  }

  if (mState != ST_HIDE) {
    mSprite[SPR_RANK].setPosition({ rank_x, (s16)15 });
    mSprite[SPR_RANK_0].setPosition(rank0_pos);

    if (sRankInfo[mRank].star_spr != nullptr) {
      mSprite[SPR_STAR].setPosition(star_pos);
    }
  }

  mSprite[SPR_BIRD].setPosition({
    (s16)(result_x + bird_ofs.x()),
    (s16)(186 + bird_ofs.y())
  });

  mSprite[SPR_RESULTS].setPosition(
    { result_x, (s16)186 }
  );
}

// -------------------------------------------------------------------------- //

void THudResults::draw() {
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

bool THudResults::isPressUp(
  TPad const * pad
) const {
  if (pad->getAnalogY() > 20) {
    return true;
  }

  if (pad->isHeld((EButton)(EButton::UP | EButton::C_UP))) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

bool THudResults::isPressDown(
  TPad const * pad
) const {
  if (pad->getAnalogY() < -20) {
    return true;
  }

  if (pad->isHeld((EButton)(EButton::DOWN | EButton::C_DOWN))) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

Sprite const &
THudResults::getTallySprite(u32 tally) {
  static Sprite const * SPRITES[NUM_TALLY] = {
    &result_balloon_sprite,   // TALLY_BALLOONS
    &result_food_sprite,      // TALLY_FOOD
    &result_cards_sprite,     // TALLY_CARDS
    &result_sticks_sprite,    // TALLY_STICKS
    &result_tables_sprite,    // TALLY_TABLES
    &result_chairs_sprite,    // TALLY_CHAIRS
    &result_noodles_sprite,   // TALLY_NOODLES
    &result_jewelry_sprite,   // TALLY_JEWELRY
    &result_pots_sprite,      // TALLY_POTS
    &result_toasters_sprite,  // TALLY_TOASTERS
    &result_stones_sprite,    // TALLY_STONES
    &result_trash_sprite,     // TALLY_TRASH
    &result_mailboxes_sprite, // TALLY_MAILBOXES
    &result_lamps_sprite,     // TALLY_LAMPS
    &result_boards_sprite,    // TALLY_BOARDS
    &result_balls_sprite,     // TALLY_BALLS
    &result_goals_sprite,     // TALLY_GOALS
    &result_plants_sprite,    // TALLY_PLANTS
    &result_beehives_sprite,  // TALLY_BEEHIVES
    &result_chickens_sprite,  // TALLY_CHICKENS
    &result_cats_sprite,      // TALLY_CATS
    &result_fences_sprite,    // TALLY_FENCES
    &result_tires_sprite,     // TALLY_TIRES
    &result_vehicles_sprite,  // TALLY_VEHICLES
    &result_logos_sprite,     // TALLY_STORE_LOGOS
    &result_citizens_sprite   // TALLY_CITIZENS
  };

  return *SPRITES[tally % NUM_TALLY];
}

// -------------------------------------------------------------------------- //

Sprite const &
THudResults::getDigitSprite(u32 digit) {
  static Sprite const * SPRITES[10] = {
    &result_digit0_sprite, &result_digit1_sprite,
    &result_digit2_sprite, &result_digit3_sprite,
    &result_digit4_sprite, &result_digit5_sprite,
    &result_digit6_sprite, &result_digit7_sprite,
    &result_digit8_sprite, &result_digit9_sprite
  };

  return *SPRITES[digit % 10];
}

// -------------------------------------------------------------------------- //

THud::THud(TPad * pad) :
  mPad { pad }
{}

// -------------------------------------------------------------------------- //

void THud::init() {
  mCountDown.init();
  mScore.init();
  mTime.init();
  mExit.init();
}

// -------------------------------------------------------------------------- //

void THud::update() {
  mCountDown.update();
  mScore.update();
  mTime.update(&mClock);
  mExit.update();

  if (mResults != nullptr) {
    EResultState old = mResults->getState();
    mResults->update(mPad);
    EResultState state = mResults->getState();

    if (old != state) {
      switch (state) {
        case EResultState::WAIT: {
          mExit.show();
          break;
        }
        case EResultState::OUT: {
          mExit.hide();
          mCountDown.fade(1.0F);
          TAudio::fadeMusic(0.0F, 1.0F);
          TAudio::playSound(SFX_MENU_SELECT);

          mState = ST_EXIT;
          mStateTimer.set(1.0F);
          break;
        }
      }
    }
  }

  if (mState != ST_EXIT) {
    switch (mState) {
      case ST_COUNTDOWN: {
        if (mStateTimer.update()) {
          if (mTimeLimit != 0) {
            mClock.start((float)(mTimeLimit * 60));
            mTime.show(mTimeLimit);

            mState = ST_TIME_FLASH;
            mStateTimer.set(3.5F);
          } else {
            mExit.show();

            mState = ST_SHOW;
          }
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

          if (mTimeLimit != 0) {
            mTime.raise();
          }

          mState = ST_SHOW;
        }

        break;
      }
      case ST_TIME_UP: {
        if (mStateTimer.update()) {
          u32 rank;

          if (mScoreDown) {
            mScore.lower();
          } else {
            mScoreDown = true;
            mScore.show();
          }

          mTime.scram();
          mResults = new THudResults {};
          rank = TRank::calcRank(getScore());
          mResults->init(rank);

          if (rank == RANK_A) {
            TMenuScene::unlockFreedomMode();
          }

          mState = ST_RESULTS;
          mStateTimer.set(1.5F);
        }

        break;
      }
      case ST_RESULTS: {
        if (mStateTimer.update()) {
          mResults->show();
        }

        break;
      }
    }

    if (mState >= ST_SHOW) {
      if (mTimeLimit != 0) {
        float t;
        u32 before, after;

        mClock.get(&before);
        mClock.update();
        t = mClock.get(&after);

        if (t == 0.0F && !mTimeUp) {
          TAudio::playSound(SFX_TIMEOUT);
          TAudio::fadeMusic(0.5F, 1.0F);
          mCountDown.timeup();
          mTimeUp = true;

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
      } else if (mPad->isPressed(EButton::START)) {
        mExit.hide();
        mCountDown.fade(1.0F);
        TAudio::fadeMusic(0.0F, 1.0F);
        TAudio::playSound(SFX_MENU_SELECT);

        mState = ST_EXIT;
        mStateTimer.set(1.0F);
      }
    }
  } else {
    if (mStateTimer.update()) {
      mExitFlag = true;
    }
  }
}

// -------------------------------------------------------------------------- //

void THud::draw() {
  mScore.draw();
  mTime.draw();
  mExit.draw();

  if (mResults != nullptr) {
    mResults->draw();
  }

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

    if (mState == ST_SHOW && mTimeLimit != 0) {
      mTime.lower();
    }

    if (mState != ST_EXIT) {
      mState = ST_SCORE;
      mStateTimer.set(2.5F);
    }
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

void THud::startCountDown() {
  mTimeLimit = TMenuScene::getTimeLimit();
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

  if (mTimeLimit == 0) {
    return false;
  }

  return (mClock.get() == 0.0F);
}

// -------------------------------------------------------------------------- //

bool THud::isExit() const {
  return mExitFlag;
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
