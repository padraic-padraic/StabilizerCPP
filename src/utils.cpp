//
// Created by Padraic Calpin on 29/03/2017.
//

#include <algorithm>
#include <vector>
#include "lib/SymplecticPauli.h"
#include "lib/utils.h"

unsigned int uiPow(unsigned int base, unsigned int exp) {
    unsigned int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

unsigned int factorial(unsigned int n) {
    if (n<=1) {
        return 1;
    } else {
        return factorial(n-1)*n;
    }
}

unsigned int nCr(unsigned int n, unsigned int r){
    return factorial(n)/(factorial(n-r)*factorial(r));
}

std::vector<bool> getMaskArray(size_t n, unsigned int r){
    std::vector<bool> mask(n, false);
    std::fill(mask.end()-r, mask.end(), true);
    return mask;
}

