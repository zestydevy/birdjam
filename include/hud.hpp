
#ifndef INCLUDE_HUD_HPP
#define INCLUDE_HUD_HPP

#include <nusys.h>

#include "rank.hpp"
#include "score.hpp"
#include "sprite.hpp"
#include "util.hpp"

// -------------------------------------------------------------------------- //

class THudAlarm {

  public:

  THudAlarm() = default;
  ~THudAlarm() = default;

  float get() const;
  float get(float min, float max) const;

  void set(float);
  bool update();
  bool off() const;

  private:

  float mTime { 0.0F };
  float mAlarm { 0.0F };

};

// -------------------------------------------------------------------------- //

class THudScore {

  public:

  THudScore() = default;
  ~THudScore() = default;

  bool isLower() const {
    switch (mState) {
      case ST_DOWN:
      case ST_LOWER:
      case ST_SHOW: {
        return true;
      }
    }

    return false;
  }

  void hide();
  void show();
  void lower();
  void raise();

  u32 getScore() const;
  void setScore(u32);

  void init();
  void update();
  void draw();

  private:

  enum {

    ST_HIDE,
    ST_SHOW,
    ST_UP,
    ST_DOWN,
    ST_LOWER,
    ST_RAISE

  };

  enum : u32 {

    SPR_SCORE,

    // these need to be contiguous, with metric last
    SPR_SCORE_0,
    SPR_SCORE_1,
    SPR_SCORE_2,
    SPR_SCORE_3,
    SPR_SCORE_4,
    SPR_DOT,
    SPR_METRIC,

    NUM_SPRITES,

    NUM_SCORE_DIGITS = 5,
    NUM_FRAC_PLACES = 2,
    NUM_INT_PLACES = (NUM_SCORE_DIGITS - NUM_FRAC_PLACES),

    SCORE_SPEED = 1000 // pts per sec

  };

  int mState { ST_HIDE };
  THudAlarm mStateTimer;
  float mCurScore { 0.0F };
  u32 mFinScore { 0 };
  float mBounceTime { 0.0F };
  TSprite mSprite[NUM_SPRITES];
  u32 mSpriteMask { 0 };

  void setOffSprite(u32 i) { mSpriteMask |= (1U << i); }
  void setOnSprite(u32 i) { mSpriteMask &= ~(1U << i); }

};

// -------------------------------------------------------------------------- //

class THudTime {

  public:

  THudTime() = default;
  ~THudTime() = default;

  void hide();
  void show(u32 min);
  void lower();
  void raise();
  void flash(u32 min);
  void scram();

  void init();
  void update(TTimer const *);
  void draw();

  private:

  enum {

    ST_HIDE,
    ST_SHOW_WAIT,
    ST_SHOW_SLIDE,
    ST_UP,
    ST_DOWN,
    ST_LOWER,
    ST_RAISE,
    ST_SCRAM

  };

  enum : u32 {

    SPR_TIME,
    SPR_MIN,
    SPR_COLON,
    SPR_SEC_0,
    SPR_SEC_1,

    NUM_SPRITES

  };

  int mState { ST_HIDE };
  THudAlarm mStateTimer;
  u32 mFlashMin { 0 };
  float mFlashTime { 0.0F };
  TSprite mSprite[NUM_SPRITES];
  u32 mSpriteMask { 0 };

  void setOffSprite(u32 i) { mSpriteMask |= (1U << i); }
  void setOnSprite(u32 i) { mSpriteMask &= ~(1U << i); }

};

// -------------------------------------------------------------------------- //

class THudCountDown {

  public:

  THudCountDown() = default;
  ~THudCountDown() = default;

  void hide();
  void show();
  void timeup();

  void init();
  void update();
  void draw();

  private:

  enum {

    ST_HIDE,
    ST_READY_IN,
    ST_READY,
    ST_READY_3,
    ST_READY_2,
    ST_READY_1,
    ST_FLY,
    ST_FLY_OUT,
    ST_TIMEUP_IN,
    ST_TIMEUP_WAIT,
    ST_TIMEUP_OUT

  };

  enum : u32 {

    SPR_HEADER,
    SPR_DIGIT,

    NUM_SPRITES

  };

  int mState { ST_HIDE };
  THudAlarm mStateTimer;
  TSprite mSprite[NUM_SPRITES];
  u32 mSpriteMask { 0 };

  void setOffSprite(u32 i) { mSpriteMask |= (1U << i); }
  void setOnSprite(u32 i) { mSpriteMask &= ~(1U << i); }

};

// -------------------------------------------------------------------------- //

class THudResults {

  public:

  THudResults() = default;
  ~THudResults() = default;

  void hide();
  void show();

  void init(u32 rank);
  void update();
  void draw();

  private:

  enum {

    ST_HIDE,
    ST_RESULTS_IN,
    ST_RESULTS_WAIT,
    ST_TALLY,
    ST_TALLY_WAIT,
    ST_RANK_IN,
    ST_RANK_STAR,
    ST_RANK_WAIT

  };

  enum : u32 {

    SPR_RESULTS,
    SPR_BIRD,

    SPR_STAR,
    SPR_RANK,
    SPR_RANK_0,

    SPR_TALLY0_TITLE,
    SPR_TALLY0_DIGIT0,
    SPR_TALLY0_DIGIT1,

    SPR_TALLY1_TITLE,
    SPR_TALLY1_DIGIT0,
    SPR_TALLY1_DIGIT1,

    SPR_TALLY2_TITLE,
    SPR_TALLY2_DIGIT0,
    SPR_TALLY2_DIGIT1,

    SPR_TALLY3_TITLE,
    SPR_TALLY3_DIGIT0,
    SPR_TALLY3_DIGIT1,

    SPR_TALLY4_TITLE,
    SPR_TALLY4_DIGIT0,
    SPR_TALLY4_DIGIT1,

    NUM_SPRITES,

    NUM_DISP_TALLY = 5

  };

  struct TRankInfo {

    Sprite const * bird_spr;
    TVec2S bird_ofs;

    Sprite const * rank_spr;
    TVec2S rank_pos;
    TVec2S rank_sz;

    Sprite const * star_spr;
    TVec2S star_pos;
    TVec2S star_sz;

    void * rom_src;
    s32 rom_sz;

  };

  int mState { ST_HIDE };
  THudAlarm mStateTimer;
  TSprite mSprite[NUM_SPRITES];
  u32 mSpriteMask { 0 };
  u8 mTally[NUM_TALLY];
  u8 mMaxNumTally { 0 };
  u8 mNumTally { 0 };
  float mWaveTimer { 0.0F };
  u32 mRank { 0 };

  static TRankInfo sRankInfo[NUM_RANKS];

  void setOffSprite(u32 i) { mSpriteMask |= (1U << i); }
  void setOnSprite(u32 i) { mSpriteMask &= ~(1U << i); }

  static Sprite const & getTallySprite(u32);
  static Sprite const & getDigitSprite(u32);

};

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

  void startCountDown();
  void stopTimer();

  bool isCountedDown() const;
  bool isTimeUp() const;

  static void splitDigits(u32, u32[], u32);
  static Sprite const & getDigitSprite(u32);

  private:

  enum {

    ST_HIDE,
    ST_COUNTDOWN,
    ST_SHOW,
    ST_TIME_FLASH,
    ST_TIME_UP,
    ST_RESULTS,
    ST_SCORE

  };

  int mState { ST_HIDE };
  THudAlarm mStateTimer;
  u32 mTimeLimit { 0 };
  TTimer mClock;
  THudResults * mResults { nullptr };
  THudCountDown mCountDown;
  THudScore mScore;
  THudTime mTime;
  bool mScoreDown { false };
  bool mTimeUp { false };

};

// -------------------------------------------------------------------------- //

extern THud * gHud;

// -------------------------------------------------------------------------- //

#endif
