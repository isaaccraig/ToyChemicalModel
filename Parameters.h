
#include "Eigen/Dense"
#include "Eigen/Core"

inline int xindex (int i) {return i / (ny * nz);}
inline int yindex (int i) {return (i%(ny * nz))/nz;}
inline int zindex (int i) {return (i%(ny * nz))%nz;}

namespace MODPARAMS {
  static const unsigned int NX = 5, NY = 5, NZ = 5; // Number of Spatial Boxes
  static const unsigned int N = NX * NY * NZ;
  static const unsigned int NCHEM = 9; // Number of chemical species
  static const unsigned int NSTATIC = 3; // Number of chemical species held constant (ie H2O)
  typedef Eigen::Matrix<double,N,N>       NMATRIX;
  typedef Eigen::Matrix<double,N,1>       NVECTOR;
  typedef Eigen::Matrix<double,NCHEM,N>   CONCMAT;
  typedef std::map<string,NVECTOR>        CHEMMAP;
  static const float initial_time = 12; // Initial Local Time in Hours
  static const float spinup_duration = 1; // Hours To Spin Up
  static const float time_step = 0.5; // Operator split time step used in all cycling except chem (Hours)
  static const float final_time = 14; // Final Local Time in Hours
  static const unsigned int del_x = 1000, del_y = 1000, del_z = 1000; // Box Lengths in Meters
  static string mod_names[] = {'O3', 'NO2', 'NO', 'AP', 'APN', 'HNO3', 'HO', 'HO2', 'PROD', 'RO2'};
  static string argmod_names[] = {'O3', 'NO2', 'NO', 'AP', 'APN', 'HNO3', 'HO', 'HO2', 'PROD'};
};

namespace PHYSPARAMS {

  static const double CM = 2.5e19;
  double D=1e4; // Turbulent Diffusion
  static const double PHOX ;
  static double U=0, V=0, W=0; // Wind Speeds
  inline double TEMP(float hour){

  };

};

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
