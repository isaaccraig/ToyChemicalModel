
#pragma once

#include "Eigen/Dense"
#include "Eigen/Core"
#include <string>
#include <map>
#include <vector>

#define NX 5
#define NY 5
#define NZ 1
#define N 25
#define NCHEM 12
#define NSTAT 3

typedef Eigen::Matrix<double,N,N>                     NMATRIX;
typedef Eigen::Matrix<double,N,1>                     NVECTOR;
typedef Eigen::Matrix<double,NCHEM,1>                 NCHEMVECTOR;
typedef Eigen::Matrix<double,NCHEM,N>                 CONCMAT;
typedef std::map<std::string,NVECTOR>                 FULLCHEMMAP;

typedef Eigen::Matrix<double,6,1>                     BCVEC;
typedef std::map<std::string,BCVEC>                   BCMAP;
typedef std::map<std::string,double>                  POINTCHEMMAP;

extern const float PARAMS_initial_time ; // Initial Local Time in Hours
extern const float PARAMS_spinup_duration ; // Hours To Spin Up
extern const float PARAMS_time_step ; // Operator split time step used in all cycling except chem (Hours)
extern const float PARAMS_final_time; // Final Local Time in Hours
extern const unsigned int PARAMS_del_x, PARAMS_del_y, PARAMS_del_z; // Box Lengths in Meters
extern const std::string PARAMS_mod_names[];
extern const std::string PARAMS_argmod_names[];
extern const double PARAMS_CM;
extern const double PARAMS_D; // Turbulent Diffusion
extern const double PARAMS_PHOX;
extern const double PARAMS_U, PARAMS_V, PARAMS_W; // Wind Speeds

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
     return 273 + Tmin + Trange * (exp(-gam * t) * pow((1 + t/a), (gam*a)));};

extern const std::string PARAMS_InputLocation ;
extern const std::string PARAMS_Efile ;
extern const std::string PARAMS_BCfile ;
extern const std::string PARAMS_VDfile ;

extern std::vector<const std::string> PARAMS_Evars ;
extern std::vector<const std::string> PARAMS_VDvars ;
extern std::vector<const std::string> PARAMS_BCvars ;
