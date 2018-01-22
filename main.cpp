
#include <iostream>
#include <fstream>
#include <cstdio>
#include <netcdf>
#include <map>
#include <string>
#include "Utils.hpp"
#include "AdvectionOperator.hpp"
#include "DepositionOperator.hpp"
#include "EmissionOperator.hpp"
#include "ChemOperator.hpp"
#include "Parameters.hpp"

using namespace std;
//using namespace netCDF;
//using namespace netCDF::exceptions;

void read_VD(const char *filename, POINTCHEMMAP *map);
void read_BC(const char *filename, BCMAP *map);
void read_matrix(const char *filename, FULLCHEMMAP *map);

void read_VD(const char *filename, POINTCHEMMAP *map){

    double value;
    string key;

    ifstream input(filename);

    for (int i=0; i<NCHEM; i++) {
      input >> key;
      input >> value;
      (*map)[key] = value;
    }

    input.close();
}
void read_BC(const char *filename, BCMAP *map){

    BCVEC values;
    string key;
    ifstream input(filename);

    for (int i=0; i<NCHEM; i++) {
      input >> key;
      for (int j=0; j<6; j++) {
        input >> values(j);
      }
      (*map)[key] = values;
    }

    input.close();
}
void read_matrix(const char *filename, FULLCHEMMAP *map){

  NVECTOR values;
  int x, y, z;
  string key;

  ifstream input(filename);

  for (int i=0; i<NCHEM; i++) {
    input >> key;
    for (int j=0; j<N; j++) {
      input >> x >> y >> z >> values(linearindex(x,y,z));
    }
    (*map)[key] = values;
  }

  input.close();
}

int main(){

  int debuglevel = 3;
  double xcoord[NX], ycoord[NY], zcoord[NZ], tcoord[NT];
  double temp_record[NT];
  string tab = "    ";

  // NcVar chemVars[NCHEM];
  map<string,double[NX][NY][NZ][NT]> conc_out;

  FULLCHEMMAP E;
  read_matrix(PARAMS_Efile.c_str(), &E);

  FULLCHEMMAP INITIAL;
  read_matrix(PARAMS_Initfile.c_str(), &INITIAL);

  POINTCHEMMAP VD;
  read_VD(PARAMS_VDfile.c_str(), &VD);

  BCMAP BC;
  read_BC(PARAMS_BCfile.c_str(), &BC);

  AdvectionOperator AdvDifOp(&BC);
  EmissionOperator EmOp(&E);
  DepositionOperator DepOp(&VD);
  ChemistryOperator ChemOp;
  Grid C(&INITIAL);

  cout << " ----------------- Toy Chemical Transport Model ----------------- " << endl;
  cout << "   Initial Time : " <<  PARAMS_initial_time  << endl;
  cout << "   Final Time : " << PARAMS_final_time << endl;
  cout << "   Spinup Duration : " << PARAMS_spinup_duration << endl;
  cout << "   Time Step : " << PARAMS_time_step << endl;
  cout << "   NX : " << NX << " (dx = " << PARAMS_del_x << " " << PARAMS_spatialunits << ")" << endl;
  cout << "   NY : " << NY << " (dy = " << PARAMS_del_y << " " << PARAMS_spatialunits << ")" << endl;
  cout << "   NZ : " << NZ << " (dz = " << PARAMS_del_z << " " << PARAMS_spatialunits << ")" << endl;
  cout << "   U : " << PARAMS_U << endl;
  cout << "   V : " << PARAMS_V << endl;
  cout << "   W : " << PARAMS_W << endl;

  for (int i=0; i<NX; i++) {xcoord[i] = PARAMS_del_x * i;}
  for (int i=0; i<NY; i++) {ycoord[i] = PARAMS_del_y * i;}
  for (int i=0; i<NZ; i++) {zcoord[i] = PARAMS_del_z * i;}
  for (int i=0; i<NT; i++) {tcoord[i] = PARAMS_initial_time + (PARAMS_time_step * i);}

  /*

  Cycles through the Spinup time frame and model time frame, applying each Operator Object
  to the Grid Object Sequentially.

  */

  for (double t=(PARAMS_initial_time - PARAMS_spinup_duration); t < PARAMS_initial_time ; t += PARAMS_time_step) {

      if (debuglevel > 0) {cout << " ----------------- spinup at time : " << t << " ----------------- " << endl;}

      if (debuglevel > 2) {cout << "   running spinup emissions at time " << t << endl;}
      EmOp.apply(&C);

      if (debuglevel > 2) {cout << "   running spinup deposition at time " << t << endl;}
      DepOp.apply(&C);

      if (debuglevel > 2) {cout << "   running spinup advection at time " << t << endl;}
      AdvDifOp.apply(&C);

      if (debuglevel > 2) {cout << "   running spinup chemistry at time " << t << endl;}
      ChemOp.SSC_apply(&C, t);
  }

  int index = 0;
  string label;

  for(double t=PARAMS_initial_time; t < PARAMS_final_time ; t += PARAMS_time_step) {

      for (int n = 0; n < NCHEM; n++) {
        for (int i = 0; i < N; i++) {
          label = C.names[n];
          conc_out[(C.names)[n]][xindex(i)][yindex(i)][zindex(i)][index] = (C.values[label])(i);
        }
      }
      temp_record[index] = TEMP(t);
      index++;

      if (debuglevel > 0) {cout << " ----------------- running at time : " << t << " ----------------- " << endl;}

      if (debuglevel > 2) {cout << "   running emissions at time " << t << endl;}
      EmOp.apply(&C);

      if (debuglevel > 2) {cout << "   running depostion at time " << t << endl;}
      DepOp.apply(&C);

      if (debuglevel > 2) {cout << "   running advection at time " << t << endl;}
      AdvDifOp.apply(&C);

      if (debuglevel > 2) {cout << "   running chemistry at time " << t << endl;}
      ChemOp.SSC_apply(&C, t);
  }

  if (debuglevel > 0) {cout << " ----------------- creating results file -----------------" << endl;}

  ofstream fid;
  fid.open(PARAMS_Exitfile.c_str());

  for (int n = 0; n < NCHEM; n++) {
    label = C.names[n];
    fid << label << endl;
    for (int i = 0; i < N; i++) {
      for (int t = 0; t < index; t++) {
        fid << xindex(i) << tab << yindex(i) << tab << zindex(i) << tab;
        fid << t << tab << conc_out[label][xindex(i)][yindex(i)][zindex(i)][t] << endl;
      }
    }
  }

  fid.close();


  /*

  WRITE NETCDF FILE OF DATA HERE

  */

  /**

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
    **/

}
