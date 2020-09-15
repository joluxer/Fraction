#include "Fraction.h"

#include <climits>
#include <cmath>
#include <functional>

Fraction::Fraction(int numerator, int denominator) noexcept
: numerator(numerator), denominator(denominator)
{
  this->simplify();
}

/**
 *  Explanation:
 *
 *  We get the mantissa (mt), the exponent (n)
 *  that represents the float number and the
 *  number of decimal digits of the mantissa (m)
 *
 *  So we turn it in the form:
 *
 *  number = ((10^m * mt) * 2^n) / (10 ^ m)
 *
 * So, before calculate the exponentiations,
 * we simplify z = (2^n)/(10^m) by turning it doing:
 *
 * h = min(n, m)
 *
 * z = (2^(n-h))/(5^h * 10^(m-h))
 *
 * Then we'll have the numerator and the denominator,
 * that we simplify by dividing them by them GCD.
 *
 */
Fraction::Fraction(float number) noexcept
{
  float mantissa;

  int exponent, numerator, denominator, h;

  // Mantissa of the floating number
  mantissa = frexp(number, &exponent);

  // E.g. turns 0.123 into 123
  numerator = mantissaToInteger(mantissa, &denominator);

  h = ::std::min(denominator, exponent);

  // Simplify (2^n)/(10^m)
  this->numerator = numerator * pow(2, exponent - h);
  this->denominator = pow(5, h) * pow(10, denominator - h);

  this->simplify();
}

const Fraction Fraction::ZERO(0);
const Fraction Fraction::ONE(1);
const Fraction Fraction::MAX_VALUE(INT_MAX);
const Fraction Fraction::MIN_VALUE(INT_MIN);
const Fraction Fraction::PI(3126535, 995207);

template<typename ComparisonOperator>
bool Fraction::comparison(const Fraction &f2, ComparisonOperator operation) const noexcept
{

  if (this->denominator == f2.denominator)
  {
    return operation(this->numerator, f2.numerator);
  }

  int lcm = this->lcm(this->denominator, f2.denominator);

  return operation(this->numerator * (lcm / this->denominator), f2.numerator * (lcm / f2.denominator));
}

template<typename ComparisonOperator>
bool Fraction::comparison(const int &i1, ComparisonOperator operation) const noexcept
{

  if (this->denominator == 1)
  {
    return operation(this->numerator, i1);
  }

  return operation(this->numerator, i1 * this->denominator);
}

template<typename PlusMinusOperator>
Fraction& Fraction::commonOperation(const Fraction &f2, PlusMinusOperator operation, Fraction& result) const noexcept
{

  auto lcmNumber = lcm(this->denominator, f2.denominator);

  result = Fraction(operation(this->numerator * (lcmNumber / this->denominator), f2.numerator * (lcmNumber / f2.denominator)), lcmNumber);

  result.simplify();

  return result;
}

template<typename PlusMinusOperator>
Fraction& Fraction::commonOperation(const int &i1, PlusMinusOperator operation, Fraction& result) const noexcept
{
  result = Fraction(operation(this->numerator, i1 * this->denominator), this->denominator);

  result.simplify();

  return result;
}

Fraction Fraction::operator-() noexcept
{
  return Fraction(-this->numerator, this->denominator);
}

Fraction Fraction::operator+(const Fraction &fraction) const noexcept
{
  Fraction result;
  return this->commonOperation(fraction, std::plus<int>(), result);
}

Fraction Fraction::operator+(const int &integer) const noexcept
{
  Fraction result;
  return this->commonOperation(integer, std::plus<int>(), result);
}

Fraction& Fraction::operator+=(const Fraction &fraction) noexcept
{
  return this->commonOperation(fraction, std::plus<int>(), *this);
}

Fraction& Fraction::operator+=(const int &integer) noexcept
{
  return this->commonOperation(integer, std::plus<int>(), *this);
}

Fraction Fraction::operator-(const Fraction &fraction) const noexcept
{
  Fraction result;
  return this->commonOperation(fraction, std::minus<int>(), result);
}

Fraction Fraction::operator-(const int &integer) const noexcept
{
  Fraction result;
  return this->commonOperation(integer, std::minus<int>(), result);
}

Fraction& Fraction::operator-=(const Fraction &fraction) noexcept
{
  return this->commonOperation(fraction, std::minus<int>(), *this);
}

Fraction& Fraction::operator-=(const int &integer) noexcept
{
  return this->commonOperation(integer, std::minus<int>(), *this);
}

Fraction Fraction::operator*(const Fraction &fraction) const noexcept
{
  Fraction result(this->numerator * fraction.numerator, this->denominator * fraction.denominator);

  result.simplify();

  return result;
}

Fraction Fraction::operator*(const int &integer) const noexcept
{
  Fraction result(this->numerator * integer, this->denominator);

  result.simplify();

  return result;
}

Fraction& Fraction::operator*=(const Fraction &fraction) noexcept
{
  numerator = this->numerator * fraction.numerator;
  denominator = this->denominator * fraction.denominator;

  simplify();

  return *this;
}

Fraction& Fraction::operator*=(const int &integer) noexcept
{
  numerator = this->numerator * integer;

  simplify();

  return *this;
}

Fraction Fraction::operator/(const Fraction &fraction) const
{
  checkDivisionByZero(fraction.numerator);

  Fraction result(this->numerator * fraction.denominator, this->denominator * fraction.numerator);

  result.simplify();

  return result;
}

Fraction Fraction::operator/(const int &integer) const
{
  checkDivisionByZero(integer);

  Fraction result(this->numerator, this->denominator * integer);

  result.simplify();

  return result;
}

Fraction& Fraction::operator/=(const Fraction &fraction)
{
  checkDivisionByZero(fraction.numerator);

  numerator = this->numerator * fraction.denominator;
  denominator = this->denominator * fraction.numerator;

  simplify();

  return *this;
}

Fraction& Fraction::operator/=(const int &integer)
{
  checkDivisionByZero(integer);

  denominator = this->denominator * integer;

  simplify();

  return *this;
}

int Fraction::operator%(const Fraction &fraction) const
{
  checkDivisionByZero(fraction.numerator);

  Fraction division = (*this) / fraction;

  int integer = (int) division.getFloatValue();

  integer = division.denominator * integer;

  return division.numerator - integer;
}

int Fraction::operator%(const int &integer) const
{
  checkDivisionByZero(integer);

  Fraction division = (*this) / integer;

  int integerPart = (int) division.getFloatValue();

  integerPart = division.denominator * integerPart;

  return division.numerator - integerPart;
}

bool Fraction::operator==(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::equal_to<int>());
}

bool Fraction::operator==(const int &integer) const noexcept
{
  return this->comparison(integer, std::equal_to<int>());
}

bool Fraction::operator!=(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::not_equal_to<int>());
}

bool Fraction::operator!=(const int &integer) const noexcept
{
  return this->comparison(integer, std::not_equal_to<int>());
}

bool Fraction::operator>(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::greater<int>());
}

bool Fraction::operator>(const int &integer) const noexcept
{
  return this->comparison(integer, std::greater<int>());
}

bool Fraction::operator<(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::less<int>());
}

bool Fraction::operator<(const int &integer) const noexcept
{
  return this->comparison(integer, std::less<int>());
}

bool Fraction::operator>=(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::greater_equal<int>());
}

bool Fraction::operator>=(const int &integer) const noexcept
{
  return this->comparison(integer, std::greater_equal<int>());
}

bool Fraction::operator<=(const Fraction &fraction) const noexcept
{
  return this->comparison(fraction, std::less_equal<int>());
}

bool Fraction::operator<=(const int &integer) const noexcept
{
  return this->comparison(integer, std::less_equal<int>());
}

double Fraction::getDoubleValue() const noexcept
{
  return this->numerator / (double) this->denominator;
}

float Fraction::getFloatValue() const noexcept
{
  return this->numerator / (float) this->denominator;
}

int Fraction::gcd(int a, int b)  noexcept
{
  for (;;)
  {

    if (a == 0)
    {
      return b;
    }

    b %= a;

    if (b == 0)
    {
      return a;
    }

    a %= b;
  }

  return 1;
}

int Fraction::lcm(int a, int b) noexcept
{
  int gcdNumber = gcd(a, b);

  return gcdNumber ? (a / gcdNumber * b) : 0;
}

int Fraction::mantissaToInteger(float mantissa, int *n) noexcept
{
  *n = 0;

  while (mantissa != (int) mantissa)
  {
    mantissa *= 10;
    *n += 1;
  }

  return mantissa;
}

void Fraction::simplify() noexcept
{
  int gcd = this->gcd(this->numerator, this->denominator);

  this->numerator /= gcd;
  this->denominator /= gcd;

  if (this->denominator < 0)
  {
    this->numerator = -this->numerator;
    this->denominator = -this->denominator;
  }
}
