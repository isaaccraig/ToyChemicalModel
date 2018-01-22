
#pragma once
#include "Grid.hpp"

class DepositionOperator {

  public:
    void apply(Grid *C);

    DepositionOperator(POINTCHEMMAP *vd);
    ~DepositionOperator();

  private:
    POINTCHEMMAP vd;
};
