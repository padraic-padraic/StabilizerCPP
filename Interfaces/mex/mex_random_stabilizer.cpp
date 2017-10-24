#include <complex>
#include <Eigen/Dense>
#include "lib/StabilizerMatrix.h"
#include "lib/utils.h"
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nrhs != 1 || !mxIsScalar(prhs[0]))
    {
        mexErrMsgIdAndTxt("random_stabilizer:nrhs", "1 input, nqubits, required");
    }
    if (nlhs != 1)
    {
        mexErrMsgIdAndTxt("random_stabilizer:mlhs", "1 output required");
    }
    unsigned int n_qubits, dim;
    n_qubits = (unsigned int) mxGetScalar(prhs[0]);
    dim = uiPow(2, n_qubits);
    plhs[0] = mxCreateDoubleMatrix((mwSize)dim, 1, mxCOMPLEX);
    double *out_r, *out_i;
    out_r = mxGetPr(plhs[0]);
    out_i = mxGetPi(plhs[0]);
    StabilizerMatrix m(n_qubits);
    bool linearly_independent = false;
    while(!linearly_independent){
        m.random();
        m.toCanonicalForm();
        linearly_independent = m.linearlyIndependent();
    }
    Eigen::VectorXcd state = m.stabilizerState();
    for (unsigned int i=0; i<dim; i++)
    {
        out_r[i] = real(state(i));
        out_i[i] = imag(state(i));
    }
    return;
}