
#pragma once
#include "Operator.h"
#include "Parameters.h"

class Concentrations{

public:
  string names[MODPARAMS::NCHEM];
  string argnames[MODPARAMS::NCHEM - MODPARAMS::NSTAT];
  MODPARAMS::CONCMAT values;
  Concentrations(initial);
  ~Concentrations();
}
