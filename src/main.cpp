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
    if (test==test2){
        std::cout << "Woohoo" << std::endl;
    } else {
        std::cout << "Oh" << std::endl;
    }
    std::vector<StabilizerGroup> groups;
    std::vector<SymplecticPauli> elements;
    for (unsigned int i=1; i<uiPow(2,4); i++){
        elements.push_back(SymplecticPauli(2, i));
    }
    std::cout << elements.size() << std::endl;
    std::vector<bool> mask = getMaskArray(elements.size(), 2);
    do {
        StabilizerGroup candidate;
        for(std::vector<bool>::size_type i=0; i<mask.size(); i++){
            if (mask[i]){
                candidate.add(elements[i]);
            }
        }
        std::cout << candidate.order() << std::endl;
        if (candidate.nGenerators()!=2){
            continue;
        }
        if (groups.size()==0){
            groups.push_back(candidate);
            continue;
        }
        if (std::none_of(groups.begin(), groups.end(), [&candidate](StabilizerGroup& g){return candidate==g;})){
            groups.push_back(candidate);
        }
    } while(std::next_permutation(mask.begin(), mask.end()));
    std::cout << groups.size() << std::endl;
    return 0;
}
