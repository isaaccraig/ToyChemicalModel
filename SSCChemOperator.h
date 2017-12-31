
#pragma once
#include "ChemOperator.h"
#include "Parameters.h"

class SSControledChemOperator{

  public:

    void apply(Concentrations *C, double hour);
    void check();
    SSControledChemOperator(int active=1);
    ~SSControledChemOperator();

  private:

    bool applied;
    bool active;
    double exit_time;
    ChemistryOperator ChemOp;

  };
