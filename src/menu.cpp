
#include "app.hpp"
#include "dynlist.hpp"
#include "hud.hpp"
#include "menu.hpp"
#include "scene.hpp"
#include "segment.h"
#include "sprite.hpp"
#include "util.hpp"

#include "../models/ovl/sprites/sp_menu.h"
#include "../models/static/sprites/black_sprite.h"
#include "../models/static/sprites/white_sprite.h"

// -------------------------------------------------------------------------- //

static bool sFreedomMode { false };
static u32 sTimeLimit { 0 };

// -------------------------------------------------------------------------- //

template<typename T>
T Lerp(T p0, T p1, float mu) {
  return (T)((float)p0 * (1.0F - mu) + (float)p1 * mu);
}

// -------------------------------------------------------------------------- //

template<typename T>
T Sinerp(T p0, T p1, float mu) {
  float a = TSine::fromDeg(mu * 90.0F);
  return Lerp<T>(p0, p1, TSine::ssin(a));
}

// -------------------------------------------------------------------------- //

template<typename T>
T Coserp(T p0, T p1, float mu) {
  float a = TSine::fromDeg(mu * 90.0F);
  return Lerp<T>(p0, p1, (1.0F - TSine::scos(a)));
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

TMenuScene::TMenuScene(TDynList2 * dl) :
  TScene { "Menu", dl }
{}

// -------------------------------------------------------------------------- //

void TMenuScene::init() {
  mStatus = ESceneState::RUNNING;
  nuGfxDisplayOn();

  TUtil::toMemory(
    _menu_ovlSegmentStart,
    _menu_ovlSegmentRomStart, (s32)(
      _menu_ovlSegmentRomEnd -
      _menu_ovlSegmentRomStart
    )
  );

  mPad = new TPad { 0 };

  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    mSprite[i].setAttributes(SP_TRANSPARENT | SP_FRACPOS);
    setOffSprite(i);
  }

  mSprite[SPR_BG].load(menu_bg_sprite);

  mSprite[SPR_BIRD].load(menu_bird_sprite);

  mSprite[SPR_LOGO].load(menu_logo_sprite);
  mSprite[SPR_LOGO].setPosition({ 24, 25 });

  mSprite[SPR_FLASH].load(white_sprite);
  mSprite[SPR_FLASH].setPosition({ 0, 0 });
  mSprite[SPR_FLASH].setScale({ 10.0F, 7.5F });

  mSprite[SPR_MENU_SWOOP].load(menu_swoop_sprite);
  mSprite[SPR_MENU_SWOOP].setPosition({ 45, 162 });
  mSprite[SPR_MENU_SWOOP].setColor({ 255, 255, 255, 127 });

  mSprite[SPR_MENU_LEFT].load(menu_left_sprite);
  mSprite[SPR_MENU_RIGHT].load(menu_right_sprite);

  mSprite[SPR_START].load(menu_ok_sprite);

  mStateTimer.set(1.0F);

  mMenuList[0] = OPT_PRACTICE;
  mMenuList[1] = OPT_TIME;
  mMenuList[2] = OPT_FREEDOM;
  mNumMenuOpts = 3;
}

// -------------------------------------------------------------------------- //

void TMenuScene::update() {
  mPad->read();

  switch (mState) {
    case ST_BIRD_IN: {
      setOnSprite(SPR_BIRD);
      s16 x, y;
      float t;

      x = Lagrange<s16>(-40, 96, 174, mStateTimer.get());
      y = Lagrange<s16>(-50, 90, 16, mStateTimer.get());
      t = Sinerp<float>(0.0F, 1.0F, mStateTimer.get());

      x += (s16)((float)menu_birdTRUEIMAGEW * (1.0 - t) * 0.5F);
      y += (s16)((float)menu_birdTRUEIMAGEH * (1.0 - t) * 0.5F);

      mSprite[SPR_BIRD].setPosition({ x, y });
      mSprite[SPR_BIRD].setScale({ t, t });

      if (mStateTimer.update()) {
        mSprite[SPR_BIRD].setPosition({ 174, 16 });
        mSprite[SPR_BIRD].setScale({ 1.0F, 1.0F });

        mState = ST_FLASH_IN;
        mStateTimer.set(0.25F);
      }

      break;
    }
    case ST_FLASH_IN: {
      setOnSprite(SPR_FLASH);
      u8 a = Lerp<u8>(0, 255, mStateTimer.get());
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        setOnSprite(SPR_BG);
        setOnSprite(SPR_MENU_SWOOP);
        setOnSprite(SPR_LOGO);

        mState = ST_FLASH_OUT;
        mStateTimer.set(0.25F);
      }

      break;
    }
    case ST_FLASH_OUT: {
      setOnSprite(SPR_FLASH);
      u8 a = Lerp<u8>(255, 0, mStateTimer.get());
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        setOffSprite(SPR_FLASH);
        mSprite[SPR_FLASH].load(black_sprite);
        mSprite[SPR_MENU_0].load(getOptSprite(mMenuList[mMenuOpt]));

        mState = ST_MENU_WAIT;
      }

      break;
    }
    case ST_MENU_WAIT: {
      setOnSprite(SPR_MENU_0);
      setOffSprite(SPR_MENU_1);
      setOnSprite(SPR_MENU_LEFT);
      setOnSprite(SPR_MENU_RIGHT);
      s16 x, y, x0;

      y = (s16)(5.0F * TSine::ssin(
        TSine::fromDeg(mMenuTimer * 360.0F)
      ));

      x0 = (s16)(160 - getOptWidth(mMenuList[mMenuOpt]) / 2);
      mSprite[SPR_MENU_0].setPosition({ x0, (s16)(151 + y) });

      x = TMath<s16>::abs((s16)(5.0F * TSine::ssin(
        TSine::fromDeg(mMenuTimer * 360.0F)
      )));

      mSprite[SPR_MENU_LEFT].setPosition({ (s16)(46 - x), (s16)160 });
      mSprite[SPR_MENU_RIGHT].setPosition({ (s16)(260 + x), (s16)160 });

      mMenuTimer += kInterval;

      if (isPressSelect()) {
        mMenuTimer = 0.0F;
        mState = ST_MENU_FLASH;
        mStateTimer.set(1.0F);
      } else if (isPressLeft()) {
        mMenuTimer = 0.0F;
        mOldMenuOpt = mMenuOpt;

        if (mMenuOpt == 0) {
          mMenuOpt = (mNumMenuOpts - 1);
        } else {
          --mMenuOpt;
        }

        mSprite[SPR_MENU_0].load(getOptSprite(mMenuList[mMenuOpt]));
        mSprite[SPR_MENU_0].setColor({ 255, 255, 255, 0 });

        mSprite[SPR_MENU_1].load(getOptSprite(mMenuList[mOldMenuOpt]));
        mSprite[SPR_MENU_1].setColor({ 255, 255, 255, 255 });
        mSprite[SPR_MENU_1].setPosition({ x0, (s16)151 });
        setOnSprite(SPR_MENU_1);
        setOffSprite(SPR_MENU_RIGHT);

        mState = ST_MENU_LEFT;
        mStateTimer.set(0.5F);
      } else if (isPressRight()) {
        mMenuTimer = 0.0F;
        mOldMenuOpt = mMenuOpt;

        if (mMenuOpt == (mNumMenuOpts - 1)) {
          mMenuOpt = 0;
        } else {
          ++mMenuOpt;
        }

        mSprite[SPR_MENU_0].load(getOptSprite(mMenuList[mMenuOpt]));
        mSprite[SPR_MENU_0].setColor({ 255, 255, 255, 0 });

        mSprite[SPR_MENU_1].load(getOptSprite(mMenuList[mOldMenuOpt]));
        mSprite[SPR_MENU_1].setColor({ 255, 255, 255, 255 });
        mSprite[SPR_MENU_1].setPosition({ x0, (s16)151 });
        setOnSprite(SPR_MENU_1);
        setOffSprite(SPR_MENU_LEFT);

        mState = ST_MENU_RIGHT;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_MENU_LEFT: {
      s16 x, y, w, x0, x1, x2;
      float t;
      u8 a;

      t = Sinerp<float>(0.4F, 1.0F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mMenuOpt]) / 2) * t);

      x0 = (s16)(50 - w);
      x1 = (s16)(80 - w);
      x2 = (s16)(160 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(120, 145, 151, mStateTimer.get());
      a = Lerp<u8>(0, 255, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_0].setPosition({ x, y });
      mSprite[SPR_MENU_0].setColor({ 255, 255, 255, a });
      mSprite[SPR_MENU_0].setScale({ t, t });

      t = Coserp<float>(1.0F, 0.4F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mOldMenuOpt]) / 2) * t);

      x0 = (s16)(160 - w);
      x1 = (s16)(240 - w);
      x2 = (s16)(270 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(151, 145, 120, mStateTimer.get());
      a = Lerp<u8>(255, 0, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_1].setPosition({ x, y });
      mSprite[SPR_MENU_1].setColor({ 255, 255, 255, a });
      mSprite[SPR_MENU_1].setScale({ t, t });

      x = Lagrange<s16>(46, -24, 46, mStateTimer.get());
      mSprite[SPR_MENU_LEFT].setPosition({ x, (s16)160 });

      if (mStateTimer.update()) {
        mSprite[SPR_MENU_1].setScale({ 1.0F, 1.0F });
        setOffSprite(SPR_MENU_1);
        mState = ST_MENU_WAIT;
      }

      break;
    }
    case ST_MENU_RIGHT: {
      s16 x, y, w, x0, x1, x2;
      float t;
      u8 a;

      t = Sinerp<float>(0.4F, 1.0F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mMenuOpt]) / 2) * t);

      x0 = (s16)(270 - w);
      x1 = (s16)(240 - w);
      x2 = (s16)(160 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(120, 145, 151, mStateTimer.get());
      a = Lerp<u8>(0, 255, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_0].setPosition({ x, y });
      mSprite[SPR_MENU_0].setColor({ 255, 255, 255, a });
      mSprite[SPR_MENU_0].setScale({ t, t });

      t = Coserp<float>(1.0F, 0.4F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mOldMenuOpt]) / 2) * t);

      x0 = (s16)(160 - w);
      x1 = (s16)(80 - w);
      x2 = (s16)(50 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(151, 145, 120, mStateTimer.get());
      a = Lerp<u8>(255, 0, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_1].setPosition({ x, y });
      mSprite[SPR_MENU_1].setColor({ 255, 255, 255, a });
      mSprite[SPR_MENU_1].setScale({ t, t });

      x = Lagrange<s16>(260, 320, 260, mStateTimer.get());
      mSprite[SPR_MENU_RIGHT].setPosition({ x, (s16)160 });

      if (mStateTimer.update()) {
        mSprite[SPR_MENU_1].setScale({ 1.0F, 1.0F });
        setOffSprite(SPR_MENU_1);
        mState = ST_MENU_WAIT;
      }

      break;
    }
    case ST_MENU_FLASH: {
      setOnSprite(SPR_MENU_0);
      setOffSprite(SPR_MENU_LEFT);
      setOffSprite(SPR_MENU_RIGHT);
      s16 x, y, x0;

      x0 = (s16)(160 - getOptWidth(mMenuList[mMenuOpt]) / 2);
      mSprite[SPR_MENU_0].setPosition({ x0, (s16)151 });

      if (TMath<float>::mod(mStateTimer.get(), 0.125F) >= 0.0625F) {
        setOffSprite(SPR_MENU_0);
      } else {
        setOnSprite(SPR_MENU_0);
      }

      if (mStateTimer.update()) {
        setOnSprite(SPR_MENU_0);

        if (mMenuOpt == OPT_TIME || mMenuOpt == OPT_FREEDOM) {
          mSubMenuList[0] = SUBOPT_300;
          mSubMenuList[1] = SUBOPT_500;
          mSubMenuList[2] = SUBOPT_700;
          mNumSubMenuOpts = 3;
          mSubMenuOpt = 1;

          mState = ST_SUBMENU_IN;
          mStateTimer.set(0.5F);
        } else {
          mState = ST_START_IN;
          mStateTimer.set(0.5F);
        }
      }

      break;
    }
    case ST_SUBMENU_IN: {
      s16 x, y, w;
      float t;

      t = Sinerp<float>(1.0F, 0.5F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mMenuOpt]) / 2) * t);

      x = (s16)(160 - w);
      y = Sinerp<s16>(151, 108, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_0].setPosition({ x, y });
      mSprite[SPR_MENU_0].setScale({ t, t });

      if (mStateTimer.update()) {
        mSprite[SPR_SUBMENU_0].load(
          getSubOptSprite(mMenuList[mSubMenuOpt])
        );

        mState = ST_SUBMENU_WAIT;
      }

      break;
    }
    case ST_SUBMENU_WAIT: {
      setOnSprite(SPR_SUBMENU_0);
      setOffSprite(SPR_SUBMENU_1);
      setOnSprite(SPR_MENU_LEFT);
      setOnSprite(SPR_MENU_RIGHT);

      s16 x, y, x0;

      y = (s16)(5.0F * TSine::ssin(
        TSine::fromDeg(mMenuTimer * 360.0F)
      ));

      x0 = (s16)(160 - getSubOptWidth(mMenuList[mMenuOpt]) / 2);
      mSprite[SPR_SUBMENU_0].setPosition({ x0, (s16)(163 + y) });

      x = TMath<s16>::abs((s16)(5.0F * TSine::ssin(
        TSine::fromDeg(mMenuTimer * 360.0F)
      )));

      mSprite[SPR_MENU_LEFT].setPosition({ (s16)(46 - x), (s16)160 });
      mSprite[SPR_MENU_RIGHT].setPosition({ (s16)(260 + x), (s16)160 });

      mMenuTimer += kInterval;

      if (isPressSelect()) {
        mMenuTimer = 0.0F;

        mState = ST_SUBMENU_FLASH;
        mStateTimer.set(1.0F);
      } else if (isPressCancel()) {
        mMenuTimer = 0.0F;

        mState = ST_SUBMENU_OUT;
        mStateTimer.set(0.5F);
      } else if (isPressLeft()) {
        mMenuTimer = 0.0F;
        mOldSubMenuOpt = mSubMenuOpt;

        if (mSubMenuOpt == 0) {
          mSubMenuOpt = (mNumSubMenuOpts - 1);
        } else {
          --mSubMenuOpt;
        }

        mSprite[SPR_SUBMENU_0].load(
          getSubOptSprite(mSubMenuList[mSubMenuOpt])
        );

        mSprite[SPR_SUBMENU_1].load(
          getSubOptSprite(mSubMenuList[mOldSubMenuOpt])
        );

        mSprite[SPR_SUBMENU_0].setColor({ 255, 255, 255, 0 });
        mSprite[SPR_SUBMENU_1].setColor({ 255, 255, 255, 255 });
        mSprite[SPR_SUBMENU_1].setPosition({ x0, (s16)163 });

        setOnSprite(SPR_SUBMENU_1);
        setOffSprite(SPR_MENU_RIGHT);

        mState = ST_SUBMENU_LEFT;
        mStateTimer.set(0.5F);
      } else if (isPressRight()) {
        mMenuTimer = 0.0F;
        mOldSubMenuOpt = mSubMenuOpt;

        if (mSubMenuOpt == (mNumSubMenuOpts - 1)) {
          mSubMenuOpt = 0;
        } else {
          ++mSubMenuOpt;
        }

        mSprite[SPR_SUBMENU_0].load(
          getSubOptSprite(mSubMenuList[mSubMenuOpt])
        );

        mSprite[SPR_SUBMENU_1].load(
          getSubOptSprite(mSubMenuList[mOldSubMenuOpt])
        );

        mSprite[SPR_SUBMENU_0].setColor({ 255, 255, 255, 0 });
        mSprite[SPR_SUBMENU_1].setColor({ 255, 255, 255, 255 });
        mSprite[SPR_SUBMENU_1].setPosition({ x0, (s16)163 });

        setOnSprite(SPR_SUBMENU_1);
        setOffSprite(SPR_MENU_LEFT);

        mState = ST_SUBMENU_RIGHT;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_SUBMENU_FLASH: {
      setOnSprite(SPR_SUBMENU_0);
      setOffSprite(SPR_MENU_LEFT);
      setOffSprite(SPR_MENU_RIGHT);
      s16 x, y, x0;

      x0 = (s16)(160 - getSubOptWidth(mSubMenuList[mSubMenuOpt]) / 2);
      mSprite[SPR_SUBMENU_0].setPosition({ x0, (s16)159 });

      if (TMath<float>::mod(mStateTimer.get(), 0.125F) >= 0.0625F) {
        setOffSprite(SPR_SUBMENU_0);
      } else {
        setOnSprite(SPR_SUBMENU_0);
      }

      if (mStateTimer.update()) {
        setOnSprite(SPR_SUBMENU_0);

        mState = ST_START_IN;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_SUBMENU_LEFT: {
      s16 x, y, w, x0, x1, x2;
      float t;
      u8 a;

      t = Sinerp<float>(0.4F, 1.0F, mStateTimer.get());
      w = (s16)((float)(getSubOptWidth(mSubMenuList[mSubMenuOpt]) / 2) * t);

      x0 = (s16)(50 - w);
      x1 = (s16)(80 - w);
      x2 = (s16)(160 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(132, 157, 163, mStateTimer.get());
      a = Lerp<u8>(0, 255, mStateTimer.get());
      y += (s16)((float)(menu_300TRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_SUBMENU_0].setPosition({ x, y });
      mSprite[SPR_SUBMENU_0].setColor({ 255, 255, 255, a });
      mSprite[SPR_SUBMENU_0].setScale({ t, t });

      t = Coserp<float>(1.0F, 0.4F, mStateTimer.get());
      w = (s16)((float)(getSubOptWidth(mSubMenuList[mOldSubMenuOpt]) / 2) * t);

      x0 = (s16)(160 - w);
      x1 = (s16)(240 - w);
      x2 = (s16)(270 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(163, 157, 132, mStateTimer.get());
      a = Lerp<u8>(255, 0, mStateTimer.get());
      y += (s16)((float)(menu_300TRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_SUBMENU_1].setPosition({ x, y });
      mSprite[SPR_SUBMENU_1].setColor({ 255, 255, 255, a });
      mSprite[SPR_SUBMENU_1].setScale({ t, t });

      x = Lagrange<s16>(46, -24, 46, mStateTimer.get());
      mSprite[SPR_MENU_LEFT].setPosition({ x, (s16)160 });

      if (mStateTimer.update()) {
        mSprite[SPR_SUBMENU_1].setScale({ 1.0F, 1.0F });
        setOffSprite(SPR_SUBMENU_1);
        mState = ST_SUBMENU_WAIT;
      }

      break;
    }
    case ST_SUBMENU_RIGHT: {
      s16 x, y, w, x0, x1, x2;
      float t;
      u8 a;

      t = Sinerp<float>(0.4F, 1.0F, mStateTimer.get());
      w = (s16)((float)(getSubOptWidth(mSubMenuList[mSubMenuOpt]) / 2) * t);

      x0 = (s16)(270 - w);
      x1 = (s16)(240 - w);
      x2 = (s16)(160 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(132, 157, 163, mStateTimer.get());
      a = Lerp<u8>(0, 255, mStateTimer.get());
      y += (s16)((float)(menu_300TRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_SUBMENU_0].setPosition({ x, y });
      mSprite[SPR_SUBMENU_0].setColor({ 255, 255, 255, a });
      mSprite[SPR_SUBMENU_0].setScale({ t, t });

      t = Coserp<float>(1.0F, 0.4F, mStateTimer.get());
      w = (s16)((float)(getSubOptWidth(mSubMenuList[mOldSubMenuOpt]) / 2) * t);

      x0 = (s16)(160 - w);
      x1 = (s16)(80 - w);
      x2 = (s16)(50 - w);

      x = Lagrange<s16>(x0, x1, x2, mStateTimer.get());
      y = Lagrange<s16>(163, 157, 132, mStateTimer.get());
      a = Lerp<u8>(255, 0, mStateTimer.get());
      y += (s16)((float)(menu_300TRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_SUBMENU_1].setPosition({ x, y });
      mSprite[SPR_SUBMENU_1].setColor({ 255, 255, 255, a });
      mSprite[SPR_SUBMENU_1].setScale({ t, t });

      x = Lagrange<s16>(260, 320, 260, mStateTimer.get());
      mSprite[SPR_MENU_RIGHT].setPosition({ x, (s16)160 });

      if (mStateTimer.update()) {
        mSprite[SPR_SUBMENU_1].setScale({ 1.0F, 1.0F });
        setOffSprite(SPR_SUBMENU_1);
        mState = ST_SUBMENU_WAIT;
      }

      break;
    }
    case ST_SUBMENU_OUT: {
      setOffSprite(SPR_SUBMENU_0);
      setOffSprite(SPR_SUBMENU_1);
      setOffSprite(SPR_MENU_LEFT);
      setOffSprite(SPR_MENU_RIGHT);

      s16 x, y, w;
      float t;

      t = Sinerp<float>(0.5F, 1.0F, mStateTimer.get());
      w = (s16)((float)(getOptWidth(mMenuList[mMenuOpt]) / 2) * t);

      x = (s16)(160 - w);
      y = Sinerp<s16>(108, 151, mStateTimer.get());
      y += (s16)((float)(menu_practiceTRUEIMAGEH / 2) * (1.0F - t));

      mSprite[SPR_MENU_0].setPosition({ x, y });
      mSprite[SPR_MENU_0].setScale({ t, t });

      if (mStateTimer.update()) {
        mSprite[SPR_MENU_0].setScale({ 1.0F, 1.0F });
        mState = ST_MENU_WAIT;
      }

      break;
    }
    case ST_START_IN: {
      setOnSprite(SPR_FLASH);
      setOnSprite(SPR_START);

      s16 x, y, w;
      u8 a;

      w = (s16)(menu_okTRUEIMAGEW / 2);
      x = Lagrange<s16>(-300, 320, (140 - w), mStateTimer.get());
      y = (s16)(120 - menu_okTRUEIMAGEH / 2);
      a = Lerp<u8>(0, 200, mStateTimer.get());

      mSprite[SPR_START].setPosition({ x, y });
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        mState = ST_START_WAIT;
      }

      break;
    }
    case ST_START_WAIT: {
      if (isPressSelect()) {
        mState = ST_START_OUT;
        mStateTimer.set(0.5F);
      } else if (isPressCancel()) {
        mState = ST_START_CANCEL;
        mStateTimer.set(0.5F);
      }

      break;
    }
    case ST_START_OUT: {
      s16 x, y, w;
      u8 a;

      w = (s16)(menu_okTRUEIMAGEW / 2);
      x = Lagrange<s16>((160 - w), 0, 400, mStateTimer.get());
      y = (s16)(120 - menu_okTRUEIMAGEH / 2);
      a = Lerp<u8>(200, 255, mStateTimer.get(0.0F, 0.5F));

      mSprite[SPR_START].setPosition({ x, y });
      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        mStatus = ESceneState::EXITING;
      }

      break;
    }
    case ST_START_CANCEL: {
      setOffSprite(SPR_START);
      u8 a;

      a = Lerp<u8>(200, 0, mStateTimer.get());

      mSprite[SPR_FLASH].setColor({ 255, 255, 255, a });

      if (mStateTimer.update()) {
        setOffSprite(SPR_FLASH);

        if (mMenuList[mMenuOpt] == OPT_PRACTICE) {
          mState = ST_MENU_WAIT;
        } else {
          mState = ST_SUBMENU_WAIT;
        }
      }

      break;
    }
  }
}

// -------------------------------------------------------------------------- //

void TMenuScene::draw() {
  gDPSetColorImage(mDynList->pushDL(),
    G_IM_FMT_RGBA, G_IM_SIZ_16b, kResWidth,
    osVirtualToPhysical(nuGfxCfb_ptr)
  );

  u32 color = GPACK_RGBA5551(20, 60, 100, 1); // (108, 48, 142, 1);

  gDPSetFillColor(mDynList->pushDL(),
    ((color << 16) | color)
  );

  gDPFillRectangle(mDynList->pushDL(),
    0, 0, (kResWidth - 1), (kResHeight - 1)
  );
}

// -------------------------------------------------------------------------- //

void TMenuScene::draw2D() {
  for (u32 i = 0; i < NUM_SPRITES; ++i) {
    if (mSpriteMask & (1U << i)) {
      continue;
    }

    mSprite[i].draw();
  }
}

// -------------------------------------------------------------------------- //

TScene *
TMenuScene::exit() {
  int mode = mMenuList[mMenuOpt];
  sFreedomMode = (mode == OPT_FREEDOM);

  if (mode == OPT_PRACTICE) {
    sTimeLimit = 0;
  } else {
    switch (mSubMenuList[mSubMenuOpt]) {
      case SUBOPT_300: {
        sTimeLimit = 3;
        break;
      }
      case SUBOPT_500: {
        sTimeLimit = 5;
        break;
      }
      case SUBOPT_700: {
        sTimeLimit = 7;
        break;
      }
    }
  }

  return new TTestScene { "game", mDynList };
}

// -------------------------------------------------------------------------- //

u32 TMenuScene::getTimeLimit() {
  return sTimeLimit;
}

// -------------------------------------------------------------------------- //

bool TMenuScene::isFreedomMode() {
  return sFreedomMode;
}

// -------------------------------------------------------------------------- //

bool TMenuScene::isPressLeft() const {
  if (mPad->getAnalogX() < -20) {
    return true;
  }

  if (mPad->isHeld((EButton)(EButton::LEFT | EButton::C_LEFT))) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

bool TMenuScene::isPressRight() const {
  if (mPad->getAnalogX() > 20) {
    return true;
  }

  if (mPad->isHeld((EButton)(EButton::RIGHT | EButton::C_RIGHT))) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

bool TMenuScene::isPressSelect() const {
  if (mPad->isHeld((EButton)(EButton::START | EButton::A))) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

bool TMenuScene::isPressCancel() const {
  if (mPad->isHeld(EButton::B)) {
    return true;
  }

  return false;
}

// -------------------------------------------------------------------------- //

Sprite const &
TMenuScene::getOptSprite(int opt) {
  static Sprite const * SPRITES[NUM_OPTIONS] = {
    &menu_practice_sprite,
    &menu_time_sprite,
    &menu_freedom_sprite,
  };

  return *SPRITES[opt % NUM_OPTIONS];
}

// -------------------------------------------------------------------------- //

s16 TMenuScene::getOptWidth(int opt) {
  static s16 WIDTHS[NUM_OPTIONS] = {
    menu_practiceTRUEIMAGEW,
    menu_timeTRUEIMAGEW,
    menu_freedomTRUEIMAGEW,
  };

  return WIDTHS[opt % NUM_OPTIONS];
}

// -------------------------------------------------------------------------- //

Sprite const &
TMenuScene::getSubOptSprite(int opt) {
  static Sprite const * SPRITES[NUM_SUBOPTIONS] = {
    &menu_300_sprite,
    &menu_500_sprite,
    &menu_700_sprite,
  };

  return *SPRITES[opt % NUM_SUBOPTIONS];
}

// -------------------------------------------------------------------------- //

s16 TMenuScene::getSubOptWidth(int opt) {
  static s16 WIDTHS[NUM_SUBOPTIONS] = {
    menu_300TRUEIMAGEW,
    menu_500TRUEIMAGEW,
    menu_700TRUEIMAGEW,
  };

  return WIDTHS[opt % NUM_SUBOPTIONS];
}

// -------------------------------------------------------------------------- //
