
#include "Concentration.h"
#include "Utils.h"
#include "Paramters.h" // MODELPARAMS namespace

EmisOperator::EmisOperator(MATRIX *Emis, int active) {
  this->applied = false;
  this->E = Emis;
  this->active = active;
}

bool EmisOperator::check() {
  if (active and not applied)
    Utils::Error("Failed to apply Emissions");
  if (not active and applied)
    Utils::Error("Unintended Emission Application");
}

void EmisOperator::apply(*Concentration C) {
    if (active)
      for (int n=0; n<MODELPARAMS::NCHEM; n++)
            for (int i=0; i<MODELPARAMS::N; i++)
              // molecules/cm^3 =  E (molec cm^-3 s^-1) * dt (hr) * 3600s/hr
              (C->values)[n][i] += E[n][i] * MODELPARAMS::time_step * 3600;
      applied = true;
    check();
}
