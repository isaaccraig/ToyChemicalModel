
#pragma once
#include "Parameters.h"
#include <string>

class Concentrations{

public:
  std::string names[MODPARAMS::NCHEM];
  std::string argnames[MODPARAMS::NCHEM - MODPARAMS::NSTAT];
  MODPARAMS::CONCMAT values;
  Concentrations(MODPARAMS::CONCMAT initial);
  ~Concentrations();
};
