#include <complex>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include "lib/generation.h"
#include "lib/StabilizerMatrix.h"
#include "lib/utils.h"
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nrhs != 2 || !mxIsScalar(prhs[0]) || !mxIsScalar(prhs[1]))
    {
        mexErrMsgIdAndTxt("random_stabilizer:nrhs", "1 input, nqubits, required");
    }
    if (nlhs != 1)
    {
        mexErrMsgIdAndTxt("random_stabilizer:mlhs", "1 output required");
    }
    unsigned int n_qubits, n_states, dim;
    n_qubits = (unsigned int) mxGetScalar(prhs[0]);
    n_states = (unsigned int) mxGetScalar(prhs[1]);
    dim = uiPow(2, n_qubits);
    plhs[0] = mxCreateDoubleMatrix((mwSize)dim, n_states, mxCOMPLEX);
    double *out_r, *out_i;
    out_r = mxGetPr(plhs[0]);
    out_i = mxGetPi(plhs[0]);
    VectorList states = getStabilizerStates(n_qubits, n_states);
    unsigned int state_counter = 0;
    for (auto j = states.cbegin(); j!=states.cend(); j++)
    {
        for (unsigned int i=0; i<dim; i++)
        {
            out_r[i][state_counter] = real(*j(i));
            out_i[i][state_counter] = imag(*j(i));
        }
        state_counter++;
    }
    return;
}