#include "motion.h"
#include "contiki.h"
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

#define DIRECTION_TRUE      100
#define DIRECTION_LEEWAY    30

#define BOTTOM_THRESHOLD    (DIRECTION_TRUE - DIRECTION_LEEWAY)
#define TOP_THRESHOLD       (DIRECTION_TRUE + DIRECTION_LEEWAY)

/*---------------------------------------------------------------------------*/

mpu_values front_readings[10];
mpu_values back_readings[10];


void process_packet(comms_packet packet)
{
  mpu_values new_value;
  new_value = packet.mpu_reading;

  printf("Node Id: %d\n", packet.node_id);
  print_reading(new_value);
  add_reading(packet.node_id, packet.mpu_reading);

  //detect_roll(*front_readings);
  detect_one_direction_roll(front_readings);
}

int has_state(bool (*test)(mpu_values), int start_index, mpu_values readings[10]) 
{
  for (int i = start_index; i < 10; i++) {
    if (test(readings[i])) {
      return i;
    }
  }
  return -1;
}

void detect_one_direction_roll(mpu_values readings[10]) {
  int up    = has_state(facing_up, 0, readings);
  int left  = has_state(facing_left, 0, readings);
  int right = has_state(facing_right, 0, readings);
  int down  = has_state(facing_down, 0, readings);
  printf("Up: %d\n", up);
  printf("Left: %d\n", left);
  printf("Right: %d\n", right);
  printf("Down: %d\n", down);
}

void detect_roll(mpu_values readings[10])
{

  //mpu_values readings[10];
  //memcpy(readings, readings_global, sizeof(readings));

  int up = has_state(facing_up, 0, readings);
  if (up == -1) { return; }
  int left = has_state(facing_left, up, readings);
  int right = has_state(facing_right, up, readings);
  int down = has_state(facing_down, up, readings);
  int returning_state = -1;
  if (left != 1 || right != -1 || down != -1) {
    returning_state = MAX(MAX(left, right), down);
  }

  int up_again = -1;

  if (returning_state != -1) {
    up_again = has_state(facing_up, returning_state, readings);
  }

  printf("Started at up(%d), found left(%d), right(%d), down(%d), and up_again(%d)\n", up, left, right, down, up_again);
}

void print_direction(mpu_values reading) {
  if (facing_up(reading)) {
    printf("UP\n");
  } else if (facing_down(reading)) {
    printf("DOWN\n");
  } else if (facing_left(reading)) {
    printf("LEFT\n");
  } else if (facing_right(reading)) {
    printf("RIGHT\n");
  }
}

void add_reading(int id, mpu_values reading)
{
  if (id == FRONT) {
    memmove(&front_readings, &(front_readings[1]), 9*sizeof(mpu_values));
    front_readings[9] = reading;
    for (int i = 0; i < 10; i++) {
      print_direction(front_readings[i]);
    }
    //printf("Shifted reading's left and added tobacco\n");
  } 
  if (id == BACK) {
    memmove(&back_readings, &(back_readings[1]), 9*sizeof(mpu_values));
    back_readings[9] = reading;
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
