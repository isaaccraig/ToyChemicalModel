
#pragma once
#include "Concentration.h"

class DepositionOperator {

  public:
    void apply(Concentrations *C);
    void check();
    DepositionOperator(MODPARAMS::POINTCHEMMAP *vd, int active=1);
    ~DepositionOperator();
  private:
    MODPARAMS::POINTCHEMMAP vd;
    bool applied;
    bool active;
};
