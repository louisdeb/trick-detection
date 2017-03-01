#include "../utils.h"
#include <stdbool.h>

/*---------------------------------------------------------------------------*/

void process_packet(comms_packet);

void add_reading(int, mpu_values);
void print_reading(mpu_values);


void detect_one_direction_roll(mpu_values[]);
void detect_roll(mpu_values[]);
bool facing_up(mpu_values);
bool facing_down(mpu_values);
bool facing_right(mpu_values);
bool facing_left(mpu_values);
bool facing(int);
