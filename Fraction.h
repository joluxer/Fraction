#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{

public:
  constexpr
  Fraction() noexcept
  : numerator(0), denominator(1)
  {}

  constexpr
  Fraction(int numerator_) noexcept
  : numerator(numerator_), denominator(1)
  {}

  Fraction(int numerator, int denominator) noexcept;

  Fraction(float) noexcept;

  const static Fraction ZERO;
  const static Fraction ONE;
  const static Fraction MAX_VALUE;
  const static Fraction MIN_VALUE;
  const static Fraction PI;

  static int gcd(int, int) noexcept;
  static int lcm(int, int) noexcept;

  // Negative
  Fraction operator-() noexcept;

  // Common operations
  Fraction operator+(const Fraction&) const noexcept;
  Fraction operator+(const int&) const noexcept;
  Fraction& operator+=(const Fraction&) noexcept;
  Fraction& operator+=(const int&) noexcept;

  Fraction operator-(const Fraction&) const noexcept;
  Fraction operator-(const int&) const noexcept;
  Fraction& operator-=(const Fraction&) noexcept;
  Fraction& operator-=(const int&) noexcept;

  Fraction operator*(const Fraction&) const noexcept;
  Fraction operator*(const int&) const noexcept;
  Fraction& operator*=(const Fraction&) noexcept;
  Fraction& operator*=(const int&) noexcept;

  Fraction operator/(const Fraction&) const;
  Fraction operator/(const int&) const;
  Fraction& operator/=(const Fraction&);
  Fraction& operator/=(const int&);

  int operator%(const Fraction&) const;
  int operator%(const int&) const;

  // Comparators
  bool operator==(const Fraction&) const noexcept;
  bool operator==(const int&) const noexcept;

  bool operator!=(const Fraction&) const noexcept;
  bool operator!=(const int&) const noexcept;

  bool operator>(const Fraction&) const noexcept;
  bool operator>(const int&) const noexcept;

  bool operator<(const Fraction&) const noexcept;
  bool operator<(const int&) const noexcept;

  bool operator>=(const Fraction&) const noexcept;
  bool operator>=(const int&) const noexcept;

  bool operator<=(const Fraction&) const noexcept;
  bool operator<=(const int&) const noexcept;

  double getDoubleValue() const noexcept;
  float getFloatValue() const noexcept;

  // numerator/denominator
  int numerator;
  int denominator;

private:
  // Utils methods
  static void checkDivisionByZero(int);
  static int mantissaToInteger(float, int*) noexcept;
  void simplify() noexcept;

  // Generic functional comparator
  template<typename ComparisonOperator>
  bool comparison(const Fraction &f2, ComparisonOperator operation) const noexcept;

  template<typename ComparisonOperator>
  bool comparison(const int &i1, ComparisonOperator operation) const noexcept;

  template<typename PlusMinusOperator>
  Fraction& commonOperation(const Fraction &f2, PlusMinusOperator operation, Fraction&) const noexcept;

  template<typename PlusMinusOperator>
  Fraction& commonOperation(const int &i1, PlusMinusOperator operation, Fraction&) const noexcept;
};

#endif
