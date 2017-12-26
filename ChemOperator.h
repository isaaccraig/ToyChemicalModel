
#pragma once
#include "SSOperator.h"


class ChemistryOperator {

  public:

    float apply(Concentrations *C, double hour, double delt, double exit_time);
    ChemistryOperator(SteadyStateOperator *SSOP, int active);
    ~ChemistryOperator();

  private:

    SteadyStateOperator SSOP;

};
