
#include "Parameters.h"
#include <cstdio>

using namespace MODPARAMS;

NVECTOR* MODUTILS::MAKE_NVEC(double flat_C[N]){
  NVECTOR C;
  for (int i=0; i<N; i++)
    C(i) = flat_C[i];
  return &C;
}

NVECTOR* MODUTILS::MAKE_NVEC(double C[NX][NY][NZ]){
  NVECTOR C;
  for (int i=0; i<NX; i++)
    for (int j=0; j<NY; j++)
      for (int k=0; k<NZ; k++)
        int index = i*NY*NZ + j*NZ + k;
// flattens to form a vector from matrix
// so that can loop over the single n
// variable to get the relevant value
C(index) = flat_C[i][j][k];
  return &C;
}

  /* base Error to give message and halt */
inline void error( const std::string *msg ) {
  fprintf(stderr, "Error : %s\n", msg);
  exit(-1);
  }
  /* Warning to give message and continue */
inline void warning( const std::string *msg ) {
  fprintf(stderr, "Warning : %s\n", msg);
}
