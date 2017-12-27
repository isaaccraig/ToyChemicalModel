
#pragma once
#include "Parameters.h"

inline int xindex (int i) {return i / (MODPARAMS::NY * MODPARAMS::NZ);}
inline int yindex (int i) {return (i%(MODPARAMS::NY * MODPARAMS::NZ))/MODPARAMS::NZ;}
inline int zindex (int i) {return (i%(MODPARAMS::NY * MODPARAMS::NZ))%MODPARAMS::NZ;}

inline void CrankNicolson ( MODPARAMS::NVECTOR *flat_C,
                            double leftdiags[],
                            double rightdiags[],
                            double noflux_diagonal_right,
                            double noflux_diagonal_left,
                            double BC[6] );
