
#pragma once
#include "ChemOperator.hpp"
#include "Parameters.hpp"

class SSControledChemOperator{

  public:

    void apply(Grid *C, double hour);
    void check();
    SSControledChemOperator(int active=1);
    ~SSControledChemOperator();

  private:

    bool applied;
    bool active;
    ChemistryOperator ChemOp;

  };
