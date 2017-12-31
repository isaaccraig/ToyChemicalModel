
#include <iostream>
#include "Parameters.hpp"
#include "chemderiv.hpp"
#include "ChemOperator.hpp"
#include <string>

    ChemistryOperator::ChemistryOperator(int active) : SSOP (){
      this->applied = false; this->active = active;
    }

    ChemistryOperator::~ChemistryOperator(){};

    float ChemistryOperator::apply(Concentrations *C, double hour, double delt, double exit_time){
      std::string label;
      for (int t=exit_time; t < PARAMS_time_step * 3600 ; t += delt){
          if (t%50 == 0) {std::cout << "running chem at" << t << "seconds" << std::endl;}
          std::string label;
          for (int i =0; i < N; i++) {
            // combine the static arguments with the chemical arguments for the kinetics function call
            C->set_arglist(i, hour);
            POINTCHEMMAP results = *chem_solver(&(C->args));

            for (int n=0; n < NCHEM; n++){
              label = C->names[n];
              double dCdt = results[label] * delt;
              if ((C->values)[label](i) + dCdt < 0){
                std::cout << "WARNING NEGATIVE: " << n << std::endl;
                return t;
              }
              else {(C->values)[label](i) += dCdt;}
            }

            for (int n=0; n < NCHEM; n++){
              // See the SS Params Namespace for these
              label = C->names[n];
              double ss_val = SSOP.eval(label, results);
              if (ss_val < 0) {
                std::cout << "WARNING NEGATIVE: " << n << std::endl;
                return t;
              }
              else { (C->values)[label](i) = ss_val;}
            }
          }
      }
      return PARAMS_time_step * 3600;
    }
