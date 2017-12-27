
#include "Parameters.h"
#include "ChemDeriv.h"
#include "SSOperator.h"

    ChemistryOperator::ChemistryOperator(SteadyStateOperator *SSOP, int active) {
      this->applied = false; this->active = active; this->SSOP = *SSOP;
    }

    ChemistryOperator::~ChemistryOperator(){};

    float ChemistryOperator::apply(Concentrations *C, double hour, double delt, double exit_time){
      for (int t=exit_time; t < MODPARAMS::time_step * 3600 ; t += delt){
          if (t%50 == 0) {cout << "running chem at" << t << "seconds" << endl;}
          for (int i =0; i < MODPARAMS::N; i++) {
            // combine the static arguments with the chemical arguments for the cythonized kinetics function call
            double arglist[MODPARAMS::NCHEM + 5] = _set_arglist(i, hour);
            MODPARAMS::CHEMMAP results[MODPARAMS::NCHEM] = CHEMDERIV(arglist);

            for (int n=0; n < MODPARAMS::NCHEM; n++){
              double dCdt = results[n] * delt;
              if ((C->values)(n,i) + dCdt < 0){
                cout << "WARNING NEGATIVE: " << n << endl;
                return t;
              }
              else {(C->values)(n,i) += dCdt;}
            }

            for (int n=0; n < MODPARAMS::NCHEM; n++){
              // See the SS Params Namespace for these
              double ss_val = SSOp->eval(n, results);
              if (ss_val < 0)
                cout << "WARNING NEGATIVE: " << n << endl;
                return t;
              else {(C->values)(n,i) = ss_val;}
            }
          }
      }
      return t;
    }
