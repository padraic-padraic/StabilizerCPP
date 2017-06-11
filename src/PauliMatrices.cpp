//
// Created by Padraic Calpin on 03/04/2017.
//
#include "lib/PauliMatrices.h"
#include <initializer_list>

Eigen::MatrixXcd kroneckerProduct(Eigen::MatrixXcd& m1, Eigen::MatrixXcd& m2){
    int rows = m1.rows(), cols=m1.cols();
    int bRows = m2.rows(), bCols=m2.cols();
    Eigen::MatrixXcd out(rows*bRows, cols*bCols);
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            out.block(bRows*i,bCols*j, bRows, bCols) = m1(i,j)*m2;
        }
    }
    return out;
}

Eigen::MatrixXcd kroneckerProduct(const Eigen::MatrixXcd& m1, const Eigen::MatrixXcd& m2){
    int rows = m1.rows(), cols=m1.cols();
    int bRows = m2.rows(), bCols=m2.cols();
    Eigen::MatrixXcd out(rows*bRows, cols*bCols);
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            out.block(bRows*i,bCols*j, bRows, bCols) = m1(i,j)*m2;
        }
    }
    return out;
}

Eigen::MatrixXcd tensor(MatrixList& matrices){
    Eigen::MatrixXcd out = matrices[0];
    for(auto it = (matrices.begin()+1); it!=matrices.end(); it++){
        out = kroneckerProduct(out, *it);
    }
    return out;
}

Eigen::MatrixXcd tensor(PauliList& matrices){
    Eigen::MatrixXcd out = matrices[0];
    for(auto it = (matrices.begin()+1); it!=matrices.end(); it++){
        out = kroneckerProduct(out, *it);
    }
    return out;
}


Eigen::MatrixXcd identity(unsigned int dim){
    Eigen::MatrixXcd out(dim, dim);
    out.setIdentity();
    return out;
}
