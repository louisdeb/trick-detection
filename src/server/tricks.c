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

/*---------------------------------------------------------------------------*/

const char* get_roll_string(Roll roll) 
{
  switch(roll)
  {
    case kick: return "Kick";
    case heel: return "Heel";
    default:   return "No Roll";
  }
}

const char* get_pop_string(Pop pop)
{
  switch(pop)
  {
    case tail: return "Tail";
    case nose: return "Nose";
    default:   return "No Pop";
  }
}

const char* get_spin_string(Spin spin)
{
  switch(spin)
  {
    case frontside: return "Frontside";
    case backside:  return "Backside";
    default:        return "No Spin";
  }
}

const char* get_trick_string(Trick trick)
{
  switch(trick)
  {
    case ollie:           return "Ollie";
    case nollie:          return "Nollie";
    case kickflip:        return "Kickflip";
    case heelflip:        return "Heelflip";
    case nollie_kickflip: return "Nollie Kickflip";
    case nollie_heelflip: return "Nollie Heelflip";
    case fsshuv:          return "Frontside Shuv";
    case shuv:            return "Pop Shuv-it";
    case nollie_fsshuv:   return "Nollie Frontside Shuv";
    case nollie_shuv:     return "Nollie Pop Shuv-it";
    case varial:          return "Varial";
    default:              return "No Trick";
  }
}