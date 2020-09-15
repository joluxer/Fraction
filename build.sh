#!/bin/sh

g++ main.cpp Fraction.cpp FractionException.cpp FractionException.h -o fraction-demo-exception
g++ main.cpp Fraction.cpp FractionAssert.cpp FractionException.h -o fraction-demo-assert
