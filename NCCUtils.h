
#pragma once
#include "Parameters.h"
#include <string>

/*

DESCRIBE !!!

*/

namespace NCC_UTILS{

  namespace READIN {

    MODPARAMS::NVECTOR* NVECTOR(const std::string *filename);

    MODPARAMS::CONCMAT* CONCMAT(const std::string *filename);

  }

  namespace SPITOUT {

  }
}
