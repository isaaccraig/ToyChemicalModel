
#include "Grid.hpp"
#include "Utils.hpp"
#include "EmissionOperator.hpp"
#include "Parameters.hpp"
#include <string>

EmissionOperator::EmissionOperator(FULLCHEMMAP *Emis) {
  this->E = *Emis;
}

void EmissionOperator::apply(Grid *C) {
    std::string label;
    for (int n=0; n<NCHEM; n++) {
          for (int i=0; i<N; i++) {
            // molecules/cm^3 =  E (molec cm^-3 s^-1) * dt (hr) * 3600s/hr
            label = C->names[n];
            (C->values)[label](i) += E[label](i) * PARAMS_time_step * 3600;
          }
    }
}

EmissionOperator::~EmissionOperator(){};
