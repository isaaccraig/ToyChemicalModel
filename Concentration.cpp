
#include "Parameters.h"

Concentrations::Concentrations(MODPARAMS::CONCMAT initial){
  this->values = initial;
  this->names = MODPARAMS::mod_names;
  this->argnames = MODPARAMS::mod_argnames;
};
