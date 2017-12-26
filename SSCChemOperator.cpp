
#include "Operator.h"
#include "ChemOperator.h"
#include "Parameters.h"


    SSControledChemOperator::SSControledChemOperator(ChemistryOperator *O, int active = 1) {
      this->applied = false; this->active = active; this->O = *O;
    }

    bool SSControledChemOperator::check() {
      if (active and not applied)
        Utils::Error("Failed to apply SSC Chemsitry");
      if (not active and applied)
        Utils::Error("Unintended SSC Chemsitry Application");
    }

    void SSControledChemOperator::apply(Concentrations *C, double hour) {
      if (active)
        applied = true;
        // step size controled call
        double delt = 1;
        int exit_time = O->apply(C, hour, delt, 0);
        while (exit_time < time_step * 3600 ) {
          delt /= 2;
          cout << "REDUCING STEP SIZE TO" << delt << endl;
          exit_time = O->apply(C, hour, delt, exit_time);
        }
        check();
    }
