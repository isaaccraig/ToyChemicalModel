
#pragma once
#include "SteadyStateOperator.h"


class ChemistryOperator {

  public:

    float apply(*Concentration C, double hour, double delt, double exit_time);
    ChemistryOperator(SteadyStateOperator *SSOP, int active);
    ~ChemistryOperator();

  private:

    SteadyStateOperator SSOP;

};
