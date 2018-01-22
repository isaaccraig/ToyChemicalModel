
#pragma once
#include "Parameters.hpp"
#include "Utils.hpp"

void CrankNicolson ( NVECTOR *flat_C, double leftdiags[], double rightdiags[], double noflux_diagonal_right, double noflux_diagonal_left, BCVEC BC );
