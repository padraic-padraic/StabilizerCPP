#include <iostream>
#include <algorithm>
#include <vector>
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"
#include "lib/utils.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
//    SymplecticPauli PauliTest = SymplecticPauli(2, 0, 1);
//    SymplecticPauli PauliTest2 = SymplecticPauli(2, 0, 2);
//    SymplecticPauli PauliTest3 = PauliTest*PauliTest2;
//    for(bInt i=0; i<PauliTest.NQubits(); i++){
//        std::cout<< PauliTest.XBits()[i] << "\t"<< PauliTest.ZBits()[i] << "\t"
//                 << PauliTest2.XBits()[i] << "\t" << PauliTest2.ZBits()[i] << "\t"
//                 << PauliTest3.XBits()[i] << "\t" << PauliTest3.ZBits()[i] << "\t"
//                 << std::endl;
//    }
//    std::cout<<PauliTest.NQubits()<<std::endl;
//    std::cout << PauliTest << std::endl;
//    std::cout << PauliTest2 << std::endl;
//    std::cout << PauliTest3 << std::endl;
    std::vector<SymplecticPauli> gens = {SymplecticPauli(2,0,1), SymplecticPauli(2,0,2)};
    StabilizerGroup test(gens);
    StabilizerGroup test2({SymplecticPauli(2,0,1), SymplecticPauli(2,0,2)});
    std::cout << test.order() << std::endl;
    std::cout << test.nGenerators() << std::endl;
    std::cout << test2.order() << std::endl;
    std::cout << test2.nGenerators() << std::endl;
    std::cout << (test == test2 ? "Woohoo" : "Oh") << std::endl;
    std::vector<StabilizerGroup> groups = getStabilizerGroups(3);
    std::cout << "Output has:" << groups.size()<< " elements." << std::endl;
    return 0;
}
