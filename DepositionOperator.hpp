
#pragma once
#include "Grid.hpp"

class DepositionOperator {

  public:
    void apply(Grid *C);
    void check();
    DepositionOperator(POINTCHEMMAP *vd, int active=1);
    ~DepositionOperator();
  private:
    POINTCHEMMAP vd;
    bool applied;
    bool active;
};
