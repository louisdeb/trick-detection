#include "../utils.h"
#include "tricks.h"
#include <stdbool.h>

/*---------------------------------------------------------------------------*/

void process_packet(comms_packet);

void add_reading(int, mpu_values);
void print_reading(mpu_values);

Roll detect_roll(mpu_values[]);
Pop detect_pop(mpu_values[], mpu_values[]);
Spin detect_spin(mpu_values[]);

bool facing_up(mpu_values);
bool facing_down(mpu_values);
bool facing_right(mpu_values);
bool facing_left(mpu_values);
bool facing(int);

bool rotating_clockwise(mpu_values);
bool rotating_anticlockwise(mpu_values);
