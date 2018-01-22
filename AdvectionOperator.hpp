
#pragma once
#include "Parameters.hpp"
#include "Grid.hpp"
#include <cmath>

class AdvectionOperator {

  public:

    void apply(Grid *C);
    AdvectionOperator(BCMAP *bc);
    ~AdvectionOperator();

  private:
    void initialize_diags();
    BCMAP bc;
    double leftdiags[7];
    double rightdiags[7];
    double noflux_diagonal_right;
    double noflux_diagonal_left;

};
