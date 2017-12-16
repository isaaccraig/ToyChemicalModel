
#pragma once
#include "Parameters.h"

/*

DESCRIBE !!!

*/

namespace NCC_UTILS{

  namespace READIN {

    void Emissions(const char *filename) {};
    void Boundary(const char *filename) {};
    void DepVel(const char *filename) {};

  }

  namespace SPITOUT {

    void Concentrations(Concentrations* C){};

  }
}
