#include <iostream>
#include <SymplecticPauli.h>
#include "StabilizerGroup.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SymplecticPauli PauliTest = SymplecticPauli(2, 1, 2);
    SymplecticPauli PauliTest2 = SymplecticPauli(2, 2, 2);
    SymplecticPauli PauliTest3 = PauliTest*PauliTest2;
    std::cout<<PauliTest.NQubits()<<std::endl;
    for(bInt i=0; i<PauliTest.NQubits(); i++){
        std::cout<< PauliTest.XBits()[i] << "\t"<< PauliTest.ZBits()[i] << "\t"
                 << PauliTest2.XBits()[i] << "\t" << PauliTest2.ZBits()[i] << "\t"
                 << PauliTest3.XBits()[i] << "\t" << PauliTest3.ZBits()[i] << "\t"
                 << std::endl;
    }
    return 0;
}