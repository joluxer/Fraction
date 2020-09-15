/*
 * FractionException.cpp
 *
 *  Created on: 15.09.2020
 *      Author: lode
 */

#include "Fraction.h"
#include "FractionException.h"

#include <string>

void Fraction::checkDivisionByZero(int possibleZero)
{

  if (possibleZero == 0)
    throw FractionException("Error: Division by zero");
}
