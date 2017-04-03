//
// Created by Padraic Calpin on 03/04/2017.
//
#include "lib/PauliMatrices.h"

Eigen::MatrixXcd kroneckerProduct(Eigen::MatrixXcd& m1, Eigen::MatrixXcd& m2){
    Eigen::MatrixXcd out(m1.rows()*m2.rows(), m1.cols()*m2.cols());
    int blockRows = m2.rows(), blockCols=m2.cols();
    for (int i=0; i<m1.rows(); i++){
        for (int j=0; j<m1.cols(); j++){
            out.block(i,j, blockRows, blockCols) = m1(i,j)*m2;
        }
    }
    return out;
}

Eigen::MatrixXcd kroneckerProduct(std::vector<Eigen::MatrixXcd>& matrices){
    Eigen::MatrixXcd out = matrices[0]
    for(auto i=matrices.begin()+1; i!=matrices.end(); i++){
        out = kroneckerProduct(out, *i);
    }
    return out;
}
