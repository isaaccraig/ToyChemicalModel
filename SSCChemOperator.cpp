
#include <iostream>
#include "ChemOperator.h"
#include "Parameters.h"
#include "Utils.h"
#include "SSCChemOperator.h"

    SSControledChemOperator::SSControledChemOperator(int active) : ChemOp(){
      this->applied = false; this->active = active;
    }

    void SSControledChemOperator::check() {
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
        int exit_time = ChemOp.apply(C, hour, delt, 0);
        while (exit_time < MODPARAMS::time_step * 3600 ) {
          delt /= 2;
          std::cout << "REDUCING STEP SIZE TO" << delt << std::endl;
          exit_time = ChemOp.apply(C, hour, delt, exit_time);
        }
        check();
    }

    SSControledChemOperator::~SSControledChemOperator() {};
