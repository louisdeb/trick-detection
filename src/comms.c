#include "comms.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

#define BROADCAST_CHANNEL 129

/*---------------------------------------------------------------------------*/

static void broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  printf("Broadcast message received from %d.%d: '%s'\n", 
    from->u8[0], from->u8[1], (char *) packetbuf_dataptr());
}

static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

/*---------------------------------------------------------------------------*/

void init_comms()
{
  broadcast_open(&broadcast, BROADCAST_CHANNEL, &broadcast_call);
}

void comms_broadcast(void) // pass some argument here
{
  packetbuf_copyfrom("Hello", 6); // also clears packet buffer
  broadcast_send(&broadcast);
  printf("sent broadcast\n");
}