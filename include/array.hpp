
#ifndef INCLUDE_ARRAY_HPP
#define INCLUDE_ARRAY_HPP

#include <ultra64.h>

template<typename T>
class TArray {

  public:

  using TValue = T;
  using TIterator = TValue *;
  using TConstIterator = TValue const *;

  TArray() = default;
  TArray(u32 n);
  TArray(u32 n, TValue const & v);
  ~TArray();

  inline bool empty() const {
    return (mBegin == mEnd);
  }

  inline u32 size() const {
    return static_cast<u32>(mEnd - mBegin);
  }

  inline u32 capacity() const {
    return static_cast<u32>(mCap - mBegin);
  }

  inline TValue & operator[](u32 i) { return *(mBegin + i); }
  inline TValue const & operator[](u32 i) const { return *(mBegin + i); }

  inline TIterator begin() { return mBegin; }
  inline TConstIterator begin() const { return mBegin; }
  inline TConstIterator cbegin() const { return mBegin; }

  inline TIterator end() { return mBegin; }
  inline TConstIterator end() const { return mBegin; }
  inline TConstIterator cend() const { return mBegin; }

  void reserve(u32 n);
  void resize(u32 n, TValue const & v = TValue());
  void shrink();

  inline void clear() { mEnd = mBegin; }
  TIterator insert(TConstIterator it, TValue const & v, u32 n = 1);
  inline void push(TValue const & v) { insert(end(), v); }
  inline void pop() { erase(end() - 1); }
  TIterator erase(TConstIterator it);
  TIterator erase(TConstIterator first, TConstIterator last);

  private:

  TValue * mBegin { nullptr };
  TValue * mEnd { nullptr };
  TValue * mCap { nullptr };

};

template<typename T>
TArray<T>::TArray(u32 n) {
  reserve(n);
}

template<typename T>
TArray<T>::TArray(u32 n, TValue const & v) {
  resize(n, v);
}

template<typename T>
TArray<T>::~TArray() {
  delete[] mBegin;
}

template<typename T>
void TArray<T>::reserve(u32 n) {
  if (capacity() >= n) {
    return;
  }

  u32 old_size = size();
  TValue * begin = new TValue[n];

  for (u32 i = 0; i < old_size; ++i) {
    begin[i] = mBegin[i];
  }

  delete[] mBegin;
  mBegin = begin;
  mEnd = (mBegin + old_size);
  mCap = (mBegin + n);
}

template<typename T>
void TArray<T>::resize(u32 n, TValue const & v) {
  if (size() > n) {
    erase((begin() + n), end());
  } else if (size() < n) {
    insert(end(), v, (n - size()));
  }
}

template<typename T>
void TArray<T>::shrink() {
  u32 n = size();

  if (capacity() == n) {
    return;
  }

  TValue * begin = new TValue[n];

  for (u32 i = 0; i < n; ++i) {
    begin[i] = mBegin[i];
  }

  delete[] mBegin;
  mBegin = begin;
  mCap = mEnd = (mBegin + n);
}

template<typename T>
typename TArray<T>::TIterator
TArray<T>::insert(TConstIterator it, TValue const & v, u32 n) {
  u32 a = static_cast<u32>(it - mBegin);

  if (n == 0) {
    return (mBegin + a);
  }

  u32 b = static_cast<u32>(a + n);
  u32 old_size = size();
  u32 new_size = (old_size + n);
  u32 m = (old_size - b);
  TValue const * pv = &v;

  if (it <= pv && pv < mEnd) {
    pv += n;
  }

  if (capacity() >= new_size) {
    for (u32 i = 0; i < m; ++i) {
      mBegin[b + m + n - (i + 1)] = mBegin[b + m - (i + 1)];
    }

    for (u32 i = 0; i < n; ++i) {
      mBegin[a + i] = *pv;
    }

    mEnd += n;
  } else {
    TValue * begin = new TValue[new_size];

    for (u32 i = 0; i < a; ++i) {
      begin[i] = mBegin[i];
    }

    for (u32 i = 0; i < m; ++i) {
      begin[a + n + i] = mBegin[a + i];
    }

    for (u32 i = 0; i < n; ++i) {
      begin[a + i] = *pv;
    }

    delete[] mBegin;
    mBegin = begin;
    mEnd = (mBegin + new_size);
    mCap = (mBegin + new_size);
  }

  return (mBegin + b);
}

template<typename T>
typename TArray<T>::TIterator
TArray<T>::erase(TConstIterator it) {
  return erase(it, (it + 1));
}

template<typename T>
typename TArray<T>::TIterator
TArray<T>::erase(TConstIterator first, TConstIterator last) {
  if (first == last) {
    return last;
  }

  if (first == mBegin && last == mEnd) {
    clear();
    return end();
  }

  u32 a = static_cast<u32>(first - mBegin);
  u32 b = static_cast<u32>(last - mBegin);
  u32 n = (size() - b);

  for (u32 i = 0; i < n; ++i) {
    mBegin[a + i] = mBegin[b + i];
  }

  mEnd -= (b - a);
  return (mBegin + a);
}


#endif