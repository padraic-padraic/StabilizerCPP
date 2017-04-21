//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerMatrix.h"
#include "lib/generation.h"

TEST(GeneratorTest, test_get_generators_2){
    std::vector<StabilizerMatrix> groups = getStabilizerGroups(2);
    ASSERT_EQ(groups.size(), 15);
}

TEST(GeneratorTest, test_get_generators_3){
    std::vector<StabilizerMatrix> groups = getStabilizerGroups(3);
    ASSERT_EQ(groups.size(), 135);
}

TEST(GeneratorTest, test_generators_commute){
    std::vector<StabilizerMatrix> groups = getStabilizerGroups(2);
    std::vector<SymplecticPauli> gens(groups[0].NQubits());
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
    std::vector<StabilizerMatrix> groups;
    std::string path = "../test/tests/fixtures/2qtest.generators";
    groups = groupsFromFile(path);
    std::cout << groups.size() << std::endl;
    ASSERT_EQ(groups.size(), 3);
    for (auto i = groups.begin(); i!=groups.end(); i++){

    }
    path = "someJunk";
    ASSERT_THROW(groupsFromFile(path), std::invalid_argument);
}

TEST(GeneratorTest, test_loaded_generators) {
    std::string path = "../test/tests/fixtures/single_test.generators";
    std::vector<StabilizerMatrix> groups;
    groups = groupsFromFile(path);
    ASSERT_EQ(groups.size(), 2);
    ASSERT_TRUE(groups[0].linearlyIndependent());
    ASSERT_FALSE(groups[1].linearlyIndependent());
}

TEST(GeneratorTest, test_save_and_load) {
    std::string path="../test/tests/fixtures/full_save_load.generators";
    std::vector<StabilizerMatrix> groups;
    groups = getStabilizerGroups(2);
    saveGroups(path, groups);
    std::vector<StabilizerMatrix> foundGroups;
    foundGroups = groupsFromFile(path);
    for (std::vector<StabilizerMatrix>::size_type i=0; i!=groups.size(); i++){
        ASSERT_EQ(groups[i], foundGroups[i]);
    }
}

TEST(GeneratorTest, test_state){
    Eigen::VectorXcd fixture(4);
    fixture << 1.,0.,0.,0.;
    StabilizerMatrix group({SymplecticPauli("IZ"), SymplecticPauli("ZI")});
    group.toCanonicalForm();
    Eigen::VectorXcd out (4);
    out = group.stabilizerState();
    for(Eigen::VectorXcd::Index i=0; i<fixture.rows(); i++){
        ASSERT_EQ(fixture(i), out(i));
    }
}

TEST(GeneratorTest, test_save_and_load_state){
    std::string path="../test/tests/fixtures/full_save_load.states";
    VectorList states;
    states = getStabilizerStates(2);
    saveStates(path, states);
    VectorList foundStates;
    foundStates = statesFromFile(path);
    Eigen::VectorXcd::Index i;
    for(VectorList::size_type j=0; j<states.size(); j++){
        for(i=0; i<states[j].rows(); i++){
            ASSERT_DOUBLE_EQ(states[j](i).real(), foundStates[j](i).real());
            ASSERT_DOUBLE_EQ(states[j](i).imag(), foundStates[j](i).imag());
        }
    }
}
