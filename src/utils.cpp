//
// Created by Padraic Calpin on 29/03/2017.
//

#include <algorithm>
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
    return n <= 1 ? 1 : factorial(n - 1) * n;
}

unsigned int nCr(unsigned int n, unsigned int r){
    return factorial(n)/(factorial(n-r)*factorial(r));
}

unsigned int nStabilizers(unsigned int nQubits){
    unsigned int out = uiPow(2, nQubits);
    for (unsigned int i=0; i<nQubits; i++){
        out *= (uiPow(2, nQubits-i)+1);
    }
    return out;
}

std::vector<bool> getMaskArray(size_t n, unsigned int r){
    std::vector<bool> mask(n, false);
    std::fill(mask.end()-r, mask.end(), true);
    return mask;
}


