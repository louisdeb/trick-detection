/*---------------------------------------------------------------------------*/

enum Roll
{
  kick,
  heel,
  no_roll
};

typedef enum Roll Roll;

/*---------------------------------------------------------------------------*/

enum Pop
{
  tail = 1,
  nose = 2,
  no_pop = 0
};

typedef enum Pop Pop;

/*---------------------------------------------------------------------------*/

enum Spin
{
  frontside,
  backside,
  no_spin
};

typedef enum Spin Spin;

/*---------------------------------------------------------------------------*/
enum Trick
{
  ollie,
  nollie,
  kickflip,
  heelflip,
  nollie_kickflip,
  nollie_heelflip,
  fsshuv,
  shuv,
  nollie_fsshuv,
  nollie_shuv,
  varial,
  no_trick
};

typedef enum Trick Trick;

/*---------------------------------------------------------------------------*/

Trick get_trick(Roll roll, Pop pop, Spin spin);




