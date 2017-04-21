//
// Created by Padraic Calpin on 21/04/2017.
//

#include <exception>
#include <string>
#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "Eigen/Householder"
#include "lib/generation.h"
#include "lib/orthogonalisation.h"

Eigen::MatrixXcd orthoProjector(VectorList& states){
    unsigned int dim = states[0].rows();
    if(states.size() > dim){
        throw std::invalid_argument("More than " + std::to_string(dim) + " states is overcomplete. A comptutational decomposition suffices.");
    }
    Eigen::MatrixXcd cols(dim,states.size());
    for (VectorList::size_type i=0; i<states.size(); i++){
        cols.col(i) = states[i];
    }
    Eigen::HouseholderQR<Eigen::MatrixXcd> orthogonatron(cols);
    return orthogonatron.householderQ();
}
