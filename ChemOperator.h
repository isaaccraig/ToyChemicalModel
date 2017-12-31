
#pragma once
#include "SSOperator.h"
#include "Concentration.h"

class ChemistryOperator {

  public:
    float apply(Concentrations *C, double hour, double delt, double exit_time);
    ChemistryOperator(int active = 1);
    ~ChemistryOperator();

  private:
    SteadyStateOperator SSOP;
    bool applied;
    bool active;

};
