//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"

TEST(GeneratorTest, test_get_generators_2){
    std::vector<StabilizerGroup> groups = getStabilizerGroups(2);
    ASSERT_EQ(groups.size(), 15);
}

TEST(GeneratorTest, test_get_generators_3){
    std::vector<StabilizerGroup> groups = getStabilizerGroups(3);
    ASSERT_EQ(groups.size(), 135);
}

TEST(GenratorTest, test_generators_commute){
    std::vector<StabilizerGroup> groups = getStabilizerGroups(2);
    std::vector<SymplecticPauli> gens(groups[0].nGenerators());
    unsigned int j=0;
    for (auto i=groups.begin(); i!=groups.end(); i++){
        for (auto k=(*i).generators.begin(); k!=(*i).generators.end(); k++){
            gens[j] = *k;
            j++;
        }
        EXPECT_TRUE(commutivityTest(gens));
        j=0;
    }
}