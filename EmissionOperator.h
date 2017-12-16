
#pragma once
#include "Paramteters.h" // For MODELPARAMS namespace
#include "Concentration.h" // For Concentration Class

class EmisOperator {

  public:
    void apply(*Concentration C);
    bool check();
    EmisOperator(MODELPARAMS::NMATRIX *E, int active);
    ~EmisOperator();
  private:
    MODELPARAMS::NMATRIX E;
    bool applied;
    bool active;
};
