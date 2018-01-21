
#pragma once
#include "Parameters.hpp"
#include "Grid.hpp"
#include <cmath>

class AdvectionOperator {

  public:

    void apply(Grid *C);
    void check();
    AdvectionOperator(BCMAP *bc, int active=1);
    ~AdvectionOperator();

  private:
    void initialize_diags();
    BCMAP bc;
    double leftdiags[7];
    double rightdiags[7];
    double noflux_diagonal_right;
    double noflux_diagonal_left;
    int applied;
    int active;

};
