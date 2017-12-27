
#pragma once

#include "Eigen/Dense"
#include "Eigen/Core"
#include <string>
#include <map>

namespace MODPARAMS {
   const unsigned int NX = 5, NY = 5, NZ = 5; // Number of Spatial Boxes
   const unsigned int N = NX * NY * NZ;
   const unsigned int NCHEM = 9; // Number of chemical species
   const unsigned int NSTAT = 3; // Number of chemical species held constant (ie H2O)
   const float initial_time = 12; // Initial Local Time in Hours
   const float spinup_duration = 1; // Hours To Spin Up
   const float time_step = 0.5; // Operator split time step used in all cycling except chem (Hours)
   const float final_time = 14; // Final Local Time in Hours
   const unsigned int del_x = 1000, del_y = 1000, del_z = 1000; // Box Lengths in Meters
   const std::string mod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "PROD", "RO2"};
   const std::string argmod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "PROD"};

   typedef Eigen::Matrix<double,N,N>       NMATRIX;
   typedef Eigen::Matrix<double,N,1>       NVECTOR;
   typedef Eigen::Matrix<double,NCHEM,N>   CONCMAT;
   typedef std::map<std::string,NVECTOR>   FULLCHEMMAP;
   typedef std::map<std::string,double>    POINTCHEMMAP;
};

namespace PHYSPARAMS {
   const double CM=2.5e19;
   const double D=1e4; // Turbulent Diffusion
   const double PHOX=10;
   double U=0, V=0, W=0; // Wind Speeds
  //inline double TEMP(float hour){};
};

namespace INPUTPARAMS {
  const std::string InputLocation = "/Documents/Models/CTTM/";
  const std::string Efile = "Emission.nc";
  const std::string BCfile = "Boundary.nc";
  const std::string VDfile = "DepostionVelocity.nc";

};
