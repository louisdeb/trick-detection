#include "motion.h"
#include <stdio.h>

mpu_values* front_readings[10];
mpu_values* back_readings[10];

void process_packet(comms_packet packet)
{

  mpu_values new_value;
  new_value = packet.mpu_reading;

  printf("Node Id: %d\n", packet.node_id);
  print_reading(new_value);
  add_reading(packet.node_id, new_value);
}

void add_reading(int id, mpu_values reading)
{

  if (id == FRONT) {
    for (int i = 0; i < 10; i++) {
      if (front_readings[i] == NULL) {
        front_readings[i] = &reading;
        return;
      }
    }
  } else if (id == BACK) {
    for (int i = 0; i < 10; i++) {
        if (back_readings[i] == NULL) {
          back_readings[i] = &reading;
          return;
        }
    }
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