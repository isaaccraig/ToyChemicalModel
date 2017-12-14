
#pragma once

class Operator {

  public:
    bool applied;
    bool active;

    virtual bool check(){

      /*

      To be inherited and called within all operators as a sanity check
      TO DO: APPLY ADDITIONAL CHECKS !!

      */


      if (not active and applied){
        error("Expected No Operator Application");
      }
      if (active and not applied){
        error("Expected Operator Application");
      }
    }
};
