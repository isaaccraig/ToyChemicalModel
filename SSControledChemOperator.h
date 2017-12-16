
#pragma once
#include "Chemistry.h"
#include "Parameters.h"

class SSControledChemOperator{

  public:

    void apply(*Concentration C, double hour);
    SSControledChemOperator(ChemistryOperator *O, int active);
    ~SSControledChemOperator();;

  private:

    double exit_time;
    ChemistryOperator O;

  }
};
