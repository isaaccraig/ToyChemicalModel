
#pragma once
#include "Parameters.h" // For MODELPARAMS namespace
#include "Concentration.h" // For Concentration Class

class EmissionOperator {
  public:
    void apply(Concentrations *C);
    void check();
    EmissionOperator(MODPARAMS::FULLCHEMMAP *E, int active = 1);
    ~EmissionOperator();
  private:
    MODPARAMS::FULLCHEMMAP E;
    bool applied;
    bool active;
};
