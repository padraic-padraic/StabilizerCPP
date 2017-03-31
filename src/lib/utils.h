//
// Created by Padraic Calpin on 29/03/2017.
//

#ifndef STABILIZERCPP_UTILS_H
#define STABILIZERCPP_UTILS_H

#include <vector>
#include "SymplecticPauli.h"


unsigned int uiPow(unsigned int base, unsigned int exp);

unsigned int factorial(unsigned int n);

unsigned int nCr(unsigned int n, unsigned int r);

std::vector<bool> getMaskArray(size_t n, unsigned int r);

#endif //STABILIZERCPP_UTILS_H
