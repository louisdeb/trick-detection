#include "tricks.h"

Trick get_trick(Roll roll, Pop pop, Spin spin) {

  if (pop == no_pop) {
    // Could determine reverts here
    return no_trick;
  }
  
  if (roll == no_roll && spin == no_spin) {
    return pop == tail ? ollie : nollie; 
  }
  
  if (roll == kick && spin == no_spin) {
    return pop == tail ? kickflip : nollie_kickflip;
  }
 
  if (roll == heel && spin == no_spin) {
    return pop == tail ? heelflip : nollie_heelflip;
  }

  if (roll == no_roll && spin == frontside) {
    return pop == tail ? fsshuv : nollie_shuv;
  }

  if (roll == no_roll && spin == backside) {
    return pop == tail ? shuv : nollie_fsshuv;
  }

  return no_trick;
}



