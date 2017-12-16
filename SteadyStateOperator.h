
#pragma once
#include "Operator.h"
#include "Parameters.h" // For MODPARAMS namespace
#include <map>
#include <string>

// Inlines for Use in the ss_func MAP, which returns a given function of
// a CHEMMAP type (see Paramteters.h) for each chemical string key

inline double nullf(void) {return 0;}
inline double ssHO(MODPARAMS::CHEMMAP values) {};
inline double ssHO2(MODPARAMS::CHEMMAP values) {return values["RO2"]};

class SteadyStateOperator {

public:

  string getkey(int chemindx){ return this->names[chemindx] };

  // OVERLOADED Evaluation for ability to call using either the
  // numerical index of the chemical or it's string key

  double eval(string chemkey, MODPARAMS::CHEMMAP values);
  double eval(int chemindx, MODPARAMS::CHEMMAP values);

  SteadyStateOperator();
  ~SteadyStateOperator();

private:

  std::map<string,bool> ss_bool;
  std::map<string, *(double f(MODPARAMS::CHEMMAP values))> ss_func;
  string names[MODPARAMS::NCHEM];

}
