
#pragma once
#include "Grid.hpp"
#include <map>
#include <string>

typedef double ss_f(POINTCHEMMAP values);

class ChemistryOperator {

  public:

    double apply(Grid *grid, double hour, double delt, double exit_time);
    double steadystate_eval(std::string key, POINTCHEMMAP values);
    void SSC_apply(Grid *grid, double hour);

    ChemistryOperator();
    ~ChemistryOperator();

  private:

    std::map<std::string,bool> ss_bool;
    std::map<std::string, ss_f*> ss_funcs;

};
