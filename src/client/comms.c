#include "comms.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

#define BROADCAST_CHANNEL 420

/*---------------------------------------------------------------------------*/

static void broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  mpu_values mpu_reading;
  memcpy(&mpu_reading, packetbuf_dataptr(), sizeof mpu_reading);
  
  printf("Received mpu readings, a_x: %d\n", mpu_reading.a_x);
}

static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

/*---------------------------------------------------------------------------*/

void init_comms(void)
{
  broadcast_open(&broadcast, BROADCAST_CHANNEL, &broadcast_call);
}

void comms_broadcast(mpu_values reading) // pass some argument here
{
  packetbuf_copyfrom(&reading, sizeof reading);
  broadcast_send(&broadcast);
  printf("sent broadcast, a_x: %d\n", reading.a_x);
}