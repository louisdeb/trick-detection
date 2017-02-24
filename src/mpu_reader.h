#include "contiki.h"
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include "dev/leds.h"
#include "dev/watchdog.h"
#include "random.h"
#include "button-sensor.h"
#include "batmon-sensor.h"
#include "board-peripherals.h"
#include "rf-core/rf-ble.h"

#include "ti-lib.h"

#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL (CLOCK_SECOND * 2)
#define BUTTON_LEFT &button_left_sensor
#define SENSOR_READING_PERIOD (CLOCK_SECOND * 2)
#define SENSOR_READING_RANDOM (CLOCK_SECOND << 4) 
/*---------------------------------------------------------------------------*/

struct mpu_values {
  int g_x;
  int g_y;
  int g_z;

  int a_x;
  int a_y;
  int a_z;
};

typedef struct mpu_values mpu_values;

void init_mpu_reading(void *);
void print_mpu_reading(int);
mpu_values get_mpu_reading(void);