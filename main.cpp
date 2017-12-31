
#include <iostream>
#include "NCCUtils.h"
#include "AdvectionOperator.h"
#include "DepositionOperator.h"
#include "EmissionOperator.h"
#include "SSOperator.h"
#include "SSCChemOperator.h"
#include "Parameters.h"

using namespace std;
using namespace MODPARAMS;
using namespace INPUTPARAMS;

int main(){

  int debuglevel = 3;

  /*

  READ NETCDF FILES OF DATA HERE : using the netcdf utility functions from NCCUtils.h,
  which includes a namespace for reading in NETCDF files in the given application.
  The filenames are contained within the INPUTPARAMS namespace within "Parameters.h"

  */

/*
  FULLCHEMMAP E = NCC_READIN<NVECTOR>(&(Efile), Evars);
  POINTCHEMMAP VD = NCC_READIN<double>(&(VDfile), VDvars);
  BCMAP BC = NCC_READIN<BCVEC>(&(BCfile), BCvars);
  FULLCHEMMAP INITIAL;    // Initial Concentrations
  */

  FULLCHEMMAP E;
  POINTCHEMMAP VD;
  BCMAP BC;
  FULLCHEMMAP INITIAL;

  /*

  Instantiation of an Advection Diffusion Operator Object, defined within
  "AdvectionDiffusionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  AdvectionOperator AdvDifOp(&BC);

  /*

  Instantiation of an Emission Operator Object, defined within
  "EmissionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::DepVel

  */

  EmissionOperator EmOp(&E);

  /*

  Instantiation of a Deposition Operator Object, defined within
  "DepositionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  DepositionOperator DepOp(&VD);

  /*

  Instantiation of an SSC Chemistry Operator Object, defined within
  "SSCChemistryOperator.h", which takes a Chemistry Operator Object
  and wraps it with Step Size Control Functionality to prevent
  unstable behavior from insufficently small time steps taken to approximate
  the highly stiff system

  */

  SSControledChemOperator SSCChemOp;

  /*

  Instantiation of a Concentration Object Instance, defined within
  "Chemistry.h"

  */

  Concentrations C(INITIAL);

  /*

  Cycles through the Spinup time frame and model time frame, applying each Operator Object
  to the Concentration Object Sequentially.

  See MODPARAMS in "Parameters.h" for parameters :
            initial_time
            time_step
            spinup_duration
            final_time

  */

  for(int t=(initial_time - spinup_duration); t<initial_time ; t += time_step) {
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

  for(int t=initial_time; t < final_time ; t += time_step) {
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

  WRITE NETCDF FILE OF DATA HERE : using the netcdf utility functions from NCCUtils.h,
  which includes a namespace for spitting out NETCDF files in the given application.
  The inputs include_inputs and include_params cause the func to save parameters and inputs
  to a log file of the same name.

  */

  //if (debuglevel > 0) {cout << "creating NETCDF " << t << endl;}
  //NCC_UTILS::SPITOUT::Concentrations(&C, include_params=true, include_inputs=true);

}
