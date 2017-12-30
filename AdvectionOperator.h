
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
    AdvectionOperator(MODPARAMS::NCHEMVECTOR *bc, int active=1);
    ~AdvectionOperator();

  private:
    void initialize_diags();
    MODPARAMS::CONCMAT bc;
    double leftdiags[7];
    double rightdiags[7];
    double noflux_diagonal_right;
    double noflux_diagonal_left;
    int applied;
    int active;

};
