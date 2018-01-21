
#include "CrankNicolson.hpp"
#include "Grid.hpp"
#include "Parameters.hpp"
#include "AdvectionOperator.hpp"
#include "Utils.hpp"
#include <cmath>
#include <string>

AdvectionOperator::AdvectionOperator(BCMAP *bc, int active) {
  this->applied = false;
  this->active = active;
  this->bc = *bc;
  initialize_diags();
}

AdvectionOperator::~AdvectionOperator(){};

void AdvectionOperator::check() {
  if (active and not applied)
    Utils::Error("Failed to apply Advection");
  if (not active and applied)
    Utils::Error("Unintended Advection Application");
}

void AdvectionOperator::apply(Grid *C){
// To apply to a full NCHEM x N matrix,
// run and slice up for each CONCMAT(n,:) term
  std::string label;
  if (active)
    applied = true;
    NVECTOR flat_C;
    for (int n=0; n<NCHEM; n++)
      label = C->names[n];
      flat_C = (C->values)[label]; // Selects a portion of C corresponding to chemical n
      CrankNicolson(&flat_C, leftdiags, rightdiags, noflux_diagonal_right, noflux_diagonal_left, bc[label]);
      // perturbs this slice
      C->values[label] = flat_C; // Reassigns perturbed slice
    check(); // checks for application and errors, inherited method from Operator
    }


void AdvectionOperator::initialize_diags(){

  double rx =   PARAMS_D * 3600 * PARAMS_time_step/pow(PARAMS_del_x,2);
  double Crx =  PARAMS_U * 3600 * PARAMS_time_step/(PARAMS_del_x);
  double ry =   PARAMS_D * 3600 * PARAMS_time_step/pow(PARAMS_del_y,2);
  double Cry =  PARAMS_V * 3600 * PARAMS_time_step/(PARAMS_del_y);
  double rz =   PARAMS_D * 3600 * PARAMS_time_step/pow(PARAMS_del_z,2);
  double Crz =  PARAMS_W * 3600 * PARAMS_time_step/(PARAMS_del_z);

  noflux_diagonal_right = 1 + rx + ry;
  noflux_diagonal_left = 1 - rx - ry;

  leftdiags[0] =  1 + rx + ry + rz;
  leftdiags[1] = - ry/2 + Cry/4;
  leftdiags[2] = - rx/2 - Crx/4;
  leftdiags[3] = - ry/2 + Cry/4;
  leftdiags[4] = - ry/2 - Cry/4;
  leftdiags[5] = - rz/2 + Crz/4;
  leftdiags[6] = - rz/2 - Crz/4;

  rightdiags[0] = 1 + rx - ry - rz;
  rightdiags[1] = ry/2 + Cry/4;
  rightdiags[2] = rx/2 - Crx/4;
  rightdiags[3] = ry/2 + Cry/4;
  rightdiags[4] = ry/2 - Cry/4;
  rightdiags[5] = rz/2 + Crz/4;
  rightdiags[6] = rz/2 - Crz/4;

  }
