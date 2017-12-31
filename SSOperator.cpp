
#include "SSOperator.h"
#include "Parameters.h" // For MODPARAMS namespace
#include <map>
#include <string>

  SteadyStateOperator::SteadyStateOperator(int active){

     ss_bool["O3"] =   false;     ss_funcs["O3"] =   not_ss;
     ss_bool["NO2"] =  false;     ss_funcs["NO2"] =  not_ss;
     ss_bool["NO"] =   false;     ss_funcs["NO"] =   not_ss;
     ss_bool["AP"] =   false;     ss_funcs["AP"] =   not_ss;
     ss_bool["APN"] =  false;     ss_funcs["APN"] =  not_ss;
     ss_bool["HNO3"] = false;     ss_funcs["HNO3"]=  not_ss;
     ss_bool["HO"] =   true;      ss_funcs["HO"] =   ssHO;
     ss_bool["HO2"] =  true;      ss_funcs["HO2"] =  ssHO2;
     ss_bool["PROD"] = false;     ss_funcs["PROD"] = not_ss;
     ss_bool["RO2"] =  false;     ss_funcs["RO2"] =  not_ss;

     this->active = active;

  }

  SteadyStateOperator::~SteadyStateOperator(){};

  double SteadyStateOperator::eval(std::string chemkey, MODPARAMS::POINTCHEMMAP values){
    if (ss_bool[chemkey]) { return ss_funcs[chemkey](values); }
    else {return 0;}
  }
