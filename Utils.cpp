namespace MODUTILS {
    using namespace  MODPARAMS;
    void flatten(double C[NX][NY][NZ], double *flat_C[N]){
      for (int i=0; i<NX; i++)
          for (int j=0; j<NY; j++)
              for (int k=0; k<NZ; k++)
                  // flattens to form a vector from matrix
                  // so that can loop over the single n
                  // variable to get the relevant value
                  int index = i*NY*NZ + j*NZ + k;
                  *flat_C[index] = C[i][j][k];

    }
    void NVEC(NVECTOR *NVEC_C, double flat_C[N]){
      for (int i=0; i<N; i++)
        *C(i) = flat_C[i];
    }
    void expand(double *C[NX][NY][NZ], double flat_C[N]){
      for (int i=0; i<NX; i++)
          for (int j=0; j<NY; j++)
              for (int k=0; k<NZ; k++)
                  // flattens to form a vector from matrix
                  // so that can loop over the single n
                  // variable to get the relevant value
                  int index = i*NY*NZ + j*NZ + k;
                  *C[i][j][k] = flat_C[index];
    }
  }

};
