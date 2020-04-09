#pragma once

#include "rational.hpp"

#include <iostream>

template <typename BaseType>
class Polynom;

std::ostream& operator<<(std::ostream& os, const rational& r)
{
  os << r.get_p() << '/' << r.get_q();
  return os;
}

template <typename BaseType>
std::ostream& operator<<(std::ostream& os, const Polynom<BaseType>& P)
{
  const size_t size = P.gsize();
  bool first_printed = false;
  if(P[0] != static_cast<BaseType>(0))
  {
    os << P[0];
    first_printed = true;
  }
  for(size_t i = 1; i < size; ++i)
  {
    if(P[i] != static_cast<BaseType>(0))
    {
      if(first_printed)
        os << " + ";
      if(P[i] == static_cast<BaseType>(1))
      {
        os << "x^" << i;
        first_printed = true;
        continue;
      }
      os << P[i] << " * x^" << i;
      first_printed = true;
    }
  }
  return os;
}

template <typename BaseType>
BaseType pown(BaseType x, size_t n)
{
  if(n == 0)
    return static_cast<BaseType>(1);
  if(x == 0)
    return x;
  BaseType res = static_cast<BaseType>(1);
  while(n > 0)
  {
    if((n % 2) == 0)
    {
      x *= x;
      n /= 2;
    }
    else
    {
      res *= x;
      n -= 1;
    }
  }
  return res;
}

