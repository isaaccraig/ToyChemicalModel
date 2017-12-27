
#include "Parameters.h"
#include "Concentration.h"

Concentrations::Concentrations(MODPARAMS::CONCMAT initial){
  this->values = initial;

  for (int n=0; n < MODPARAMS::NCHEM; n++)
    (this->names)[n] = MODPARAMS::mod_names[n];

  for (int n=0; n < (MODPARAMS::NCHEM - MODPARAMS::NSTAT); n++)
    (this->argnames)[n] = MODPARAMS::argmod_names[n];
};

Concentrations::~Concentrations(){};
