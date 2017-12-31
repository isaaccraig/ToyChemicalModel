
#include <iostream>
#include "Parameters.h"
#include "Concentration.h"
#include "DepositionOperator.h"
#include "Utils.h"
#include <string>

DepositionOperator::DepositionOperator(MODPARAMS::POINTCHEMMAP *vd, int active){
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
      for (int n = 0; n<MODPARAMS::NCHEM; n++){
        for (int i = 0; i<MODPARAMS::N; i++){
          label = (C->names)[n];
          C->values[label](i) += C->values[label](i) * vd[label] * \
          (MODPARAMS::time_step * 3600) * 1/(100*MODPARAMS::del_z);
        }
      }  
      applied = true;
    check();
  }

DepositionOperator::~DepositionOperator(){};
