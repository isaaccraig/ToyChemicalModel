

#include "NCCUtils.h"
#include "AdvectionDiffusionOperator.h"
#include "DepositionOperator.h"
#include "EmissionOperator.h"
#include "SteadyStateOperator.h"
#include "SSCChemistryOperator.h"
#include "Parameters.h"

int main(){

  /*

  MODPARAMS in "Parameters.h" for type definitions

  */

  MODPARAMS::NVEC BC;         // Boundary Conditions
  MODPARAMS::NVEC VD;         // Deposition Velocity
  MODPARAMS::NVEC E;          // Emissions
  MODPARAMS::NVEC INITIAL;    // Initial Concentrations

  /*

  READ NETCDF FILES OF DATA HERE : using the netcdf utility functions from NCCUtils.h,
  which includes a namespace for reading in NETCDF files in the given application.
  The filenames are contained within the INPUTPARAMS namespace within "Parameters.h"

  */

  if (verbosity > 3) {cout << "reading in Emissions ..." << endl;}
  *E = NCC_UTILS::READIN::NVEC(&(OUTPUTPARAMS::Efile));

  if (verbosity > 3) {cout << "reading in Boundary ... " << endl;}
  *BC = NCC_UTILS::READIN::NVEC(&(OUTPUTPARAMS::BCfile));

  if (verbosity > 3) {cout << "reading in DepVel ... " << endl;}
  *VD = NCC_UTILS::READIN::NVEC(&(OUTPUTPARAMS::VDfile));

  /*

  Instantiation of an Advection Diffusion Operator Object, defined within
  "AdvectionDiffusionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  if (verbosity > 3) {cout << "Constructing Advection Diffusion Operator ..." << endl;}
  AdvectionDiffusionOperator AdvDifOp(&BC);

  /*

  Instantiation of an Emission Operator Object, defined within
  "EmissionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::DepVel

  */

  if (verbosity > 3) {cout << "Constructing Emission Operator ..." << endl;}
  EmissionOperator EmOp(&E);

  /*

  Instantiation of a Deposition Operator Object, defined within
  "DepositionOperator.h", which takes a CONCVEC type input
  obtained through NCC_UTILS::READIN::Boundary

  */

  if (verbosity > 3) {cout << "Constructing Depositon Operator ..." << endl;}
  DepositionOperator DepOp(&VD);

  /*

  Instantiation of a Steady State Operator Object, defined within
  "SteadyStateOperator.h", which takes in ()
  and is only called internally through the Chemistry Operator object,
  which requires it as an arument to its contructor

  */

  if (verbosity > 3) {cout << "Constructing SS Operator ..." << endl;}
  SteadyStateOperator SSOp();             // used within chem

  /*

  Instantiation of a Chemistry Operator Object, defined within
  "ChemistryOperator.h", which takes a Steady State Operator Object
  and is only called internally through the SSC Chemistry Operator object,
  which requires it as an arument to its contructor

  */

  if (verbosity > 3) {cout << "Constructing Chemistry Operator ..." << endl;}
  ChemistryOperator ChemOp(&SSOp);        // used within SSC chem

  /*

  Instantiation of an SSC Chemistry Operator Object, defined within
  "SSCChemistryOperator.h", which takes a Chemistry Operator Object
  and wraps it with Step Size Control Functionality to prevent
  unstable behavior from insufficently small time steps taken to approximate
  the highly stiff system

  */

  if (verbosity > 3) {cout << "Constructing SSC Chemistry Operator ..." << endl;}
  SSControledChemOperator SSCOp(&ChemOp);

  /*

  Instantiation of a Concentration Object Instance, defined within
  "Chemistry.h"

  */

  if (verbosity > 3) {cout << "Constructing Concentrations Operator ..." << endl;}
  C Concentrations(&INITIAL);

  /*

  Cycles through the Spinup time frame and model time frame, applying each Operator Object
  to the Concentration Object Sequentially.

  See MODPARAMS in "Parameters.h" for parameters :
            initial_time
            time_step
            spinup_duration
            final_time

  */


  for(int t=(MODPARAMS::initial_time - MODPARAMS::spinup_duration); t<MODPARAMS::initial_time ; t += MODPARAMS::time_step) {
      if (verbosity > 0) {cout << "spinup at time " << t << endl;}

      if (verbosity > 2) {cout << "running spinup emissions at time " << t << endl;}
      EmOp.apply(C);

      if (verbosity > 2) {cout << "running spinup deposition at time " << t << endl;}
      DepOp.apply(C);

      if (verbosity > 2) {cout << "running spinup advection at time " << t << endl;}
      AdvDifOp.apply(C);

      if (verbosity > 2) {cout << "running spinup chemistry at time " << t << endl;}
      SSCOp.apply(C);
  }
  for(int t=iMODPARAMS::nitial_time; t < MODPARAMS::final_time ; t += MODPARAMS::time_step) {
      if (verbosity > 0) {cout << "running at time " << t << endl;}

      if (verbosity > 2) {cout << "running emissions at time " << t << endl;}
      EmOp.apply(C);

      if (verbosity > 2) {cout << "running depostion at time " << t << endl;}
      DepOp.apply(C);

      if (verbosity > 2) {cout << "running advection at time " << t << endl;}
      AdvDifOp.apply(C);

      if (verbosity > 2) {cout << "running chemistry at time " << t << endl;}
      SSCOp.apply(C);
  }

  /*

  WRITE NETCDF FILE OF DATA HERE : using the netcdf utility functions from NCCUtils.h,
  which includes a namespace for spitting out NETCDF files in the given application.
  The inputs include_inputs and include_params cause the func to save parameters and inputs
  to a log file of the same name.

  */

  if (verbosity > 0) {cout << "creating NETCDF " << t << endl;}
  NCC_UTILS::SPITOUT::Concentrations(&C, include_params=true, include_inputs=true);

}
