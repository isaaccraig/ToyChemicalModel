
#pragma once

#include "Eigen/Dense"
#include "Eigen/Core"
#include <string>
#include <map>
#include <vector>

namespace MODPARAMS {
   const unsigned int NX = 5, NY = 5, NZ = 5; // Number of Spatial Boxes
   const unsigned int N = NX * NY * NZ;
   const unsigned int NCHEM = 11; // Number of chemical species
   const unsigned int NSTAT = 2; // Number of chemical species held constant (ie H2O)
   const float initial_time = 12; // Initial Local Time in Hours
   const float spinup_duration = 1; // Hours To Spin Up
   const float time_step = 0.5; // Operator split time step used in all cycling except chem (Hours)
   const float final_time = 14; // Final Local Time in Hours
   const unsigned int del_x = 1000, del_y = 1000, del_z = 1000; // Box Lengths in Meters
   const std::string mod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "H2O", "PROD", "RO2"};
   const std::string argmod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "PROD"};

   typedef Eigen::Matrix<double,N,N>                     NMATRIX;
   typedef Eigen::Matrix<double,N,1>                     NVECTOR;
   typedef Eigen::Matrix<double,NCHEM,1>                 NCHEMVECTOR;
   typedef Eigen::Matrix<double,NCHEM,N>                 CONCMAT;
   typedef std::map<std::string,NVECTOR>                 FULLCHEMMAP;
   typedef Eigen::Matrix<double,6,1>                     BCVEC;
   typedef std::map<std::string, BCVEC >                 BCMAP;
   typedef std::map<std::string,double>                  POINTCHEMMAP;
};

namespace PHYSPARAMS {
   const double CM=2.5e19;
   const double D=1e4; // Turbulent Diffusion
   const double PHOX=10;
   double U=0, V=0, W=0; // Wind Speeds
   inline double TEMP(float t){
     // Pearson Type III Model for Diurnal Temperature Cycle
     int Tmin = 15, Trange = 15, a = 9;
     double gam;
     if (t > 24) {t -= 24;}
     if (t <= 5) {t += 10;}
     else if (t >= 14) {t -= 14;}
     else if (t > 5 and t < 14) {t -= 14;}
     if (t < 0) {gam = 0.24;}
     else {gam = 0.8;}
     return 273 + Tmin + Trange * (exp(-gam * t) * pow((1 + t/a), (gam*a)));
   };
};

namespace INPUTPARAMS {
  const std::string InputLocation = "/Documents/Models/CTTM/";
  const std::string Efile = "Emission.nc";
  const std::string BCfile = "Boundary.nc";
  const std::string VDfile = "DepostionVelocity.nc";

  std::vector<const std::string> Evars = {"O3", "NO2"};
  std::vector<const std::string> VDvars = {"O3", "NO2"};
  std::vector<const std::string> BCvars = {"O3", "NO2"};

};
