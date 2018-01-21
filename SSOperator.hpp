
#pragma once
#include "Parameters.hpp"
#include <map>
#include <string>
#include <iostream>


// Inlines for Use in the ss_func MAP, which returns a given function of
// a CHEMMAP type (see Paramteters.hpp) for each chemical string key

typedef double ss_f(POINTCHEMMAP values);
inline double ssHO2(POINTCHEMMAP values) {return values["AP"];};
inline double ssHO(POINTCHEMMAP values) {return 1;};
inline double not_ss(POINTCHEMMAP values) {return 0;}

class SteadyStateOperator {

public:

  double eval(std::string chemkey, POINTCHEMMAP values);

  SteadyStateOperator(int active = 1);
  ~SteadyStateOperator();

private:

  int active;
  std::map<std::string,bool> ss_bool;
  std::map<std::string, ss_f*> ss_funcs;

};
