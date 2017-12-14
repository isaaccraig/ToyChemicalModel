
#pragma once
#include "Operator.h"
#include "Parameters.h"

using namespace MODPARAMS;

class DepositionOperator : public Operator {

  public:
    DepositionOperator(MATRIX *vd, bool active) {
      this->applied = false; this->vd = vd; this->active = active;
    }
    ~DepositionOperator() {  };
  private:
    void apply(*Concentration C) {
      if (active)
        this->applied = true;
        for (int n=0; n<C->NCHEM; n++)
            for (int i=0; i<N; i++)
              (C->values)[n][i] += (C->values)[n][i] * vd[n][i] * (time_step * 3600) * 1/(100*del_z);
        check();
    }
};
