
#pragma once
#include "Operator.h"
#include "CrankNicolson.h"
#include "Parameters.h"
#include <math>

using namespace MODPARAMS;
using namespace PHYSPARAMS;

class AdvDifOperator : public Operator {

  public:
    AdvDifOperator(CONCMAT *bc, bool active=true) {
      this->applied = false;
      this->active = active;
      this->bc = *bc;
      initialize_diags();
    }
    void apply(NVECTOR *C){
      if (this->active)
        this->applied = true;
        CrankNicolson(C, this->leftdiags, this->rightdiags);
        check();
    }
    void apply(CONCMAT *C){
      // To apply to a full NCHEM x N matrix,
      // run and slice up for each CONCMAT(n,:) term
      if (this->active)
        this->applied = true;
        NVECTOR flat_C;
        for (int n=0; n<NCHEM; n++)
          flat_C(:) = *C(n,:); // Selects a portion of C corresponding to chemical n
          CrankNicolson(&flat_C, this->leftdiags, this->rightdiags); // perturbs this slice
          *C(n,:) = flat_C; // Reassigns perturbed slice
          check(); // checks for application and errors, inherited method from Operator
    }
    ~AdvDifOperator() {  }

  protected:
    void initialize_diags(){

      double rx = D * dt/pow(del_x,2);    double Crx = u * dt/(del_x);
      double ry = D * dt/pow(del_y,2);    double Cry = v * dt/(del_y);
      double rz = D * dt/pow(del_z,2);    double Crz = v * dt/(del_z);

      this->leftdiags =  {  1 + rx + ry + rz,
                          - ry/2 + Cry/4,
                          - rx/2 - Crx/4,
                          - ry/2 + Cry/4,
                          - ry/2 - Cry/4,
                          - rz/2 + Crz/4,
                          - rz/2 - Crz/4};

      this->rightdiags = {  1 + rx - ry - rz,
                          ry/2 + Cry/4,
                          rx/2 - Crx/4,
                          ry/2 + Cry/4,
                          ry/2 - Cry/4,
                          rz/2 + Crz/4,
                          rz/2 - Crz/4]};
    }

  private:
    CONCMAT bc;
    double leftdiags[7];
    double rightdiags[7];

};
