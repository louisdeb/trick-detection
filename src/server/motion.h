#include "../utils.h"
#include "tricks.h"
#include <stdbool.h>

/*---------------------------------------------------------------------------*/

void process_packet(comms_packet);

Roll detect_roll(mpu_values[]);
Pop detect_pop(mpu_values[], mpu_values[]);
Spin detect_spin(mpu_values[]);

// Accelerometer Data
bool facing_up(mpu_values);
bool facing_down(mpu_values);
bool facing_right(mpu_values);
bool facing_left(mpu_values);
bool facing(int);

// Gyroscope Data
bool rotating_clockwise(mpu_values);
bool rotating_anticlockwise(mpu_values);
bool ascending(mpu_values);
bool descending(mpu_values);

bool at_origin(mpu_values);

void add_reading(int, mpu_values);
void reset_histories(void);
void print_reading(mpu_values);
