
#pragma once
#include "Parameters.hpp"
#include "Concentration.hpp" // For Concentration Class

class EmissionOperator {
  public:
    void apply(Concentrations *C);
    void check();
    EmissionOperator(FULLCHEMMAP *E, int active = 1);
    ~EmissionOperator();
  private:
    FULLCHEMMAP E;
    bool applied;
    bool active;
};
