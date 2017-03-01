#include "comms.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

#define BROADCAST_CHANNEL 420

/*---------------------------------------------------------------------------*/

static void broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  comms_packet packet;
  memcpy(&packet, packetbuf_dataptr(), sizeof packet);
}

static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

/*---------------------------------------------------------------------------*/

void init_comms(void)
{
  broadcast_open(&broadcast, BROADCAST_CHANNEL, &broadcast_call);
}

void comms_broadcast(comms_packet packet)
{
  packetbuf_copyfrom(&packet, sizeof packet);
  broadcast_send(&broadcast);
  printf("Sent mpu reading:\n");
  printf("a_x:\t%d\n", packet.mpu_reading.a_x);
  printf("a_y:\t%d\n", packet.mpu_reading.a_y);
  printf("a_z:\t%d\n", packet.mpu_reading.a_z);
  printf("\n");
}