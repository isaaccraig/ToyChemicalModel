
#include <iostream>
#include "Parameters.hpp"
#include "chemderiv.hpp"
#include "ChemOperator.hpp"
#include <string>

using namespace std;

/**
  Steady State HO2 Calculation Function
**/
inline double ssHO2(POINTCHEMMAP values) {
  return values["AP"]; // equal to RO2 value
};

/**
  Steady State HO Calculation Function
**/
inline double ssHO(POINTCHEMMAP values) {
  return 1;
};

/**
  Constructor
**/
ChemistryOperator::ChemistryOperator(){

  ss_bool["O3"] =   false;
  ss_bool["NO2"] =  false;
  ss_bool["NO"] =   false;
  ss_bool["AP"] =   false;
  ss_bool["APN"] =  false;
  ss_bool["HNO3"] = false;
  ss_bool["PROD"] = false;

  ss_bool["HO"] =   true;
  ss_funcs["HO"] =   ssHO;
  ss_bool["HO2"] =  true;
  ss_funcs["HO2"] =  ssHO2;

}

/**
  Destructor
**/
ChemistryOperator::~ChemistryOperator(){};

/**
  Alters Grid
**/
double ChemistryOperator::apply(Grid *grid, double hour, double delt, double exit_time){

  string label;
  double delta_Concentration;

  /**
  iterate over all time (starting from the time last exited until the end of a full
  operator split timestep (PARAMS_time_step, in hours), with steps delt
  **/
  for (double t = exit_time; t < PARAMS_time_step * 3600; t += delt){

      for (int i = 0; i < N; i++) {

        // combine the static arguments with the chemical arguments for the kinetics function call
        grid->set_arglist(i, hour);

        // call chem_solver on those arguments
        POINTCHEMMAP results = *chem_solver(&(grid->args));

        for (int n=0; n < NCHEM; n++){
          // find the corresponding chemical label at index n
          // set dC = dt * dC/dt
          label = grid->names[n];
          delta_Concentration = results[label] * delt; // results[label] is dC/dt for label

          if ((grid->values)[label](i) + delta_Concentration < 0){
              // if would result in negative value, exit function at failed timestep
              // this time is now exit_time, the time that must be re-run from
              cout << "WARNING NEGATIVE: " << label << " at index: " << n << endl;
              return t;
          } else {
              // if not negative, assign the value to itself + dC
              (grid->values)[label](i) += delta_Concentration;
          }
        }

        for (int n=0; n < NCHEM; n++){
          // again iterate over all chemicals
          // must be done in separate loops as all non-steady state values must
          // be assigned prior
          label = grid->names[n];
          // calculate the steady state value of the chemical
          // if not approximated by ss, will return value found above without alteration
          (grid->values)[label](i) = steadystate_eval(label, results);
        }
      }
    }
    return PARAMS_time_step * 3600;
}

/**
  Returns the SS value for chemical given by key if ss_bool[key] is true,
  Otherwise returns the explcit concentration given by values (from chem_solver)
**/
double ChemistryOperator::steadystate_eval(string key, POINTCHEMMAP values){
  if (ss_bool[key]) {
    return ss_funcs[key](values); // Steady state function call
  } else {
    return values[key]; // Unperturbed value
  }
}

/**
 step size controled call to apply
**/
void ChemistryOperator::SSC_apply(Grid *grid, double hour) {

    double delt = 1;
    double exit_time = this->apply(grid, hour, delt, 0);

    while (exit_time < PARAMS_time_step * 3600 ) {

      delt /= 2;
      cout << "REDUCING STEP SIZE TO" << delt << endl;
      exit_time = this->apply(grid, hour, delt, exit_time);

    }
}
