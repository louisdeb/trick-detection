#include "board-peripherals.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

#define SENSOR_READING_PERIOD (CLOCK_SECOND * 2)

/*---------------------------------------------------------------------------*/

struct mpu_values {
  float g_x;
  float g_y;
  float g_z;

  int a_x;
  int a_y;
  int a_z;
};

typedef struct mpu_values mpu_values;

void init_mpu_reading(void *);
mpu_values get_mpu_reading(void);
void print_mpu_reading(char*, int);
void print_mpu_readings(mpu_values);