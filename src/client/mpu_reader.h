#include "board-peripherals.h"
#include <stdio.h>

#include "../utils.h"

/*---------------------------------------------------------------------------*/

#define SENSOR_READING_PERIOD (CLOCK_SECOND * 2)

/*---------------------------------------------------------------------------*/

void init_mpu_reading(void *);
mpu_values get_mpu_reading(void);
void print_mpu_reading(char*, int);
void print_mpu_readings(mpu_values);