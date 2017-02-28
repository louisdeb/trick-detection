#include "motion.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

#define DIRECTION_TRUE      100
#define DIRECTION_LEEWAY    10

#define BOTTOM_THRESHOLD    (DIRECTION_TRUE - DIRECTION_LEEWAY)
#define TOP_THRESHOLD       (DIRECTION_TRUE + DIRECTION_LEEWAY)

/*---------------------------------------------------------------------------*/

mpu_values* front_readings[10];
mpu_values* back_readings[10];


void process_packet(comms_packet packet)
{
  mpu_values new_value;
  new_value = packet.mpu_reading;

  printf("Node Id: %d\n", packet.node_id);
  print_reading(new_value);
  add_reading(packet.node_id, packet.mpu_reading);
}

void detect_roll(mpu_values readings[10])
{
  bool up, down, left, right, up_again;
  up = down = left = right = up_again = false;
  
  for (int i = 0; i < 10; i++) {
    if (!up) { // face up first
      up = facing_up(readings[i]);
    } else if(!right && !left && !down) { // get something other than up
      right = facing_right(readings[i]);
      left = facing_left(readings[i]); 
      down = facing_down(readings[i]);
    } else if(!down) { // goes upside-down at some point
      down = facing_down(readings[i]);
    } else if(!up_again) {
      up_again = facing_up(readings[i]);
    }
  }

  if (up && down && right && left && up_again) {
    printf("Roll detected");
  }
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

    for (int i = 1; i < 10; i++) {
      front_readings[i-1] = front_readings[i];
    }
    front_readings[9] = &reading;
    return;
    
  } else if (id == BACK) {
    for (int i = 0; i < 10; i++) {
        if (back_readings[i] == NULL) {
          back_readings[i] = &reading;
          return;
        }
    }

    for (int i = 1; i < 10; i++) {
      back_readings[i-1] = back_readings[i];
    }
    back_readings[9] = &reading;
    return;

  }
}

bool facing_up(mpu_values reading) { return facing(reading.a_z); }
bool facing_down(mpu_values reading) { return facing(-reading.a_z); }
bool facing_right(mpu_values reading) { return facing(reading.a_y); }
bool facing_left(mpu_values reading) { return facing(-reading.a_y); }

bool facing(int value) 
{
  return (value > BOTTOM_THRESHOLD && value < TOP_THRESHOLD);
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