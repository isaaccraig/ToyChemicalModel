
#pragma once
#include "Parameters.hpp"
#include "Grid.hpp" // For Grid Class

class EmissionOperator {
  public:
    void apply(Grid *C);

    EmissionOperator(FULLCHEMMAP *E);
    ~EmissionOperator();
  private:
    FULLCHEMMAP E;
};
