
#include "Parameters.h"

DepositionOperator::DepositionOperator(MODPARAMS::MATRIX *vd, bool active){
  this->applied = false;
  this->vd = vd;
  this->active = active;
}

bool EmisOperator::check() {
  if (active and not applied)
    Utils::Error("Failed to apply Deposition");
  if (not active and applied)
    Utils::Error("Unintended Deposition Application");
}

void DepositionOperator::apply(*Concentration C) {
    if (active)
      for (int n=0; n<MODPARAMS::NCHEM; n++)
          for (int i=0; i<MODPARAMS::N; i++)
            (C->values)[n][i] += (C->values)[n][i] * vd[n][i] * (MODPARAMS::time_step * 3600) * 1/(100*MODPARAMS::del_z);
      applied = true;
    check();
  }
