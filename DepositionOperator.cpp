
#include <iostream>
#include "Parameters.hpp"
#include "Concentration.hpp"
#include "DepositionOperator.hpp"
#include "Utils.hpp"
#include <string>

DepositionOperator::DepositionOperator(POINTCHEMMAP *vd, int active){
  this->applied = false;
  this->vd = *vd;
  this->active = active;
}

void DepositionOperator::check() {
  if (active and not applied)
    Utils::Error("Failed to apply Deposition");
  if (not active and applied)
    Utils::Error("Unintended Deposition Application");
}

void DepositionOperator::apply(Concentrations *C) {
    std::string label;
    if (active)
      for (int n = 0; n<NCHEM; n++){
        for (int i = 0; i<N; i++){
          label = (C->names)[n];
          C->values[label](i) += C->values[label](i) * vd[label] * \
          (PARAMS_time_step * 3600) * 1/(100*PARAMS_del_z);
        }
      }
      applied = true;
    check();
  }

DepositionOperator::~DepositionOperator(){};
