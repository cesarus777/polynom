#pragma once

#include "extension.hpp"

#include <stdexcept>
#include <vector>

template <typename BaseType>
class Polynom
{
  private:
    BaseType *data;
    size_t size;
  public:
    Polynom()
    {
      size = 1;
      data = new BaseType();
    }

    Polynom(BaseType a)
    {
      size = 1;
      data = new BaseType(a);
    }

    Polynom(BaseType a, int n)
    {
      size = n + 1;
      data = new BaseType[size]();
      data[n] = a;
    }

    Polynom(std::vector<BaseType> &C)
    {
      size = C.size();
      data = new BaseType[size];
      for(size_t i = 0; i < size; ++i)
      {
        data[i] = C[i];
      }
    }

    Polynom(Polynom<BaseType>& P)
    {
      size = P.size;
      data = new BaseType[size]();
      for(size_t i = 0; i < size; ++i)
        data[i] = P[i];
    }

    Polynom<BaseType>& operator=(const Polynom<BaseType>& P)
    {
      if(size < P.size)
      {
        delete [] data;
        size = P.size;
        data = new BaseType[size](0);
      }
      for(size_t i = 0; i < size; ++i)
      {
        data[i] = P[i];
      }
    }

    Polynom(Polynom<BaseType>&& P)
    {
      size = P.size;
      P.size = 0;
      data = P.data;
      P.data = NULL;
    }

    Polynom<BaseType>& operator=(Polynom<BaseType>&& P)
    {
      delete [] data;
      size = P.size;
      data = P.data;
      P.size = 0;
      P.data= NULL;
      return *this;
    }

    ~Polynom()
    {
      delete [] data;
    }

    constexpr size_t gsize() const { return size; }

    BaseType value(BaseType x) const
    {
      BaseType res = 0;
      for(size_t i = 0; i < size; ++i)
      {
        res += data[i] * pown(x, i);
      }
      return res;
    }

    BaseType& operator[](size_t i) const
    {
      if(i > size - 1)
        throw std::out_of_range("operator[]");
      else
        return data[i];
    }

    Polynom operator+(Polynom<BaseType>& P) const
    {
      bool P_larger = (P.size > size);
      size_t big_size = P_larger ? P.size : size;
      Polynom res(0, big_size - 1);
      for(size_t i = 0; i < big_size; ++i)
      {
        res[i] = data[i] + P[i];
      }
      return res;
    }

    Polynom operator-(Polynom<BaseType>& P) const
    {
      bool P_larger = (P.size > size);
      size_t big_size = P_larger ? P.size : size;
      Polynom res(0, big_size - 1);
      for(size_t i = 0; i < big_size; ++i)
      {
        res[i] = data[i] - P[i];
      }
      return res;
    }

    Polynom operator*(Polynom<BaseType>& P) const
    {
      Polynom<BaseType> res(0, size + P.size - 2);
      for(size_t i = 0; i < size; i++)
        for(size_t j = 0; j < P.size; j++)
          res[i + j] += data[i] * P.data[j];
      return res;
    }

    Polynom Integral() const
    {
      Polynom<BaseType> res(0, size);
      res[0] = 0;
      for(size_t i = 0; i < size; i++)
        res[i + 1] = data[i] / (i + 1);
      return res;
    }

    Polynom Derivative() const
    {
      Polynom<BaseType> res(0, size - 2);
      for(size_t i = 0; i < res.size; i++)
        res[i] = data[i + 1] * (i + 1);
      return res;
    }
};

