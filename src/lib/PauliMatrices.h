//
// Created by Padraic Calpin on 03/04/2017.
//

#ifndef STABILIZERCPP_PAULIMATRICES_H
#define STABILIZERCPP_PAULIMATRICES_H

#include <complex>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "utils.h"

//typedef std::vector<Eigen::MatrixXcd, Eigen::aligned_allocator<Eigen::MatrixXcd>> MatrixList;

Eigen::MatrixXcd kroneckerProduct(Eigen::MatrixXcd& m1, Eigen::MatrixXcd& m2);
Eigen::MatrixXcd kroneckerProduct(const Eigen::MatrixXcd& m1, const Eigen::MatrixXcd& m2);
Eigen::MatrixXcd tensor(std::vector<Eigen::MatrixXcd, Eigen::aligned_allocator<Eigen::MatrixXcd>>& matrices);
Eigen::MatrixXcd identity(unsigned int dim);

const Eigen::MatrixXcd X((Eigen::Matrix2cd() << 0.,1.,1.,0.).finished());
const Eigen::MatrixXcd Y((Eigen::Matrix2cd() << 0., -1.*I, I, 0.).finished());
const Eigen::MatrixXcd Z((Eigen::Matrix2cd() << 1.,0.,0.,-1.).finished());
const Eigen::MatrixXcd Id = identity(2);

#endif //STABILIZERCPP_PAULIMATRICES_H
