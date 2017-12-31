
#include <iostream>
#include "Parameters.hpp"
#include "Concentration.hpp"
#include <string>

Concentrations::Concentrations(FULLCHEMMAP initial){
  this->values = initial;

  for (int n=0; n < NCHEM; n++)
    (this->names)[n] = PARAMS_mod_names[n];

  for (int n=0; n < (NCHEM - NSTAT); n++)
    (this->argnames)[n] = PARAMS_argmod_names[n];
};

void Concentrations::set_arglist(int i, double hour){
  std::string label;
  double value;

  args[0] = PARAMS_time_step * 3600; //seconds
  args[1] = hour;
  args[2] = TEMP(hour);
  args[3] = PARAMS_CM;
  args[4] = PARAMS_del_z; //meters

  for (int n=0; n<(NCHEM-NSTAT); n++){
    label = argnames[n];
    value = values[label](i);
    args[5+n] = value;
  }
};

Concentrations::~Concentrations(){};
