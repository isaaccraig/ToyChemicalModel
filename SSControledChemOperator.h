
#pragma once
#include "Operator.h"
#include "Chemistry.h"
#include "Parameters.h"

using namespace MODPARAMS;

class SSControledChemOperator : public Operator {

  public:
    SSControledChemOperator(ChemistryOperator *O, int active) {
      this->applied = false; this->active = active; this->O = *O;
    }
    ~SSControledChemOperator() {  };

    void apply(*Concentration C, double hour) {
      if (active)
        this->applied = true;
        // step size controled call
        double delt = 1;
        int exit_time = this->O->apply(C, hour, delt, 0);
        while (exit_time < time_step * 3600 ) {
          delt /= 2;
          cout << "REDUCING STEP SIZE TO" << delt << endl;
          exit_time = this->O->apply(C, hour, delt, exit_time);
        }
        check();
    }
  private:

    double exit_time;
    ChemistryOperator O;

  }
};
