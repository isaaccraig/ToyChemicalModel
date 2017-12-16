
#pragma once

class Operator {

  public:
    bool applied;
    bool active;

    virtual int check();
    Operator();
    ~Operator();
};
