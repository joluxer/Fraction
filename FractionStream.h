/*
 * FractionStream.h
 *
 *  Created on: 15.09.2020
 *      Author: lode
 */

#include "Fraction.h"

#include <ostream>

inline
std::ostream& operator<<(std::ostream &strm, const Fraction &fraction)
{
  return strm << fraction.numerator << "/" << fraction.denominator;
}

