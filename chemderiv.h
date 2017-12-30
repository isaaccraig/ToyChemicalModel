
#include <string>
#include <cmath>
#include <map>

typedef std::map<std::string,double>   CHEMMAP;

CHEMMAP* chem_solver(double dt, double HOUR, double TEMP, double C_M, double HEIGHT, double conc_O3, double conc_NO2, double conc_NO, double conc_AP, double conc_APN, double conc_HNO3, double conc_HO, double conc_HO2, double conc_PROD);

double dO3_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_O3, double conc_NO2, double conc_NO);
double dNO2_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_AP, double conc_APN, double conc_O3, double conc_HO, double conc_NO2, double conc_NO);
double dNO_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_O3, double conc_NO2, double conc_NO);
double dAP_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_NO2, double conc_HO2, double conc_APN, double conc_AP);
double dAPN_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_NO2, double conc_APN, double conc_AP);
double dHNO3_dt(double HOUR, double TEMP, double C_M, double HEIGHT, double conc_HO, double conc_NO2);
double dHO_dt(double TEMP, double C_M);
double dHO2_dt(double TEMP, double C_M);
double dPROD_dt(double TEMP, double C_M);
double ARR2(double A0, double B0, double TEMP);
double TROE(double k0_300K, double n, double kinf_300K, double m, double TEMP, double C_M);
double TROEE(double A, double B, double k0_300K, double n, double kinf_300K, double m, double TEMP, double C_M);
