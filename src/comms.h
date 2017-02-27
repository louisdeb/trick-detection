#include "net/packetbuf.h"
#include "net/linkaddr.h"
#include "net/rime/rime.h"

#include "mpu_reader.h"

/*---------------------------------------------------------------------------*/

void init_comms(void);
void comms_broadcast(mpu_values);