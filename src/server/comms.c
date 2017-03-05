#include "comms.h"
#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/

static void broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  comms_packet packet;
  memcpy(&packet, packetbuf_dataptr(), sizeof packet);
  fix_values(&packet);
  process_packet(packet);
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
}

void fix_values(comms_packet* packet)
{
  if (abs(packet->mpu_reading.a_x) > 3000) { packet->mpu_reading.a_x = 0; }
  if (abs(packet->mpu_reading.a_y) > 3000) { packet->mpu_reading.a_y = 0; }
  if (abs(packet->mpu_reading.a_z) > 3000) { packet->mpu_reading.a_z = 0; }
  if (abs(packet->mpu_reading.g_x) > 3000) { packet->mpu_reading.g_x = 0; }
  if (abs(packet->mpu_reading.g_y) > 3000) { packet->mpu_reading.g_y = 0; }
  if (abs(packet->mpu_reading.g_z) > 3000) { packet->mpu_reading.g_z = 0; }
}