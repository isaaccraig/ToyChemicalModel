
#include "Parameters.hpp"
#include "Grid.hpp"
#include <string>

DepositionOperator::DepositionOperator(POINTCHEMMAP *vd){
  this->vd = vd;
}

void DepositionOperator::apply(Grid *C) {
    std::string label;
    for (int n=0; n<NCHEM; n++)
        for (int i=0; i<N; i++) {
          label = C->names[n];
          (C->values)[label](i) += (C->values)[label](i) * vd[label] * (time_step * 3600) * 1/(100*del_z);
        }
    }
  }

DepositionOperator::~DepositionOperator(){};
