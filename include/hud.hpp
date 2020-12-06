
#ifndef INCLUDE_HUD_HPP
#define INCLUDE_HUD_HPP

#include <nusys.h>

#include "score.hpp"
#include "sprite.hpp"
#include "util.hpp"

// -------------------------------------------------------------------------- //

class THud {

  public:

  THud() = default;
  ~THud() = default;

  void init();
  void update();
  void draw();

  u32 getScore() const;
  void addScore(u32 pts);
  void subScore(u32 pts);

  bool isTimeUp() const;
  void startClock(u32 minutes);

  private:

  enum {

    ST_DOWN,
    ST_UP,
    ST_LOWERING,
    ST_RAISING,

  };

  enum : u32 {

    SPR_SCORE,
    SPR_TIME,
    SPR_TIME_COLON,

    SPR_SCORE_0,
    SPR_SCORE_1,
    SPR_SCORE_2,
    SPR_SCORE_3,
    SPR_SCORE_4,
    SPR_SCORE_5,

    SPR_TIME_0,
    SPR_TIME_1,
    SPR_TIME_2,

    NUM_SPRITES,

    NUM_SCORE_DIGITS = 6,
    NUM_TIME_DIGITS = 3

  };

  int mState { ST_DOWN };
  float mTime { 0.0F };
  float mMaxTime { 0.0F };
  float mFlashTime { 0.0F };
  TSprite mSprite[NUM_SPRITES];
  u32 mSpriteMask { 0 };
  TTimer mClock;
  float mCurScore { 0.0F };
  u32 mFinScore { 0 };
  float mScoreTime { 0.0F };

  void updateScore();
  void updateTime();

  bool updateTimer();
  void startTimer(float);
  float getTimer() const;
  float getTimer(float, float) const;

  static void splitDigits(u32, u32[], u32);
  static Sprite const * getDigitSprite(u32);

};

// -------------------------------------------------------------------------- //

extern THud * gHud;

// -------------------------------------------------------------------------- //

#endif
