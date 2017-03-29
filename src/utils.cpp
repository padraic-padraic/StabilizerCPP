//
// Created by Padraic Calpin on 29/03/2017.
//

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