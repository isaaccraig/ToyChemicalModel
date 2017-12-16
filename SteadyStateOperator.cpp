
#include "SteadyStateOperator.h"
#include "Parameters.h" // For MODPARAMS namespace
#include <map>
#include <string>


  SteadyStateOperator::SteadyStateOperator(void){

     names = MODPARAMS::mod_names; // MODPARAMS

     ss_bool['O3'] =   false;     ss_func['O3'] =   &(nullf);
     ss_bool['NO2'] =  false;     ss_func['NO2'] =  &(nullf);
     ss_bool['NO'] =   false;     ss_func['NO'] =   &(nullf);
     ss_bool['AP'] =   false;     ss_func['AP'] =   &(nullf);
     ss_bool['APN'] =  false;     ss_func['APN'] =  &(nullf);
     ss_bool['HNO3'] = false;     ss_func['HNO3']=  &(nullf);
     ss_bool['HO'] =   true;      ss_func['HO'] =   &(nullf);
     ss_bool['HO2'] =  true;      ss_func['HO2'] =  &(nullf);
     ss_bool['PROD'] = false;     ss_func['PROD'] = &(nullf);
     ss_bool['RO2'] =  false;     ss_func['RO2'] =  &(nullf);

  }

  double SteadyStateOperator::eval(string chemkey, CHEMMAP values){
    if (ss_bool[chemkey]) {return ss_func[chemkey](values);}}

  double SteadyStateOperator::eval(int chemindx, CHEMMAP values){
    string chemkey = getkey(chemindx);
    if (ss_bool[chemkey]) {return ss_func[chemkey](values);}}
