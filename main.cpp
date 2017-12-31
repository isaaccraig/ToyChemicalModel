
#include <iostream>
#include "NCCUtils.hpp"
#include "AdvectionOperator.hpp"
#include "DepositionOperator.hpp"
#include "EmissionOperator.hpp"
#include "SSOperator.hpp"
#include "SSCChemOperator.hpp"
#include "Parameters.hpp"

using namespace std;

int main(){

  int debuglevel = 3;

  /*

  READ NETCDF FILES OF DATA HERE : using the netcdf utility functions from NCCUtils.hpp,
  which includes a namespace for reading in NETCDF files in the given application.
  The filenames are contained within the INPUTPARAMS namespace within "Parameters.hpp"

  */

/*
  FULLCHEMMAP E = NCC_READIN<NVECTOR>(&(Efile), Evars);
  POINTCHEMMAP VD = NCC_READIN<double>(&(VDfile), VDvars);
  BCMAP BC = NCC_READIN<BCVEC>(&(BCfile), BCvars);
  */

  FULLCHEMMAP E;
  POINTCHEMMAP VD;
  BCMAP BC;
  FULLCHEMMAP INITIAL;

  /*

  Instantiation of an Advection Diffusion Operator Object, defined within
  "AdvectionDiffusionOperator.hpp", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  AdvectionOperator AdvDifOp(&BC);

  /*

  Instantiation of an Emission Operator Object, defined within
  "EmissionOperator.hpp", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::DepVel

  */

  EmissionOperator EmOp(&E);

  /*

  Instantiation of a Deposition Operator Object, defined within
  "DepositionOperator.hpp", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  DepositionOperator DepOp(&VD);

  /*

  Instantiation of an SSC Chemistry Operator Object, defined within
  "SSCChemistryOperator.hpp", which takes a Chemistry Operator Object
  and wraps it with Step Size Control Functionality to prevent
  unstable behavior from insufficently small time steps taken to approximate
  the highly stiff system

  */

  SSControledChemOperator SSCChemOp;

  /*

  Instantiation of a Concentration Object Instance, defined within
  "Chemistry.hpp"

  */

  Concentrations C(INITIAL);

  /*

  Cycles through the Spinup time frame and model time frame, applying each Operator Object
  to the Concentration Object Sequentially.

  See MODPARAMS in "Parameters.hpp" for parameters :
            initial_time
            time_step
            spinup_duration
            final_time

  */

  for(int t=(PARAMS_initial_time - PARAMS_spinup_duration); t<PARAMS_initial_time ; t += PARAMS_time_step) {
      if (debuglevel > 0) {cout << "spinup at time " << t << endl;}

      if (debuglevel > 2) {cout << "running spinup emissions at time " << t << endl;}
      EmOp.apply(&C);

      if (debuglevel > 2) {cout << "running spinup deposition at time " << t << endl;}
      DepOp.apply(&C);

      if (debuglevel > 2) {cout << "running spinup advection at time " << t << endl;}
      AdvDifOp.apply(&C);

      if (debuglevel > 2) {cout << "running spinup chemistry at time " << t << endl;}
      SSCChemOp.apply(&C, t);
  }

  for(int t=PARAMS_initial_time; t < PARAMS_final_time ; t += PARAMS_time_step) {
      if (debuglevel > 0) {cout << "running at time " << t << endl;}

      if (debuglevel > 2) {cout << "running emissions at time " << t << endl;}
      EmOp.apply(&C);

      if (debuglevel > 2) {cout << "running depostion at time " << t << endl;}
      DepOp.apply(&C);

      if (debuglevel > 2) {cout << "running advection at time " << t << endl;}
      AdvDifOp.apply(&C);

      if (debuglevel > 2) {cout << "running chemistry at time " << t << endl;}
      SSCChemOp.apply(&C, t);
  }

  /*

  WRITE NETCDF FILE OF DATA HERE : using the netcdf utility functions from NCCUtils.hpp,
  which includes a namespace for spitting out NETCDF files in the given application.
  The inputs include_inputs and include_params cause the func to save parameters and inputs
  to a log file of the same name.

  */

  //if (debuglevel > 0) {cout << "creating NETCDF " << t << endl;}
  //NCC_UTILS::SPITOUT::Concentrations(&C, include_params=true, include_inputs=true);

}
