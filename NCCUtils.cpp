
#include "NCCUtils.hpp"
#include "Utils.hpp"
#include <iostream>
#include <netcdf>
#include <map>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

template <typename T>
  map<string, T> NCC_READIN (const string *filename, vector<const string> varnames) {
  try {
    map<string, T> result;
    T result_piece;
    NcFile dataFile(PARAMS_InputLocation + *filename, NcFile::read);

    for (int n=0; n<varnames.size(); n++) {
      NcVar data=dataFile.getVar(varnames[n]);
      if(data.isNull())
        cout << "ERROR : Could Not Find" << (varnames[n]) << "in" << (*filename);
        Utils::Error();
        data.getVar(result_piece);
        result[varnames[n]] = result_piece;
      }
    return (result);
  } catch(NcException& e)
    {
      e.what();
      cout << "FAILURE READING NETCDF : " << *filename << endl;
      exit(-1);
    }
}
