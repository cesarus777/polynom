#include "extension.hpp"
#include "polynom.hpp"
#include "rational.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <time.h>

void test_ctors();
void test_value();
void test_arithm();
void test_integral();
void test_derivative();
void test_cout();

int main()
{
  std::cout << "What to test:\n"
            << "1 - test ctors\n"
            << "2 - test value\n"
            << "3 - test arithm\n"
            << "4 - test integral\n"
            << "5 - test darivative\n"
            << "6 - test cout\n"
            << "7 - test all" << std::endl;
  size_t test;
  std::cin >> test;
  std::srand(time(NULL));
  switch(test)
  {
    case 1:
      test_ctors();
      break;
    case 2:
      test_value();
      break;
    case 3:
      test_arithm();
      break;
    case 4:
      test_integral();
      break;
    case 5:
      test_derivative();
      break;
    case 6:
      test_cout();
      break;
    case 7:
      test_ctors();
      test_value();
      test_arithm();
      test_integral();
      test_derivative();
      test_cout();
      break;
    default:
      break;
  }
}

template <typename T> void test_ctors(std::string);
template <typename T> void test_value(std::string);
template <typename T> void test_arithm(std::string);
template <typename T> void test_integral(std::string);
template <typename T> void test_derivative(std::string);
template <typename T> void test_cout(std::string);

void test_ctors()
{
  std::cout << "\x1b[1;32mtesting ctors\x1b[0m" << std::endl;
  test_ctors<int>("int");
  test_ctors<double>("double");
  test_ctors<rational>("rational");
  std::cout << "\x1b[1;32mctors tested successfully\x1b[0m" << std::endl;
}

void test_value()
{
  std::cout << "\x1b[1;32mtesting value\x1b[0m" << std::endl;
  test_value<int>("int");
  test_value<double>("double");
  test_value<rational>("rational");
  std::cout << "\x1b[1;32mvalue tested successfully\x1b[0m" << std::endl;
}

void test_arithm()
{
  std::cout << "\x1b[1;32mtesting arithm\x1b[0m" << std::endl;
  test_arithm<int>("int");
  test_arithm<double>("double");
  test_arithm<rational>("rational");
  std::cout << "\x1b[1;32marithm tested successfully\x1b[0m" << std::endl;
}

void test_integral()
{
  std::cout << "\x1b[1;32mtesting integral\x1b[0m" << std::endl;
  test_integral<int>("int");
  test_integral<double>("double");
  test_integral<rational>("rational");
  std::cout << "\x1b[1;32mintegral tested successfully\x1b[0m" << std::endl;
}

void test_derivative()
{
  std::cout << "\x1b[1;32mtesting derivative\x1b[0m" << std::endl;
  test_derivative<int>("int");
  test_derivative<double>("double");
  test_derivative<rational>("rational");
  std::cout << "\x1b[1;32mderivative tested successfully\x1b[0m" << std::endl;
}

void test_cout()
{
  std::cout << "\x1b[1;32mtesting cout\x1b[0m" << std::endl;
  test_cout<int>("int");
  test_cout<double>("double");
  test_cout<rational>("rational");
  std::cout << "\x1b[1;32mcout tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_ctors(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  std::cout << "testing ctor without args" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    Polynom<T> P;
    if(P[0] == 0)
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "testing ctor with one arg" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    T r = static_cast<T>(std::rand());
    Polynom<T> P(r);
    if(P[0] == r)
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "testing ctor with two args" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    T r = static_cast<T>(std::rand());
    int n = std::rand() % 11;
    Polynom<T> P(r, n);
    for(int i = 0; i < n; ++i)
    {
      if(P[i] == 0)
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }
    if(P[n] == r)
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "testing ctor with vector as arg" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    std::vector<T> v;
    int n = std::rand() % 11;
    for(int i = 0; i < n; ++i)
      v.push_back(static_cast<T>(std::rand()));

    Polynom<T> P(v);
    for(int i = 0; i < n; ++i)
    {
      if(P[i] == v[i])
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  std::cout << "testing copy ctor" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    std::vector<T> v;
    int n = std::rand() % 11;
    for(int i = 0; i < n; ++i)
      v.push_back(static_cast<T>(std::rand()));

    Polynom<T> P(v);
    for(int i = 0; i < n; ++i)
    {
      if(P[i] == v[i])
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }

    Polynom<T> P2(P);
    for(int i = 0; i < n; ++i)
    {
      if(P2[i] == v[i])
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  std::cout << "testing move ctor" << std::endl;
  for(size_t i = 0; i < 5; ++i)
  {
    std::vector<T> v;
    int n = std::rand() % 11;
    for(int i = 0; i < n; ++i)
      v.push_back(static_cast<T>(std::rand()));

    Polynom<T> P(v);
    for(int i = 0; i < n; ++i)
    {
      if(P[i] == v[i])
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }

    Polynom<T> P2(std::move(P));
    if(P.gsize() != 0)
    {
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; ++i)
    {
      if(P2[i] == v[i])
        continue;
      std::cout << "bad test" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_value(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  std::vector<T> v;
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  Polynom<T> P(v);

  if(P.value(0) != P[0])
  {
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(P.value(static_cast<T>(1)) != static_cast<T>(66))
  {
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(P.value(static_cast<T>(2)) != static_cast<T>(4083))
  {
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_arithm(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  std::cout << "testing sum" << std::endl;
  std::vector<T> v;
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  Polynom<T> P1(v);

  std::reverse(v.begin(), v.end());
  Polynom<T> P2(v);

  Polynom<T> P(P1 + P2);

  for(int i = 0; i < 11; ++i)
  {
    if(P[i] == static_cast<T>(12))
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "testing sub" << std::endl;
  v.clear();
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  P1 = Polynom<T>(v);

  std::reverse(v.begin(), v.end());
  P2 = Polynom<T>(v);

  P = P1 - P2;

  for(int i = 0; i < 11; ++i)
  {
    if(P[i] == static_cast<T>(10 - 2 * i))
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "testing mul" << std::endl;
  v.clear();
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  P1 = Polynom<T>(v);

  std::reverse(v.begin(), v.end());
  P2 = Polynom<T>(v);

  P = P1 * P2;

  for(int i = 0; i < 11; ++i)
  {
    T check_value = 0;
    for(int j = 0; j < i + 1; ++j)
      check_value += v[10 - j] * v[i - j];

    if(P[i] == static_cast<T>(check_value))
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_integral(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  std::vector<T> v;
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  Polynom<T> P(v);

  Polynom<T> Int = std::move(P.Integral());

  if(Int[0] != static_cast<T>(0))
  {
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < 11; ++i)
  {
    if(Int[i + 1] == static_cast<T>(v[i] / (i + 1)))
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_derivative(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  std::vector<T> v;
  for(int i = 0; i < 11; ++i)
    v.push_back(static_cast<T>(11 - i));

  Polynom<T> P(v);

  Polynom<T> der = std::move(P.Derivative());

  for(int i = 1; i < 11; ++i)
  {
    if(der[i - 1] == static_cast<T>(v[i] * i))
      continue;
    std::cout << "bad test" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

template <typename T> void test_cout(std::string type)
{
  std::cout << "\x1b[1mtesting " << type << "\x1b[0m" << std::endl;

  size_t n = 0;
  std::cout << "input number of coeffs" << std::endl;
  std::cin >> n;


  std::cout << "input " << n << " coeffs" << std::endl;
  std::vector<T> v;
  for(size_t i = 0; i < n; ++i)
  {
    double tmp;
    std::cin >> tmp;
    v.push_back(T(tmp));
  }

  Polynom<T> p(v);
  std::cout << "your polynom is :\n" << p << std::endl;

  std::cout << "\x1b[1m" << type << " tested successfully\x1b[0m" << std::endl;
}

