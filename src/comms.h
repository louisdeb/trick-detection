#include "net/packetbuf.h"
#include "net/linkaddr.h"
#include "net/rime/rime.h"

/*---------------------------------------------------------------------------*/

struct comms_packet 
{
  int oscillation_value;
};

typedef struct comms_packet comms_packet;

void init_comms(void);
void comms_broadcast(comms_packet);