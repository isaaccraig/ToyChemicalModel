
#include "Parameters.h"

inline void CrankNicolson ( MODPARAMS::NVECTOR *flat_C,
                            double leftdiags[],
                            double rightdiags[],
                            double noflux_diagonal_right,
                            double noflux_diagonal_left,
                            double BC[6] );
