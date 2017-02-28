#include "motion.h"
#include <stdio.h>

mpu_values* front_readings[10];

void process_packet(comms_packet packet)
{
  printf("Node Id: %d\n", packet.node_id);
  print_reading(packet.mpu_reading);
  add_reading_front(packet.mpu_reading);
}

void add_reading_front(mpu_values reading)
{
  for (int i = 0; i < 10; i++) {
    if (front_readings[i] == NULL) {
      front_readings[i] = &reading;
      return;
    }
  }
  // stores only 10 readings
  for (int i = 0; i < 10; i++) {
    print_reading(*front_readings[i]);
  }
}

void print_reading(mpu_values reading)
{
  printf("g_x: %d\n", (int) reading.g_x);
  printf("g_y: %d\n", (int) reading.g_y);
  printf("g_z: %d\n", (int) reading.g_z);
  printf("a_x: %d\n", reading.a_x);
  printf("a_y: %d\n", reading.a_y);
  printf("a_z: %d\n", reading.a_z);
}