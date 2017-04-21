//
// Created by Padraic Calpin on 21/04/2017.
//

#ifndef STABILIZERCPP_ORTHOGONALISATION_H
#define STABILIZERCPP_ORTHOGONALISATION_H

#include <vector>
#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "Eigen/Householder"
#include "generation.h"

Eigen::MatrixXcd orthoProjector(VectorList& states);

#endif //STABILIZERCPP_ORTHOGONALISATION_H
