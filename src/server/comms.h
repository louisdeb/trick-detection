#include "net/packetbuf.h"
#include "net/linkaddr.h"
#include "net/rime/rime.h"

#include "motion.h"

/*---------------------------------------------------------------------------*/

void init_comms(void);
void comms_broadcast(comms_packet);