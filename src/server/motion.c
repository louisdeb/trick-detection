#include "motion.h"
#include <stdio.h>

void process_packet(comms_packet packet)
{
  printf("Node Id: %d\n", packet.node_id);
  printf("g_x: %d\n", (int) packet.mpu_reading.g_x);
  printf("g_y: %d\n", (int) packet.mpu_reading.g_y);
  printf("g_z: %d\n", (int) packet.mpu_reading.g_z);
  printf("a_x: %d\n", packet.mpu_reading.a_x);
  printf("a_y: %d\n", packet.mpu_reading.a_y);
  printf("a_z: %d\n", packet.mpu_reading.a_z);
}