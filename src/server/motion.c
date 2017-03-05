#include "motion.h"
#include "contiki.h"
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

#define HISTORY_SIZE        10
#define BOTH_HISTORY_SIZE   HISTORY_SIZE * 2

#define DIRECTION_TRUE      100
#define DIRECTION_LEEWAY    20

#define ROTATION_THRESHOLD  150
#define VERTICAL_THRESHOLD  5

#define BOTTOM_THRESHOLD    (DIRECTION_TRUE - DIRECTION_LEEWAY)
#define TOP_THRESHOLD       (DIRECTION_TRUE + DIRECTION_LEEWAY)

/*---------------------------------------------------------------------------*/

mpu_values front_history[HISTORY_SIZE];
mpu_values back_history[HISTORY_SIZE];
mpu_values history[HISTORY_SIZE * 2];

Trick previous_trick = no_trick;

void process_packet(comms_packet packet)
{
  // printf("got packet from %s\n", (packet.node_id == 0 ? "FRONT" : "BACK"));
  // print_reading(packet.mpu_reading);
  add_reading(packet.node_id, packet.mpu_reading);

  Roll roll = detect_roll(history);
  Pop pop = detect_pop(front_history, back_history);
  Spin spin = detect_spin(history);

  Trick trick = get_trick(roll, pop, spin);
  if (trick == no_trick && previous_trick != no_trick) {
    printf("Trick: %s\n", get_trick_string(previous_trick));
    previous_trick = trick;
  }

  if ((previous_trick != no_trick && trick != ollie && trick != nollie 
      && trick != no_trick) || previous_trick == no_trick) {
    previous_trick = trick;
  }
} // we are printing ollie instead of nollie

/*---------------------------------------------------------------------------*/

int has_state(bool (*test)(mpu_values), int start_index, mpu_values readings[], int readings_size) 
{
  for (int i = start_index; i < readings_size; i++) {
    if (&readings[i] != NULL && test(readings[i])) {
      return i;
    }
  }
  return -1;
}

/*---------------------------------------------------------------------------*/

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
    return (left <= right) ? kick : heel;
  }

  return no_roll;
}

Pop detect_pop(mpu_values front_readings[HISTORY_SIZE], mpu_values back_readings[HISTORY_SIZE])
{
  int back_up = has_state(ascending, 0, back_readings, HISTORY_SIZE);
  int front_up = has_state(ascending, 0, front_readings, HISTORY_SIZE);

  if (back_up == -1 && front_up == -1)
    return no_pop;

  return (front_up < back_up) ? tail : nose;
}

// Changed to both history - maybe doesn't need to be
Spin detect_spin(mpu_values readings[BOTH_HISTORY_SIZE])
{
  if (has_state(rotating_clockwise, 0, readings, BOTH_HISTORY_SIZE) != -1) {
    return backside;
  }

  if (has_state(rotating_anticlockwise, 0, readings, BOTH_HISTORY_SIZE) != -1) {
    return frontside;
  }
  
  return no_spin;
}

/*---------------------------------------------------------------------------*/

bool facing_up(mpu_values reading) { return facing(reading.a_z); }
bool facing_down(mpu_values reading) { return facing(-reading.a_z); }
bool facing_right(mpu_values reading) { return facing(reading.a_y); }
bool facing_left(mpu_values reading) { return facing(-reading.a_y); }

bool rotating_clockwise(mpu_values reading) {
  // print_reading(reading);
  return reading.g_z > ROTATION_THRESHOLD;
}

bool rotating_anticlockwise(mpu_values reading) {
  return reading.g_z < -ROTATION_THRESHOLD;
}

bool ascending(mpu_values reading) {
  return reading.g_y > VERTICAL_THRESHOLD;
}

bool descending(mpu_values reading) {
  return reading.g_y < -VERTICAL_THRESHOLD;
}

bool facing(int value) 
{
  return (value > BOTTOM_THRESHOLD && value < TOP_THRESHOLD);
}

bool at_origin(mpu_values reading)
{
  return (facing_up(reading) && !rotating_clockwise(reading) 
          && !rotating_anticlockwise(reading));
}

/*---------------------------------------------------------------------------*/

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

// -Wnonnull doesn't like setting the histories to '0'
void reset_histories()
{
  mpu_values no_reading;
  no_reading.a_x = 0;
  no_reading.a_y = 0;
  no_reading.a_z = 0;
  no_reading.g_x = 0;
  no_reading.g_y = 0;
  no_reading.g_z = 0;

  memmove(front_history, &no_reading, HISTORY_SIZE*sizeof(mpu_values));
  memmove(back_history,  &no_reading, HISTORY_SIZE*sizeof(mpu_values));
  memmove(history,       &no_reading, BOTH_HISTORY_SIZE*sizeof(mpu_values));
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
