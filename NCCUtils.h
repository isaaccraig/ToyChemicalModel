
#pragma once
#include "Parameters.h"

/*

DESCRIBE !!!

*/

namespace NCC_UTILS{

  namespace READIN {

    MODPARAMS::NMATRIX* Emissions(const char *filename);
    MODPARAMS::NMATRIX* Boundary(const char *filename);
    MODPARAMS::NMATRIX* DepVel(const char *filename);

  }

  namespace SPITOUT {

    int Concentrations(Concentrations* C);

  }
}
