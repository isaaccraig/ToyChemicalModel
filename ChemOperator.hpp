
#pragma once
#include "SSOperator.hpp"
#include "Grid.hpp"

class ChemistryOperator {

  public:
    float apply(Grid *C, double hour, double delt, double exit_time);
    ChemistryOperator(int active = 1);
    ~ChemistryOperator();

  private:
    SteadyStateOperator SSOP;
    bool applied;
    bool active;

};
