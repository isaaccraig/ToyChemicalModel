
#pragma once
#include "Parameters.h" // For MODELPARAMS namespace
#include "Concentration.h" // For Concentration Class

class EmissionOperator {

  public:
    void apply(Concentrations *C);
    bool check();
    EmissionOperator(MODPARAMS::CONCMAT *E, int active);
    ~EmissionOperator();
  private:
    MODPARAMS::CONCMAT E;
    bool applied;
    bool active;
};
