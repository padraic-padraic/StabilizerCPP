#include <iostream>
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    SymplecticPauli PauliTest = SymplecticPauli(2, 0, 1);
//    SymplecticPauli PauliTest2 = SymplecticPauli(2, 0, 2);
//    SymplecticPauli PauliTest3 = PauliTest*PauliTest2;
//    std::cout<<PauliTest.NQubits()<<std::endl;
//    for(bInt i=0; i<PauliTest.NQubits(); i++){
//        std::cout<< PauliTest.XBits()[i] << "\t"<< PauliTest.ZBits()[i] << "\t"
//                 << PauliTest2.XBits()[i] << "\t" << PauliTest2.ZBits()[i] << "\t"
//                 << PauliTest3.XBits()[i] << "\t" << PauliTest3.ZBits()[i] << "\t"
//                 << std::endl;
//    }
//    std::vector<SymplecticPauli> gens = {SymplecticPauli(2,0,1), SymplecticPauli(2,0,2)};
//    StabilizerGroup test(gens);
//    std::cout << test.order() << std::endl;
//    std::cout << test.nGenerators() << std::endl;
    std::vector<SymplecticPauli> elements;
    for (int i=0; i<(2^4)+1; i++){
        elements.push_back(SymplecticPauli(2, i));
    }

    return 0;
}
