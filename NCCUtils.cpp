
#include "Parameters.h"
#include <iostream>
#include <netcdf>
#include <string>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


MODPARAMS::NVECTOR* NCC_UTILS::READIN::NVECTOR(const std::string *filename) {

  try {

  double output[MODPARAMS::NX][MODPARAMS::NY][MODPARAMS::NZ];
  const char path = INPUTPARAMS::InputLocation + "/" + (*filename);

  // Open for reading
  NcFile dataFile(path, NcFile::read);

  // Throw Error If Not Found
  if (not dataFile.is_valid())
    const char msg = "Could Not Open" + (*filename) + "For Reading";
    Utils::Error(&msg);

  // Retrieve the variable varname


  // TO DO : CHANGE SO THAT READS IN ALL

  NcVar data=dataFile.getVar(*varname);

  // Throw Error If Not Found
  if(data.isNull())
    msg = "Could Not Find" + (*varname) + "in" + (*filename);
    Utils::Error(&msg);

  data.getVar(output);
  // The netCDF file is automatically closed by the NcFile destructor

  return MODUTILS::MAKE_NVEC(output);

  } catch(NcException& e)
    {
      e.what();
      cout<<"FAILURE READING NETCDF"<<endl;
      exit(-1);
    }
};

int NCC_UTILS::SPITOUT::Concentrations(Concentrations* C) {


};
