
#pragma once
#include "Parameters.hpp"
#include <string>

class Grid{

public:
  std::string names[NCHEM];
  std::string units;
  std::string argnames[NCHEM - NSTAT];
  double args[NCHEM - NSTAT + 5];
  FULLCHEMMAP values;
  void set_arglist(int i, double hour);
  Grid(FULLCHEMMAP *initial);
  ~Grid();
};
