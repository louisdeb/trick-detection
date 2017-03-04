#include "motion.h"
#include "contiki.h"
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

#define HISTORY_SIZE        10
#define BOTH_HISTORY_SIZE   HISTORY_SIZE * 2

#define DIRECTION_TRUE      100
#define DIRECTION_LEEWAY    10

#define BOTTOM_THRESHOLD    (DIRECTION_TRUE - DIRECTION_LEEWAY)
#define TOP_THRESHOLD       (DIRECTION_TRUE + DIRECTION_LEEWAY)

/*---------------------------------------------------------------------------*/

mpu_values front_history[HISTORY_SIZE];
mpu_values back_history[HISTORY_SIZE];
mpu_values history[HISTORY_SIZE * 2];

void process_packet(comms_packet packet)
{
  printf("got packet from %s\n", (packet.node_id == 0 ? "FRONT" : "BACK"));
  print_reading(packet.mpu_reading);
  add_reading(packet.node_id, packet.mpu_reading);

  Roll roll = detect_roll(history);
  Pop pop = detect_pop(front_history, back_history);
  // use data to determine trick
  // clear history when we know we have a trick
}

int has_state(bool (*test)(mpu_values), int start_index, mpu_values readings[], int readings_size) 
{
  for (int i = start_index; i < readings_size; i++) {
    if (test(readings[i])) {
      return i;
    }
  }
  return -1;
}

// Returns a Roll based on the orientation readings from the MPU
// Uses the interleaved history, "history", which has readings from both sensors
// Could be improved using acceleration readings
Roll detect_roll(mpu_values readings[BOTH_HISTORY_SIZE])
{
  int up = has_state(facing_up, 0, readings, BOTH_HISTORY_SIZE);
  if (up == -1) { return no_roll; }
  int left = has_state(facing_left, up, readings, BOTH_HISTORY_SIZE);
  int right = has_state(facing_right, up, readings, BOTH_HISTORY_SIZE);
  int down = has_state(facing_down, up, readings, BOTH_HISTORY_SIZE);
  int returning_state = -1;
  if (left != 1 || right != -1 || down != -1) {
    returning_state = MAX(MAX(left, right), down);
  }

  int up_again = -1;
  if (returning_state != -1) {
    up_again = has_state(facing_up, returning_state, readings, BOTH_HISTORY_SIZE);
  }

  if (up < down && down < up_again) {
    return (left < right) ? kick : heel;
  }

  return no_roll;
}

Pop detect_pop(mpu_values front_readings[HISTORY_SIZE], mpu_values back_readings[HISTORY_SIZE])
{
  return no_pop;
}

bool facing_up(mpu_values reading) { return facing(reading.a_z); }
bool facing_down(mpu_values reading) { return facing(-reading.a_z); }
bool facing_right(mpu_values reading) { return facing(reading.a_y); }
bool facing_left(mpu_values reading) { return facing(-reading.a_y); }

bool facing(int value) 
{
  return (value > BOTTOM_THRESHOLD && value < TOP_THRESHOLD);
}

void add_reading(int id, mpu_values reading)
{
  if (id == FRONT) {
    memmove(&front_history, &(front_history[1]), (HISTORY_SIZE-1)*sizeof(mpu_values));
    front_history[(HISTORY_SIZE-1)] = reading;
  } 
  if (id == BACK) {
    memmove(&back_history, &(back_history[1]), (HISTORY_SIZE-1)*sizeof(mpu_values));
    back_history[(HISTORY_SIZE-1)] = reading;
  }

  memmove(&history, &(history[1]), (BOTH_HISTORY_SIZE-1)*sizeof(mpu_values));
  history[(BOTH_HISTORY_SIZE-1)] = reading;
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
