
#pragma once
#include "Operator.h"

class EmisOperator : public Operator {

  public:
    EmisOperator(MATRIX *E, int active) {
      this->applied = false; this->E = E; this->active = active;
    }
    ~EmisOperator() {  };
  private:
    void apply(*Concentration C) {
      if (active)
        applied = true;
        for (int n=0; n<C->NCHEM; n++)
            // molecules/cm^3 =  E (molec cm^-3 s^-1) * dt (hr) * 3600s/hr
            for (int i=0; i<N; i++)
              (C->values)[n][i] += E[n][i] * time_step * 3600;
      check();
    }
};
