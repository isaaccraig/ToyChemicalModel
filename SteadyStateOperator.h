
#pragma once
#include "Operator.h"
#include "Parameters.h"

using namespace MODPARAMS;

class SteadyStateOperator : public Operator {

public:

  SteadyStateOperator(){ default(); }
  ~SteadyStateOperator(){ }

  string getkey(int chemindx){ return this->names[chemindx] };

  double eval(string chemkey, CHEMMAP values){
    if (this->ss_bool[chemkey]) {return this->ss_func[chemkey](values);}}

  double eval(int chemindx, CHEMMAP values){
    string chemkey = this->getkey(chemindx);
    if (this->ss_bool[chemkey]) {return this->ss_func[chemkey](values);}}

private:

  std::map<string,bool> ss_bool;
  std::map<string, *(double f(CHEMMAP values))> ss_func;
  string names[NCHEM];

  inline double nullf(void) {return 0;}
  inline double ssHO(CHEMMAP values) {};
  inline double ssHO2(CHEMMAP values) {return values["RO2"]};

  void default(void){

    this->names = mod_names; // MODPARAMS

    this->ss_bool['O3'] =   false;    this->ss_func['O3'] =   &(this->nullf);
    this->ss_bool['NO2'] =  false;    this->ss_func['NO2'] =  &(this->nullf);
    this->ss_bool['NO'] =   false;    this->ss_func['NO'] =   &(this->nullf);
    this->ss_bool['AP'] =   false;    this->ss_func['AP'] =   &(this->nullf);
    this->ss_bool['APN'] =  false;    this->ss_func['APN'] =  &(this->nullf);
    this->ss_bool['HNO3'] = false;    this->ss_func['HNO3']=  &(this->nullf);
    this->ss_bool['HO'] =   true;     this->ss_func['HO'] =   &(this->nullf);
    this->ss_bool['HO2'] =  true;     this->ss_func['HO2'] =  &(this->nullf);
    this->ss_bool['PROD'] = false;    this->ss_func['PROD'] = &(this->nullf);
    this->ss_bool['RO2'] =  false;    this->ss_func['RO2'] =  &(this->nullf);

  }

}
