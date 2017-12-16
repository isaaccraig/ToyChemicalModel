
#pragma once
#include "Operator.h"
#include "CrankNicolson.h"
#include "Parameters.h"
#include <math>

class AdvDifOperator {

  public:

    void apply(MODPARAMS::NVECTOR *C);
    void apply(MODPARAMS::CONCMAT *C);
    AdvDifOperator(MODPARAMS::CONCMAT *bc, bool active=true);
    ~AdvDifOperator();

  private:
    void initialize_diags();
    MODPARAMS::CONCMAT bc;
    double leftdiags[7];
    double rightdiags[7];

};
