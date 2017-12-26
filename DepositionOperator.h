
#pragma once
#include "Concentration.h"

class DepositionOperator {

  public:
    void apply(Concentrations *C);
    bool check();
    DepositionOperator(MODPARAMS::NVECTOR *vd, bool active);
    ~DepositionOperator();
  private:
    MODPARAMS::NVECTOR vd;
    bool applied;
    bool active;
};
