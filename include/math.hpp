
#ifndef INCLUDE_MATH_HPP
#define INCLUDE_MATH_HPP

#include <ultra64.h>

#include "heap.hpp"

// -------------------------------------------------------------------------- //

template<typename T>
class TMath {

  public:

  static constexpr T epsilon() { return (T)1; }
  static constexpr T zero() { return (T)0; }
  static constexpr T one() { return (T)1; }

  static T abs(T x) { return (x >= zero() ? x : -x); }

  static inline T sqrt(T x) { return x; } // TODO integer sqrt

};

// -------------------------------------------------------------------------- //

template<>
class TMath<float> {

  public:

  static constexpr float epsilon() { return 0.0001F; }
  static constexpr float zero() { return 0.0F; }
  static constexpr float one() { return 1.0F; }

  static float abs(float x) { return (x >= 0.0F ? x : -x); }

  static inline float sqrt(float x) { return sqrtf(x); }

};

// -------------------------------------------------------------------------- //

template<typename T> class TVec2;
template<typename T> class TVec3;

// -------------------------------------------------------------------------- //

template<typename T>
class TVec2 {

  public:

  TVec2() = default;

  template<typename T2>
  TVec2(T2 x, T2 y) { set(x, y); }

  template<typename T2>
  TVec2(TVec2<T2> const & v) { set<T2>(v.x(), v.y()); }

  T & x() { return mData[0]; }
  T x() const { return mData[0]; }

  T & y() { return mData[1]; }
  T y() const { return mData[1]; }

  T * data() { return mData; }
  T const * data() const { return mData; }

  template<typename T2>
  void set(T2 x, T2 y) {
    mData[0] = static_cast<T>(x);
    mData[1] = static_cast<T>(y);
  }

  // addition

  void add(TVec2<T> const & v) { add(*this, v); }

  void add(TVec2<T> const & a, TVec2<T> const & b) {
    set((a.x() + b.x()), (a.y() + b.y()));
  }

  TVec2<T> & operator+=(TVec2<T> const & v) {
    add(*this, v);
    return *this;
  }

  // subtraction

  void sub(TVec2<T> const & v) { sub(*this, v); }

  void sub(TVec2<T> const & a, TVec2<T> const & b) {
    set((a.x() - b.x()), (a.y() - b.y()));
  }

  TVec2<T> & operator-=(TVec2<T> const & v) {
    sub(*this, v);
    return *this;
  }

  // multiplication

  void mul(T x) { mul(*this, x); }
  void mul(TVec2<T> const & v) { mul(*this, v); }

  void mul(TVec2<T> const & v, T x) {
    set((v.x() * x), (v.y() * x));
  }

  void mul(TVec2<T> const & a, TVec2<T> const & b) {
    set((a.x() * b.x()), (a.y() * b.y()));
  }

  TVec2<T> & operator*=(T x) {
    mul(*this, x);
    return *this;
  }

  TVec2<T> & operator*=(TVec2<T> const & v) {
    mul(*this, v);
    return *this;
  }

  // division

  void div(T x) { div(*this, x); }
  void div(TVec2<T> const & v) { div(*this, v); }

  void div(TVec2<T> const & v, T x) {
    set((v.x() / x), (v.y() / x));
  }

  void div(TVec2<T> const & a, TVec2<T> const & b) {
    set((a.x() / b.x()), (a.y() / b.y()));
  }

  TVec2<T> & operator/=(T x) {
    div(*this, x);
    return *this;
  }

  TVec2<T> & operator/=(TVec2<T> const & v) {
    div(*this, v);
    return *this;
  }

  // operators

  T dot(TVec2<T> const & v) const {
    return (x() * v.x() + y() * v.y());
  }

  T getSqrLength() const { return dot(*this); }
  T getLength() const { return TMath<T>::sqrt(getSqrLength()); }

  void setLength(T x) { setLength(*this, x); }

  void setLength(TVec2<f32> const & v, T x) {
    T const len = v.getLength();

    if (len != TMath<T>::zero()) {
      mul(v, (x / len));
    } else {
      set(0, 0);
    }
  }

  void normalize() { setLength(*this, TMath<T>::one()); }

  // swizzle

  TVec2<T> xx() const { return TVec2<T> { x(), x() }; }
  TVec2<T> xy() const { return TVec2<T> { x(), y() }; }
  TVec2<T> yx() const { return TVec2<T> { y(), x() }; }
  TVec2<T> yy() const { return TVec2<T> { y(), y() }; }
  TVec3<T> xxx() const { return TVec3<T> { x(), x(), x() }; }
  TVec3<T> xxy() const { return TVec3<T> { x(), x(), y() }; }
  TVec3<T> xyx() const { return TVec3<T> { x(), y(), x() }; }
  TVec3<T> xyy() const { return TVec3<T> { x(), y(), y() }; }
  TVec3<T> yxx() const { return TVec3<T> { y(), x(), x() }; }
  TVec3<T> yxy() const { return TVec3<T> { y(), x(), y() }; }
  TVec3<T> yyx() const { return TVec3<T> { y(), y(), x() }; }
  TVec3<T> yyy() const { return TVec3<T> { y(), y(), y() }; }

  private:

  T mData[2];

};

// -------------------------------------------------------------------------- //

template<typename T1, typename T2>
bool operator==(TVec2<T1> const & lhs, TVec2<T2> const & rhs) {
  return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

template<typename T1, typename T2>
bool operator!=(TVec2<T1> const & lhs, TVec2<T2> const & rhs) {
  return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
}

template<typename T>
TVec2<T> operator+(TVec2<T> const & lhs, TVec2<T> const & rhs) {
  TVec2<T> v = lhs;
  v += rhs;
  return v;
}

template<typename T>
TVec2<T> operator-(TVec2<T> const & lhs, TVec2<T> const & rhs) {
  TVec2<T> v = lhs;
  v -= rhs;
  return v;
}

template<typename T>
TVec2<T> operator*(TVec2<T> const & lhs, T const & rhs) {
  TVec2<T> v = lhs;
  v *= rhs;
  return v;
}

template<typename T>
TVec2<T> operator*(T const & lhs, TVec2<T> const & rhs) {
  TVec2<T> v = rhs;
  v *= lhs;
  return v;
}

template<typename T>
TVec2<T> operator*(TVec2<T> const & lhs, TVec2<T> const & rhs) {
  TVec2<T> v = lhs;
  v *= rhs;
  return v;
}

template<typename T>
TVec2<T> operator/(TVec2<T> const & lhs, T const & rhs) {
  TVec2<T> v = lhs;
  v /= rhs;
  return v;
}

template<typename T>
TVec2<T> operator/(TVec2<T> const & lhs, TVec2<T> const & rhs) {
  TVec2<T> v = lhs;
  v /= rhs;
  return v;
}

// -------------------------------------------------------------------------- //

template<typename T>
class TVec3 {

  public:

  TVec3() = default;

  template<typename T2>
  TVec3(T2 x, T2 y, T2 z) { set<T2>(x, y, z); }

  template<typename T2>
  TVec3(TVec3<T2> const & v) { set<T2>(v.x(), v.y() , v.z()); }

  T & x() { return mData[0]; }
  T x() const { return mData[0]; }

  T & y() { return mData[1]; }
  T y() const { return mData[1]; }

  T & z() { return mData[2]; }
  T z() const { return mData[2]; }

  T * data() { return mData; }
  T const * data() const { return mData; }

  template<typename T2>
  void set(T2 x, T2 y, T2 z) {
    mData[0] = x;
    mData[1] = y;
    mData[2] = z;
  }

  // addition

  void add(TVec3<T> const & v) { add(*this, v); }

  void add(TVec3<T> const & a, TVec3<T> const & b) {
    set((a.x() + b.x()), (a.y() + b.y()), (a.z() + b.z()));
  }

  TVec3<T> & operator+=(TVec3<T> const & v) {
    add(*this, v);
    return *this;
  }

  // subtraction

  void sub(TVec3<T> const & v) { sub(*this, v); }

  void sub(TVec3<T> const & a, TVec3<T> const & b) {
    set((a.x() - b.x()), (a.y() - b.y()), (a.z() - b.z()));
  }

  TVec3<T> & operator-=(TVec3<T> const & v) {
    sub(*this, v);
    return *this;
  }

  // multiplication

  void mul(T x) { mul(*this, x); }
  void mul(TVec3<T> const & v) { mul(*this, v); }

  void mul(TVec3<T> const & v, T x) {
    set((v.x() * x), (v.y() * x), (v.z() * x));
  }

  void mul(TVec3<T> const & a, TVec3<T> const & b) {
    set((a.x() * b.x()), (a.y() * b.y()), (a.z() * b.z()));
  }

  TVec3<T> & operator*=(T x) {
    mul(*this, x);
    return *this;
  }

  TVec3<T> & operator*=(TVec3<T> const & v) {
    mul(*this, v);
    return *this;
  }

  // division

  void div(T x) { div(*this, x); }
  void div(TVec3<T> const & v) { div(*this, v); }

  void div(TVec3<T> const & v, T x) {
    set((v.x() / x), (v.y() / x), (v.z() / x));
  }

  void div(TVec3<T> const & a, TVec3<T> const & b) {
    set((a.x() / b.x()), (a.y() / b.y()), (a.z() / b.z()));
  }

  TVec3<T> & operator/=(T x) {
    div(*this, x);
    return *this;
  }

  TVec3<T> & operator/=(TVec3<T> const & v) {
    div(*this, v);
    return *this;
  }

  // operators

  TVec3<T> cross(TVec3<T> const & v) const {
    TVec3<T> p;

    p.set(
      (y() * v.z() - z() * v.y()),
      (z() * v.x() - x() * v.z()),
      (x() * v.y() - y() * v.x())
    );

    return p;
  }

  T dot(TVec3<T> const & v) const {
    return (x() * v.x() + y() * v.y() + z() * v.z());
  }

  T getSqrLength() const { return dot(*this); }
  T getLength() const { return TMath<T>::sqrt(getSqrLength()); }

  void setLength(T x) { setLength(*this, x); }

  void setLength(TVec3<f32> const & v, T x) {
    T const len = v.getLength();

    if (len != TMath<T>::zero()) {
      mul(v, (x / len));
    } else {
      set(0, 0);
    }
  }

  void normalize() { setLength(*this, TMath<T>::one()); }

  // swizzle

  TVec2<T> xx() const { return TVec2<T> { x(), x() }; }
  TVec2<T> xy() const { return TVec2<T> { x(), y() }; }
  TVec2<T> xz() const { return TVec2<T> { x(), z() }; }
  TVec2<T> yx() const { return TVec2<T> { y(), x() }; }
  TVec2<T> yy() const { return TVec2<T> { y(), y() }; }
  TVec2<T> yz() const { return TVec2<T> { y(), z() }; }
  TVec2<T> zx() const { return TVec2<T> { z(), x() }; }
  TVec2<T> zy() const { return TVec2<T> { z(), y() }; }
  TVec2<T> zz() const { return TVec2<T> { z(), z() }; }
  TVec3<T> xxx() const { return TVec3<T> { x(), x(), x() }; }
  TVec3<T> xxy() const { return TVec3<T> { x(), x(), y() }; }
  TVec3<T> xxz() const { return TVec3<T> { x(), x(), z() }; }
  TVec3<T> xyx() const { return TVec3<T> { x(), y(), x() }; }
  TVec3<T> xyy() const { return TVec3<T> { x(), y(), y() }; }
  TVec3<T> xyz() const { return TVec3<T> { x(), y(), z() }; }
  TVec3<T> xzx() const { return TVec3<T> { x(), z(), x() }; }
  TVec3<T> xzy() const { return TVec3<T> { x(), z(), y() }; }
  TVec3<T> xzz() const { return TVec3<T> { x(), z(), z() }; }
  TVec3<T> yxx() const { return TVec3<T> { y(), x(), x() }; }
  TVec3<T> yxy() const { return TVec3<T> { y(), x(), y() }; }
  TVec3<T> yxz() const { return TVec3<T> { y(), x(), z() }; }
  TVec3<T> yyx() const { return TVec3<T> { y(), y(), x() }; }
  TVec3<T> yyy() const { return TVec3<T> { y(), y(), y() }; }
  TVec3<T> yyz() const { return TVec3<T> { y(), y(), z() }; }
  TVec3<T> yzx() const { return TVec3<T> { y(), z(), x() }; }
  TVec3<T> yzy() const { return TVec3<T> { y(), z(), y() }; }
  TVec3<T> yzz() const { return TVec3<T> { y(), z(), z() }; }
  TVec3<T> zxx() const { return TVec3<T> { z(), x(), x() }; }
  TVec3<T> zxy() const { return TVec3<T> { z(), x(), y() }; }
  TVec3<T> zxz() const { return TVec3<T> { z(), x(), z() }; }
  TVec3<T> zyx() const { return TVec3<T> { z(), y(), x() }; }
  TVec3<T> zyy() const { return TVec3<T> { z(), y(), y() }; }
  TVec3<T> zyz() const { return TVec3<T> { z(), y(), z() }; }
  TVec3<T> zzx() const { return TVec3<T> { z(), z(), x() }; }
  TVec3<T> zzy() const { return TVec3<T> { z(), z(), y() }; }
  TVec3<T> zzz() const { return TVec3<T> { z(), z(), z() }; }

  private:

  T mData[3];

};

// -------------------------------------------------------------------------- //

template<typename T1, typename T2>
bool operator==(TVec3<T1> const & lhs, TVec3<T2> const & rhs) {
  return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}

template<typename T1, typename T2>
bool operator!=(TVec3<T1> const & lhs, TVec3<T2> const & rhs) {
  return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z());
}

template<typename T>
TVec3<T> operator+(TVec3<T> const & lhs, TVec3<T> const & rhs) {
  TVec3<T> v = lhs;
  v += rhs;
  return v;
}

template<typename T>
TVec3<T> operator-(TVec3<T> const & lhs, TVec3<T> const & rhs) {
  TVec3<T> v = lhs;
  v -= rhs;
  return v;
}

template<typename T>
TVec3<T> operator*(TVec3<T> const & lhs, T const & rhs) {
  TVec3<T> v = lhs;
  v *= rhs;
  return v;
}

template<typename T>
TVec3<T> operator*(T const & lhs, TVec3<T> const & rhs) {
  TVec3<T> v = rhs;
  v *= lhs;
  return v;
}

template<typename T>
TVec3<T> operator*(TVec3<T> const & lhs, TVec3<T> const & rhs) {
  TVec3<T> v = lhs;
  v *= rhs;
  return v;
}

template<typename T>
TVec3<T> operator/(TVec3<T> const & lhs, T const & rhs) {
  TVec3<T> v = lhs;
  v /= rhs;
  return v;
}

template<typename T>
TVec3<T> operator/(TVec3<T> const & lhs, TVec3<T> const & rhs) {
  TVec3<T> v = lhs;
  v /= rhs;
  return v;
}

// -------------------------------------------------------------------------- //

template<typename T>
class TMtx44 {

  public:

  TMtx44() = default;

  T & operator()(u32 r, u32 c) { return mCl[r][c]; }
  T operator()(u32 r, u32 c) const { return mCl[r][c]; }

  void set(
    T m00, T m01, T m02, T m03,
    T m10, T m11, T m12, T m13,
    T m20, T m21, T m22, T m23,
    T m30, T m31, T m32, T m33
  ) {
    mCl[0][0] = m00; mCl[0][1] = m01; mCl[0][2] = m02; mCl[0][3] = m03;
    mCl[1][0] = m10; mCl[1][1] = m11; mCl[1][2] = m12; mCl[1][3] = m13;
    mCl[2][0] = m20; mCl[2][1] = m21; mCl[2][2] = m22; mCl[2][3] = m23;
    mCl[3][0] = m30; mCl[3][1] = m31; mCl[3][2] = m32; mCl[3][3] = m33;
  }

  void identity() {
    auto const zero = TMath<T>::zero();
    auto const one  = TMath<T>::one();

    set(
       one, zero, zero, zero,
      zero,  one, zero, zero,
      zero, zero,  one, zero,
      zero, zero, zero,  one
    );
  }

  void scale(TVec3<T> const & v) {
    auto const zero = TMath<T>::zero();
    auto const one  = TMath<T>::one();

    set(
      v.x(),  zero,  zero, zero,
       zero, v.y(),  zero, zero,
       zero,  zero, v.z(), zero,
       zero,  zero,  zero,  one
    );
  }

  void translate(TVec3<T> const & v) {
    auto const zero = TMath<T>::zero();
    auto const one  = TMath<T>::one();

    set(
       one, zero, zero, v.x(),
      zero,  one, zero, v.y(),
      zero, zero,  one, v.z(),
      zero, zero, zero, one
    );
  }

  private:

  T mCl[4][4];

};

// -------------------------------------------------------------------------- //

class TSine {

  public:

  static bool startup(u32 bits, THeap * heap = nullptr);
  static void shutdown();

  static float ssin(s16 x);
  static float scos(s16 x);

  static inline float toRad(s16 x) {
    constexpr auto kRatio = (
      static_cast<float>(65536.0 / (M_PI * 2.0))
    );

    return (static_cast<float>(x) * kRatio);
  }

  static inline float toDeg(s16 x) {
    constexpr auto kRatio = (
      static_cast<float>(65536.0 / 360.0)
    );

    return (static_cast<float>(x) * kRatio);
  }

  static inline float toRad(float x) {
    constexpr auto kRatio = (
      1.0F / static_cast<float>(360.0 / (M_PI * 2.0))
    );

    return (x * kRatio);
  }

  static inline float toDeg(float x) {
    constexpr auto kRatio = (
      static_cast<float>(360.0 / (M_PI * 2.0))
    );

    return (x * kRatio);
  }

  static inline s16 fromRad(float x) {
    constexpr auto kRatio = (
      1.0F / static_cast<float>(65536.0 / (M_PI * 2.0))
    );

    return static_cast<s16>(x * kRatio);
  }

  static inline s16 fromDeg(float x) {
    constexpr auto kRatio = (
      1.0F / static_cast<float>(65536.0 / 360.0)
    );

    return static_cast<s16>(x * kRatio);
  }

  private:

  static float * sSinTable;
  static u16 sSinShift;

};

// -------------------------------------------------------------------------- //

#endif
