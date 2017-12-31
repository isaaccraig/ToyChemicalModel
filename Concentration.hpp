
#pragma once
#include "Parameters.hpp"
#include <string>

class Concentrations{

public:
  std::string names[NCHEM];
  std::string argnames[NCHEM - NSTAT];
  double args[NCHEM - NSTAT + 5];
  FULLCHEMMAP values;
  void set_arglist(int i, double hour);
  Concentrations(FULLCHEMMAP initial);
  ~Concentrations();
};
