
#include <nusys.h>

#include "hud.hpp"
#include "sprite.hpp"
#include "util.hpp"

#include "../models/ovl/sprites/sp_hud.h"

// -------------------------------------------------------------------------- //

#define MAX_SCORE    999999
#define SCORE_SPEED    1000 // pts per sec

// -------------------------------------------------------------------------- //

THud * gHud { nullptr };

// -------------------------------------------------------------------------- //

template<typename T>
T Lerp(T p0, T p1, float mu) {
  return (T)((float)p0 * (1.0F - mu) + (float)p1 * mu);
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

void THud::init() {
  mSprite[SPR_SCORE].load(hud_score_sprite);
  mSprite[SPR_TIME].load(hud_time_sprite);
  mSprite[SPR_TIME_COLON].load(hud_colon_sprite);

  Sprite const & digit = *getDigitSprite(0);

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    mSprite[SPR_SCORE_0 + i].load(digit);
  }

  for (u32 i = 0; i < NUM_TIME_DIGITS; ++i) {
    mSprite[SPR_TIME_0 + i].load(digit);
  }

  mFlashTime = 3.0F;
  mState = ST_LOWERING;
  mClock.start(5 * 60); // 5 minutes
  startTimer(1.0F);
}

// -------------------------------------------------------------------------- //

void THud::update() {
  s32 x[NUM_SPRITES];
  s32 y[NUM_SPRITES];

  switch (mState) {
    case ST_DOWN: {
      mSpriteMask &= ~(1U << SPR_SCORE);
      mSpriteMask &= ~(1U << SPR_TIME);

      y[SPR_SCORE] = 5;
      y[SPR_TIME] = 5;
      y[SPR_TIME_COLON] = 34;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        y[SPR_SCORE_0 + i] = 34;
      }

      for (u32 i = 0; i < NUM_TIME_DIGITS; ++i) {
        y[SPR_TIME_0 + i] = 34;
      }

      if (updateTimer()) {
        startTimer(0.5F);
        mState = ST_RAISING;
      }

      break;
    }
    case ST_UP: {
      mSpriteMask |= (1U << SPR_SCORE);
      mSpriteMask |= (1U << SPR_TIME);

      y[SPR_TIME_COLON] = 5;

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        y[SPR_SCORE_0 + i] = 5;
      }

      for (u32 i = 0; i < NUM_TIME_DIGITS; ++i) {
        y[SPR_TIME_0 + i] = 5;
      }

      break;
    }
    case ST_LOWERING: {
      mSpriteMask &= ~(1U << SPR_SCORE);
      mSpriteMask &= ~(1U << SPR_TIME);

      y[SPR_SCORE] = Lerp<s32>(-40, 5, getTimer(0.0F, 0.75F));
      y[SPR_TIME] = Lerp<s32>(-40, 5, getTimer(0.0F, 0.75F));

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        float a = (0.0F + 0.05F * (float)i);
        float b = (a + 0.6F);

        y[SPR_SCORE_0 + i] = Lagrange<s32>(
          5, 70, 34, getTimer(a, b)
        );
      }

      y[SPR_TIME_0] = Lagrange<s32>(
        5, 70, 34, getTimer(0.00F, 0.60F)
      );

      y[SPR_TIME_COLON] = Lagrange<s32>(
        5, 70, 34, getTimer(0.05F, 0.65F)
      );

      y[SPR_TIME_1] = Lagrange<s32>(
        5, 70, 34, getTimer(0.10F, 0.70F)
      );

      y[SPR_TIME_2] = Lagrange<s32>(
        5, 70, 34, getTimer(0.15F, 0.75F)
      );

      if (updateTimer()) {
        startTimer(3.5F);
        mState = ST_DOWN;
      }

      break;
    }
    case ST_RAISING: {
      mSpriteMask &= ~(1U << SPR_SCORE);
      mSpriteMask &= ~(1U << SPR_TIME);

      y[SPR_SCORE] = Lerp<s32>(5, -25, getTimer());
      y[SPR_TIME] = Lerp<s32>(5, -25, getTimer());
      y[SPR_TIME_COLON] = Lerp<s32>(35, 5, getTimer());

      for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
        y[SPR_SCORE_0 + i] = Lerp<s32>(35, 5, getTimer());
      }

      for (u32 i = 0; i < NUM_TIME_DIGITS; ++i) {
        y[SPR_TIME_0 + i] = Lerp<s32>(35, 5, getTimer());
      }

      if (updateTimer()) {
        mState = ST_UP;
      }

      break;
    }
  }

  x[SPR_SCORE] = 9;
  x[SPR_TIME] = 228;

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    x[SPR_SCORE_0 + i] = (9 + 20 * i);
  }

  x[SPR_TIME_0] = 241;
  x[SPR_TIME_COLON] = 256;
  x[SPR_TIME_1] = 272;
  x[SPR_TIME_2] = 292;

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setPosition({ x[i], y[i] });
  }

  updateScore();
  updateTime();
}

// -------------------------------------------------------------------------- //

void THud::updateScore() {
  u32 digits[NUM_SCORE_DIGITS];

  if (mScoreTime > 0.0F) {
    mScoreTime -= kInterval;

    if (mScoreTime < 0.0F) {
      mScoreTime = 0.0F;
    }
  }

  if ((u32)mCurScore != mFinScore) {
    if (mScoreTime == 0.0F) {
      mScoreTime = 1.0F;
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

  if (mScoreTime != 0.0F) {
    TVec2S pos;
    s32 ofs;

    ofs = TMath<s32>::abs((s32)(8.0F *
      TSine::ssin(TSine::fromDeg(mScoreTime * 360 * 2))
    ));

    for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
      pos = mSprite[SPR_SCORE_0 + i].getPosition();
      pos.y() += ofs;
      mSprite[SPR_SCORE_0 + i].setPosition(pos);
    }
  }

  splitDigits((u32)mCurScore, digits, NUM_SCORE_DIGITS);

  for (u32 i = 0; i < NUM_SCORE_DIGITS; ++i) {
    mSprite[SPR_SCORE_0 + i].load(
      *getDigitSprite(digits[i])
    );
  }
}

// -------------------------------------------------------------------------- //

void THud::updateTime() {
  u32 digits[2];
  u32 old, min, sec;
  float t;

  mClock.get(&old);
  mClock.update();
  t = mClock.get(&min, &sec);

  if (mState == ST_UP && old > min) {
    mFlashTime = 3.0F;
    mState = ST_LOWERING;
    startTimer(1.0F);
  }

  if (mFlashTime > 0.0F) {
    if (TMath<float>::mod(mFlashTime, 0.4F) < 0.2F) {
      mSpriteMask |= (1U << SPR_TIME_COLON);
      mSpriteMask |= (1U << SPR_TIME_0);
      mSpriteMask |= (1U << SPR_TIME_1);
      mSpriteMask |= (1U << SPR_TIME_2);
    } else {
      mSpriteMask &= ~(1U << SPR_TIME_COLON);
      mSpriteMask &= ~(1U << SPR_TIME_0);
      mSpriteMask &= ~(1U << SPR_TIME_1);
      mSpriteMask &= ~(1U << SPR_TIME_2);
    }

    mFlashTime -= kInterval;

    if (mFlashTime < 0.0F) {
      mFlashTime = 0.0F;
    }

    mSprite[SPR_TIME_0].load(
      *getDigitSprite((min + 1) % 10)
    );

    mSprite[SPR_TIME_1].load(
      *getDigitSprite(0)
    );

    mSprite[SPR_TIME_2].load(
      *getDigitSprite(0)
    );
  } else {
    mSpriteMask &= ~(1U << SPR_TIME_0);
    mSpriteMask &= ~(1U << SPR_TIME_1);
    mSpriteMask &= ~(1U << SPR_TIME_2);

    if (TMath<float>::mod(t, 1.0F) < 0.5F) {
      mSpriteMask |= (1U << SPR_TIME_COLON);
    } else {
      mSpriteMask &= ~(1U << SPR_TIME_COLON);
    }

    splitDigits(sec, digits, 2);

    mSprite[SPR_TIME_0].load(
      *getDigitSprite(min % 10)
    );

    mSprite[SPR_TIME_1].load(
      *getDigitSprite(digits[0])
    );

    mSprite[SPR_TIME_2].load(
      *getDigitSprite(digits[1])
    );
  }
}

// -------------------------------------------------------------------------- //

void THud::draw() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    if (mSpriteMask & (1U << i)) {
      continue;
    }

    mSprite[i].draw();
  }
}

// -------------------------------------------------------------------------- //

u32 THud::getScore() const {
  return mFinScore;
}

// -------------------------------------------------------------------------- //

void THud::addScore(u32 pts) {
  if (pts > MAX_SCORE - mFinScore) {
    pts = (MAX_SCORE - mFinScore);
  }

  if (pts == 0) {
    return;
  }

  mFinScore += pts;
  mScoreTime = 1.0F;
}

// -------------------------------------------------------------------------- //

void THud::subScore(u32 pts) {
  if (pts > mFinScore) {
    pts = mFinScore;
  }

  if (pts == 0) {
    return;
  }

  mFinScore -= pts;
  mScoreTime = 1.0F;
}

// -------------------------------------------------------------------------- //

bool THud::isTimeUp() const {
  return (mClock.get() == 0.0F);
}

// -------------------------------------------------------------------------- //

void THud::startClock(u32 minutes) {
  mClock.start((float)(minutes * 60));
}

// -------------------------------------------------------------------------- //

bool THud::updateTimer() {
  if (mTime >= mMaxTime) {
    return true;
  }

  mTime += kInterval;

  if (mTime >= mMaxTime) {
    mTime = mMaxTime;
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

void THud::startTimer(float t) {
  mTime = 0.0F;
  mMaxTime = t;
}

// -------------------------------------------------------------------------- //

float THud::getTimer() const {
  if (mMaxTime == 0.0F) {
    return 1.0F;
  }

  return (mTime / mMaxTime);
}

// -------------------------------------------------------------------------- //

float THud::getTimer(float a, float b) const {
  if (a >= b) {
    return 0.0F;
  }

  float t = getTimer();

  if (t < a) {
    return 0.0F;
  }

  if (t > b) {
    return 1.0F;
  }

  return ((t - a) / (b - a));
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

Sprite const *
THud::getDigitSprite(u32 digit) {
  if (digit >= 10) {
    return nullptr;
  }

  static Sprite const * SPRITES[10] = {
    &hud_digit0_sprite, &hud_digit1_sprite,
    &hud_digit2_sprite, &hud_digit3_sprite,
    &hud_digit4_sprite, &hud_digit5_sprite,
    &hud_digit6_sprite, &hud_digit7_sprite,
    &hud_digit8_sprite, &hud_digit9_sprite,
  };

  return SPRITES[digit];
}

// -------------------------------------------------------------------------- //
