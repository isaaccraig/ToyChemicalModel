
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Parameters.hpp"
#include <string>
#include <map>
#include <vector>

 const float PARAMS_initial_time = 12; // Initial Local Time in Hours
 const float PARAMS_spinup_duration = 1; // Hours To Spin Up
 const float PARAMS_time_step = 0.5; // Operator split time step used in all cycling except chem (Hours)
 const float PARAMS_final_time = 14; // Final Local Time in Hours
 const unsigned int PARAMS_del_x = 1000, PARAMS_del_y = 1000, PARAMS_del_z = 1000; // Box Lengths in Meters
 const std::string PARAMS_mod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "H2O", "PROD", "RO2"};
 const std::string PARAMS_argmod_names[] = {"O3", "NO2", "NO", "AP", "APN", "HNO3", "HO", "HO2", "PROD"};

 const double PARAMS_CM=2.5e19;
 const double PARAMS_D=1e4; // Turbulent Diffusion
 const double PARAMS_PHOX=10;
 const double PARAMS_U=0, PARAMS_V=0, PARAMS_W=0; // Wind Speeds

 const std::string PARAMS_InputLocation = "/Documents/Models/CTTM/";
 const std::string PARAMS_Efile = "Emission.nc";
 const std::string PARAMS_BCfile = "Boundary.nc";
 const std::string PARAMS_VDfile = "DepostionVelocity.nc";

 std::vector<const std::string> PARAMS_Evars = {"O3", "NO2"};
 std::vector<const std::string> PARAMS_VDvars = {"O3", "NO2"};
 std::vector<const std::string> PARAMS_BCvars = {"O3", "NO2"};
