
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Parameters.hpp"
#include <string>
#include <map>
#include <vector>

 const unsigned int PARAMS_del_x = 1000, PARAMS_del_y = 1000, PARAMS_del_z = 1000; // Box Lengths in Meters
 const std::string PARAMS_spatialunits = "meters";
 const std::string PARAMS_temporalunits = "hours";
 const std::string PARAMS_temperatureunits = "Kelvin";
 const std::string PARAMS_mod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "H2O", "PROD"};
 const std::string PARAMS_argmod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "PROD"};

 const double PARAMS_CM=2.5e19;
 const double PARAMS_D=1e4; // Turbulent Diffusion
 const double PARAMS_PHOX=10;
 const double PARAMS_U=0, PARAMS_V=0, PARAMS_W=0; // Wind Speeds

 const std::string PARAMS_InputLocation = "/Documents/Models/CTTM/Inputs";
 const std::string PARAMS_ExitLocation = "/Documents/Models/CTTM/Runs/Testing";
 const std::string PARAMS_Efile = "Inputs/Emission.txt";
 const std::string PARAMS_BCfile = "Inputs/Boundary.txt";
 const std::string PARAMS_VDfile = "Inputs/DepostionVelocity.txt";
 const std::string PARAMS_Initfile = "Inputs/Initial.txt";
 const std::string PARAMS_Exitfile = "Results/Testing.txt";

 // std::vector<const std::string> PARAMS_Evars = {"O3", "NO2"};
 // std::vector<const std::string> PARAMS_VDvars = {"O3", "NO2"};
 // std::vector<const std::string> PARAMS_BCvars = {"O3", "NO2"};
 // std::vector<const std::string> PARAMS_Initvars = {"O3", "NO2"};
