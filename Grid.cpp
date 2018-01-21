
#include <iostream>
#include "Parameters.hpp"
#include "Grid.hpp"
#include <string>

Grid::Grid(FULLCHEMMAP *initial){
  this->values = *initial;
  this->units = "molecules/cm^3";

  for (int n=0; n < NCHEM; n++)
    (this->names)[n] = PARAMS_mod_names[n];

  for (int n=0; n < (NCHEM - NSTAT); n++)
    (this->argnames)[n] = PARAMS_argmod_names[n];
};

void Grid::set_arglist(int i, double hour){
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

Grid::~Grid(){};
