
#pragma once
#include "CrankNicolson.h"
#include "Parameters.h"
#include "Concentration.h"
#include <cmath>

class AdvectionOperator {

  public:

    void apply(Concentrations *C);
    void apply(MODPARAMS::NVECTOR  *C);
    void check();
    AdvectionOperator(MODPARAMS::CONCMAT *bc, int active=1);
    ~AdvectionOperator();

  private:
    void initialize_diags();
    MODPARAMS::CONCMAT bc;
    double leftdiags[7];
    double rightdiags[7];
    int applied;
    int active;

};
