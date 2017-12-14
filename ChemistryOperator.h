
#pragma once
#include "Operator.h"
#include "Parameters.h"

using namespace MODPARAMS;

class ChemistryOperator : public Operator {

  public:
    ChemistryOperator(SteadyStateOperator *SSOP, int active) {
      this->applied = false; this->active = active; this->SSOP = *SSOP;
    }
    ~ChemistryOperator() {  };

    float apply(*Concentration C, double hour, double delt, double exit_time){
      for (int t=exit_time; t < time_step * 3600 ; t += delt){
          if (t%50 == 0) {cout << "running chem at" << t << "seconds" << endl;}
          for (int i =0; i < C->N; i++) {
            // combine the static arguments with the chemical arguments for the cythonized kinetics function call
            double arglist[C.NCHEM + 5] = _set_arglist(i, hour);
            CHEMMAP results[Nchem] = CHEMDERIV(arglist);

            for (int n=0; n < C->NCHEM; n++){
              double dCdt = results[n] * delt;
              if (C->values[i] + dCdt < 0){
                cout << "WARNING NEGATIVE: " << n << endl;
                return t;
              }
              else {C->values[i] += dCdt;}
            }

            for (int n=0; n < C->NCHEM; n++){
              // See the SS Params Namespace for these
              double ss_val = SSOp->eval(n, results);
              if (ss_val < 0)
                cout << "WARNING NEGATIVE: " << n << endl;
                return t;
              else {C->values[i] = ss_val;}
            }
          }
      }
      return t;
    }

  private:

    SteadyStateOperator SSOP;

};
