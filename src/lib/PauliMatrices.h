//
// Created by Padraic Calpin on 03/04/2017.
//

#ifndef STABILIZERCPP_PAULIMATRICES_H
#define STABILIZERCPP_PAULIMATRICES_H

#include <complex>
#include "Eigen/Dense"
#include "utils.h"

const Eigen::MatrixXcd X((Eigen::Matrix2cd() << 0,1,1,0).finished());
const Eigen::MatrixXcd Y((Eigen::Matrix2cd() << 0, -1.*I, 1.*I, 0).finished());
const Eigen::MatrixXcd Z((Eigen::Matrix2cd() << 1,0,0,-1).finished());

Eigen::MatrixXcd kroneckerProduct(std::vector<Eigen::MatrixXcd> matrices);
Eigen::MatrixXcd kroneckerProduct(Eigen::MatrixXcd m1, Eigen::MatrixXcd m2);

#endif //STABILIZERCPP_PAULIMATRICES_H
