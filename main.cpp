
#include <iostream>
#include <netcdf>
//#include <netcdfcpp.h>
#include "NCCUtils.hpp"
#include "Utils.hpp"
#include "AdvectionOperator.hpp"
#include "DepositionOperator.hpp"
#include "EmissionOperator.hpp"
#include "SSOperator.hpp"
#include "SSCChemOperator.hpp"
#include "Parameters.hpp"

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

int main(){

  int debuglevel = 3;
  double xcoord[NX], ycoord[NY], zcoord[NZ], tcoord[NT];
  double temp_record[NT];
  NcVar chemVars[NCHEM];
  std::map<std::string,double[NX][NY][NZ][NT]> conc_out;


  FULLCHEMMAP E = NCC_READIN<NVECTOR>(&(PARAMS_Efile), PARAMS_Evars);
  FULLCHEMMAP INITIAL = NCC_READIN<NVECTOR>(&(PARAMS_Initfile), PARAMS_Initvars);
  POINTCHEMMAP VD = NCC_READIN<double>(&(PARAMS_VDfile), PARAMS_VDvars);
  BCMAP BC = NCC_READIN<BCVEC>(&(PARAMS_BCfile), PARAMS_BCvars);

  AdvectionOperator AdvDifOp(&BC);
  EmissionOperator EmOp(&E);
  DepositionOperator DepOp(&VD);
  SSControledChemOperator SSCChemOp;
  Concentrations C(INITIAL);

  /*

  Cycles through the Spinup time frame and model time frame, applying each Operator Object
  to the Concentration Object Sequentially.

  */

  for (int i=0; i<NX; i++) {xcoord[i] = PARAMS_del_x * i;}
  for (int i=0; i<NY; i++) {ycoord[i] = PARAMS_del_y * i;}
  for (int i=0; i<NZ; i++) {zcoord[i] = PARAMS_del_z * i;}
  for (int i=0; i<NT; i++) {tcoord[i] = PARAMS_initial_time + (PARAMS_time_step * i);}


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

  int index = 0;
  std::string label;

  for(int t=PARAMS_initial_time; t < PARAMS_final_time ; t += PARAMS_time_step) {

      for (int n = 0; n < NCHEM; n++) {
        for (int i = 0; i < N; i++) {
          label = C.names[n];
          conc_out[(C.names)[n]][xindex(i)][yindex(i)][zindex(i)][index] = (C.values[label])(i);
        }
      }
      temp_record[index] = TEMP(t);
      index++;

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

  if (debuglevel > 0) {cout << "creating NETCDF " << endl;}

  /*

  WRITE NETCDF FILE OF DATA HERE

  */

    try {

      NcFile dataFile(PARAMS_ExitLocation + PARAMS_Exitfile, NcFile::replace);

      // dataFile.add_att("spinup_duration",PARAMS_spinup_duration);
      // dataFile.add_att("Initfile",PARAMS_Initfile);
      // dataFile.add_att("Efile",PARAMS_Efile);
      // dataFile.add_att("BCfile",PARAMS_BCfile);
      // dataFile.add_att("VDfile",PARAMS_VDfile);

      NcDim xDim = dataFile.addDim("X dimension", NX);
      NcDim yDim = dataFile.addDim("Y dimension", NY);
      NcDim zDim = dataFile.addDim("Z dimension", NZ);
      NcDim tDim = dataFile.addDim("Time", NT);

      NcVar xVar = dataFile.addVar("X dimension", ncFloat, xDim);
      NcVar yVar = dataFile.addVar("Y dimension", ncFloat, yDim);
      NcVar zVar = dataFile.addVar("Z dimension", ncFloat, zDim);
      NcVar tVar = dataFile.addVar("Time", ncFloat, tDim);

      // Define units attributes for coordinate vars.
      xVar.putAtt("units",PARAMS_spatialunits);
      yVar.putAtt("units",PARAMS_spatialunits);
      zVar.putAtt("units",PARAMS_spatialunits);
      tVar.putAtt("units",PARAMS_temporalunits);

      xVar.putVar(xcoord);
      yVar.putVar(ycoord);
      zVar.putVar(zcoord);
      tVar.putVar(tcoord);

      // Define the netCDF variables
      vector<NcDim> dimVector;
      dimVector.push_back(xDim);
      dimVector.push_back(yDim);
      dimVector.push_back(zDim);
      dimVector.push_back(tDim);

      NcVar TempVar = dataFile.addVar("Temperature", ncFloat, tDim);
      TempVar.putAtt("units", PARAMS_temperatureunits);
      TempVar.putVar(temp_record);

      for (int n = 0; n < NCHEM; n++) {
        chemVars[n] = dataFile.addVar((C.names)[n], ncFloat, dimVector);
        (chemVars[n]).putAtt("units", C.units);
        (chemVars[n]).putVar(conc_out[((C.names)[n])]);
      }

    } catch(NcException& e) {
      e.what();
      Utils::Error();
    }

}
