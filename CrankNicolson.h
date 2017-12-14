
#include "Parameters.h"
using namespace MODPARAMS;

inline void CrankNicolson ( NVECTOR *flat_C, double leftdiags[], double rightdiags[] ) {

  NMATRIX R;
  NMATRIX L;
  NVECTOR boundary;

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
        if (i == j) {
            if (zindex(j) != 0) {
              R(i,j) = rightdiags[0];
              L(i,j) = leftdiags[0];
            }
            else { // remove rz from diagonal dependance for boundary condition
              R(i,j) = noflux_diagonal_right;
              L(i,j) = noflux_diagonal_left;
            }
        }
        if (i + 1 == j) {
            if (zindex(j) != nz - 1) {// positive z boundary
              R(i,j) = rightdiags[5];
              L(i,j) = leftdiags[5];
            }
            else {
              boundary(i) += (rightdiags[5] - leftdiags[5]) * BC[5];
            }
        }
        if (i - 1 == j) {
            if (zindex(j) != 0) {// negative z boundary
              L(i,j) = leftdiags[6];
              R(i,j) = rightdiags[6];
            } // subdiagonal and superdiagonal for z are zero here, no BC needed
        }
        if (i + (nz - 1) == j){
            if (yindex(j) != ny - 1){
              R(i,j) = rightdiags[3];
              L(i,j) = leftdiags[3];
            }
            else {
              boundary(i) += (rightdiags[3] - leftdiags[3]) * BC[3];
            }
        }
        if (i - (nz - 1) == j) {
            if (yindex(j) != 0) {
              R(i,j) = rightdiags[4];
              L(i,j) = leftdiags[4];
            }
            else {
              boundary(i) += (rightdiags[4] - leftdiags[4]) * BC[2];
            }
        }
        if (i + (nz*ny - 1) == j) {
            if (xindex(j) != nx - 1) {
              R(i,j) = rightdiags[1];
              L(i,j) = leftdiags[1];
            }
            else {
              boundary(i) += (rightdiags[1] - leftdiags[1]) * BC[1];
            }
        }
        if (i - (nz*ny - 1) == j) {
            if (xindex(j) != 0) {
              R(i,j) = rightdiags[2];
              L(i,j) = leftdiags[2];
            }
            else {
              boundary(i) += (rightdiags[2] - leftdiags[2]) * BC[0];
            }
        }
      }
    }

    NVECTOR right = R.dot(flat_C) + boundary;
    *flat_C = L.colPivHouseholderQr().solve(right);  // Solves L * new_C = R * flat_C + boundary

}
