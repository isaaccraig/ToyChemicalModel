
#include "SSOperator.h"
#include "Parameters.h" // For MODPARAMS namespace
#include <map>
#include <string>

  SteadyStateOperator::SteadyStateOperator(int active){

     names = MODPARAMS::mod_names; // MODPARAMS

     ss_bool['O3'] =   false;     ss_func['O3'] =   not_ss;
     ss_bool['NO2'] =  false;     ss_func['NO2'] =  not_ss;
     ss_bool['NO'] =   false;     ss_func['NO'] =   not_ss;
     ss_bool['AP'] =   false;     ss_func['AP'] =   not_ss;
     ss_bool['APN'] =  false;     ss_func['APN'] =  not_ss;
     ss_bool['HNO3'] = false;     ss_func['HNO3']=  not_ss;
     ss_bool['HO'] =   true;      ss_func['HO'] =   ssHO;
     ss_bool['HO2'] =  true;      ss_func['HO2'] =  ssHO2;
     ss_bool['PROD'] = false;     ss_func['PROD'] = not_ss;
     ss_bool['RO2'] =  false;     ss_func['RO2'] =  not_ss;

     this->active = active;

  }

  SteadyStateOperator::~SteadyStateOperator(){};

  double SteadyStateOperator::eval(string chemkey, CHEMMAP values){
    if (ss_bool[chemkey]) {return ss_func[chemkey](values);}}

  double SteadyStateOperator::eval(int chemindx, CHEMMAP values){
    string chemkey = getkey(chemindx);
    if (ss_bool[chemkey]) {return ss_func[chemkey](values);}}
