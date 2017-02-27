#include "net/packetbuf.h"
#include "net/linkaddr.h"
#include "net/rime/rime.h"

#include "mpu_reader.h"

/*---------------------------------------------------------------------------*/

struct comms_packet 
{
  int node_id;
  struct mpu_values mpu_reading;
};

typedef struct comms_packet comms_packet;

/*---------------------------------------------------------------------------*/

void init_comms(void);
void comms_broadcast(comms_packet);