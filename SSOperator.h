
#pragma once
#include "Parameters.h" // For MODPARAMS namespace
#include <map>
#include <string>
#include <iostream>


// Inlines for Use in the ss_func MAP, which returns a given function of
// a CHEMMAP type (see Paramteters.h) for each chemical string key

typedef double ss_f(MODPARAMS::POINTCHEMMAP values);
inline double ssHO2(MODPARAMS::POINTCHEMMAP values) {return values["RO2"];};
inline double ssHO(MODPARAMS::POINTCHEMMAP values) {return 1;};
inline double not_ss(MODPARAMS::POINTCHEMMAP values) {return 0;}

class SteadyStateOperator {

public:

  double eval(std::string chemkey, MODPARAMS::POINTCHEMMAP values);

  SteadyStateOperator(int active = 1);
  ~SteadyStateOperator();

private:

  int active;
  std::map<std::string,bool> ss_bool;
  std::map<std::string, ss_f*> ss_funcs;

};
