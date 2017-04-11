//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"
#include <fstream>

TEST(GeneratorTest, test_get_generators_2){
    std::vector<StabilizerGroup> groups = getStabilizerGroups(2);
    ASSERT_EQ(groups.size(), 15);
}

TEST(GeneratorTest, test_get_generators_3){
    std::vector<StabilizerGroup> groups = getStabilizerGroups(3);
    ASSERT_EQ(groups.size(), 135);
}

TEST(GeneratorTest, test_generators_commute){
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

TEST(GeneratorTest, test_file_reading){
    std::vector<StabilizerGroup> groups;
    std::string path = "../test/tests/fixtures/2qtest.generators";
    groups = groupsFromFile(path);
    std::cout << groups.size() << std::endl;
    ASSERT_EQ(groups.size(), 3);
    for (auto i = groups.begin(); i!=groups.end(); i++){
        ASSERT_EQ((*i).nGenerators(), 2);
        ASSERT_EQ((*i).order(), 4);
    }
    path = "someJunk";
    ASSERT_THROW(groupsFromFile(path), std::invalid_argument);
}

TEST(GeneratorTest, test_loaded_generators){
    std::string path = "../test/tests/fixtures/single_test.generators";
    std::vector<StabilizerGroup> groups;
    groups = groupsFromFile(path);
    ASSERT_EQ(groups.size(), 1);
    ASSERT_TRUE(groups[0].contains(SymplecticPauli("IX")));
    ASSERT_TRUE(groups[0].contains(SymplecticPauli("ZI")));
    ASSERT_TRUE(groups[0].contains(SymplecticPauli("ZX")));
    ASSERT_TRUE(groups[0].contains(SymplecticPauli("II")));
}