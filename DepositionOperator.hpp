
#pragma once
#include "Concentration.hpp"

class DepositionOperator {

  public:
    void apply(Concentrations *C);
    void check();
    DepositionOperator(POINTCHEMMAP *vd, int active=1);
    ~DepositionOperator();
  private:
    POINTCHEMMAP vd;
    bool applied;
    bool active;
};
