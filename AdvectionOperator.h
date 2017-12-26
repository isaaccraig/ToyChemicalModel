
#pragma once
#include "CrankNicolson.h"
#include "Parameters.h"
#include <cmath>

class AdvectionOperator {

  public:

    void apply(Concentrations *C);
    AdvectionOperator(MODPARAMS::CONCMAT *bc, bool active=true);
    ~AdvectionOperator();

  private:
    void initialize_diags();
    MODPARAMS::CONCMAT bc;
    double leftdiags[7];
    double rightdiags[7];

};
