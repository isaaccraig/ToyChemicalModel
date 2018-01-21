
#pragma once
#include "Parameters.hpp"
#include "Grid.hpp" // For Grid Class

class EmissionOperator {
  public:
    void apply(Grid *C);
    void check();
    EmissionOperator(FULLCHEMMAP *E, int active = 1);
    ~EmissionOperator();
  private:
    FULLCHEMMAP E;
    bool applied;
    bool active;
};
