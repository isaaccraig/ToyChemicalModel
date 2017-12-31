
#include <iostream>
#include "Parameters.h"
#include "Concentration.h"
#include <string>

Concentrations::Concentrations(MODPARAMS::FULLCHEMMAP initial){
  this->values = initial;

  for (int n=0; n < MODPARAMS::NCHEM; n++)
    (this->names)[n] = MODPARAMS::mod_names[n];

  for (int n=0; n < (MODPARAMS::NCHEM - MODPARAMS::NSTAT); n++)
    (this->argnames)[n] = MODPARAMS::argmod_names[n];
};

void Concentrations::set_arglist(int i, double hour){
  std::string label;
  double value;

  args[0] = MODPARAMS::time_step * 3600; //seconds
  args[1] = hour;
  args[2] = PHYSPARAMS::TEMP(hour);
  args[3] = PHYSPARAMS::CM;
  args[4] = MODPARAMS::del_z; //meters

  for (int n=0; n<(MODPARAMS::NCHEM-MODPARAMS::NSTAT); n++){
    label = argnames[n];
    value = values[label](i);
    args[5+n] = value;
  }
};

Concentrations::~Concentrations(){};
