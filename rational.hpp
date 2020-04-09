#pragma once

//#include "extension.hpp"

#include <cmath>
#include <iostream>
#include <string>

#define ever ;;

template <typename BaseType>
BaseType pown(BaseType x, size_t n);

int gcd(int p, unsigned q)
{
  if(p == 0)
    return q;
  int x = std::abs(p);
  int y = q;
  if(x < y)
  {
    int tmp = y;
    y = x;
    x = tmp;
  }
  for(ever)
  {
    int gcd = x % y;
    if(gcd == 0)
      return y;
    x = y;
    y = gcd;
  }
  return q;
}

class rational
{
  int p;
  unsigned q;

  void rationalize()
  {
    int div = gcd(p, q);
    p /= div;
    q /= div;
  }
  public:
  rational() : p(0), q(1) {}

  rational(int _p, unsigned _q) : p(_p), q(_q)
  {
    if(q == 0)
    {
      throw std::domain_error("zero denominator");
    }
    rationalize();
  }

  rational(int n) : p(n), q(1u) {}

  rational(size_t n) : p(n), q(1u) {}

  rational(double d)
  {
    if((d == d) == false)
      throw std::domain_error("NaN");
    if(d == 0.0)
    {
      p = 0;
      q = 1u;
    }
    else
    {
      float f = d;
      unsigned u = *((unsigned *) &f);
      int exp = ((u >> 23) & 0xff);
      unsigned mant = (u & 0x07fffffu) | (1u << 23);
      if(exp < 127)
      {
        p = static_cast<int>((mant >> 23) * (d / d));
        q = pown(2, 127 - exp);
        rationalize();
      }
      else
      {
        p = d;
        q = 1u;
      }
    }
  }

  rational(const rational& another)
  {
    p = another.get_p();
    q = another.get_q();
  }

  rational& operator=(const rational& another)
  {
    p = another.get_p();
    q = another.get_q();
    return *this;
  }

  int get_p() const { return p; }
  unsigned get_q() const { return q; }

  rational operator+(const rational& another) const
  {
    int _p = another.get_p();
    int _q = another.get_q();
    rational result(p * _q + _p * q, q * _q);
    result.rationalize();
    return result;
  }

  rational& operator+=(const rational& another)
  {
    int _p = another.get_p();
    int _q = another.get_q();
    rational result(p * _q + _p * q, q * _q);
    result.rationalize();
    *this = result;
    return *this;
  }

  rational operator-(const rational& another) const
  {
    int _p = another.get_p();
    int _q = another.get_q();
    rational result(p * _q - _p * q, q * _q);
    result.rationalize();
    return result;
  }

  rational& operator-=(const rational& another)
  {
    int _p = another.get_p();
    int _q = another.get_q();
    rational result(p * _q - _p * q, q * _q);
    result.rationalize();
    *this = result;
    return *this;
  }

  rational operator*(const rational& another) const
  {
    rational result(p * another.get_p(), q * another.get_q());
    result.rationalize();
    return result;
  }

  rational& operator*=(const rational& another)
  {
    p *= another.get_p();
    q *= another.get_q();
    return *this;
  }

  rational operator/(const rational& another) const
  {
    if(another.get_p() == 0)
    {
      throw std::domain_error(std::to_string(__LINE__));
    }
    rational result(p * another.get_q(), q * another.get_p());
    result.rationalize();
    return result;
  }

  rational& operator/=(const rational& another)
  {
    if(another.get_p() == 0)
    {
      throw std::domain_error(std::to_string(__LINE__));
    }
    p *= another.get_q();
    q *= another.get_p();
    return *this;
  }

  bool operator==(const rational& another) const
  {
    return (p == another.get_p()) && (q == another.get_q());
  }

  bool operator==(const int& another) const
  {
    return (p == another) && (q == 1u);
  }

  bool operator!=(const rational& another) const
  {
    return (p != another.get_p()) || (q != another.get_q());
  }
};

