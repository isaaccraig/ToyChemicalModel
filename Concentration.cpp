
#include "Parameters.h"


Concentrations::Concentrations(initial){
  this->values = initial;
  this->names = MODPARAMS::mod_names;
  this->argnames = MODPARAMS::mod_argnames;
};
