
#pragma once
#include "Operator.h"
#include "Parameters.h"

using namespace MODPARAMS;

class Concentrations{

public:
  string names[NCHEM];
  string argnames[NCHEM-NSTAT];
  CONCMAT values;
  Concentrations(initial){
    this->values = initial;
    this->names = mod_names;        // in MODPARAMS
    this->argnames = mod_argnames;  // in MODPARAMS
  };
  ~Concentrations(){ };

}
