
#pragma once
#include "Parameters.h"
#include <string>

class Concentrations{

public:
  std::string names[MODPARAMS::NCHEM];
  std::string argnames[MODPARAMS::NCHEM - MODPARAMS::NSTAT];
  double args[MODPARAMS::NCHEM - MODPARAMS::NSTAT + 5];
  MODPARAMS::FULLCHEMMAP values;
  void set_arglist(int i, double hour);
  Concentrations(MODPARAMS::FULLCHEMMAP initial);
  ~Concentrations();
};
