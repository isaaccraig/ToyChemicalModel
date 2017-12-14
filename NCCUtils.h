
#pragma once
#include "Parameters.h"

/*

DESCRIBE !!!

*/

using namespace MODPARAMS;

namespace NCC_UTILS{

  namespace READIN {

    void Emissions() {};
    void Boundary() {};
    void DepVel() {};

  }

  namespace SPITOUT {

    void Concentrations(Concentrations* C){};

  }
}
