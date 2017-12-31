
#pragma once
#include "Parameters.hpp"

inline int xindex (int i) {return i / (NY * NZ);}
inline int yindex (int i) {return (i%(NY * NZ))/NZ;}
inline int zindex (int i) {return (i%(NY * NZ))%NZ;}

void CrankNicolson ( NVECTOR *flat_C, double leftdiags[], double rightdiags[], double noflux_diagonal_right, double noflux_diagonal_left, BCVEC BC );
