
#pragma once

class DepositionOperator {

  public:
    void apply(*Concentration C);
    bool check();
    DepositionOperator(MATRIX *vd, bool active);
    ~DepositionOperator();
  private:
    MATRIX vd;
    bool applied;
    bool active;
};
