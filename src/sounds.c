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

static struct etimer et;
static struct ctimer mpu_timer;

/*---------------------------------------------------------------------------*/

static void init_mpu_reading(void *not_used);

/*---------------------------------------------------------------------------*/

PROCESS(sound_process, "sound process");
AUTOSTART_PROCESSES(&sound_process);

/*---------------------------------------------------------------------------*/

static void
print_mpu_reading(int reading)
{
  if(reading < 0) {
    printf("-");
    reading = -reading;
  }

  printf("%d.%02d", reading / 100, reading % 100);
}

static void
get_mpu_reading()
{
  int value;
  clock_time_t next = SENSOR_READING_PERIOD +
    (random_rand() % SENSOR_READING_RANDOM);

  printf("MPU Gyro: X=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_X);
  print_mpu_reading(value);
  printf(" deg/sec\n");

  printf("MPU Gyro: Y=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Y);
  print_mpu_reading(value);
  printf(" deg/sec\n");

  printf("MPU Gyro: Z=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Z);
  print_mpu_reading(value);
  printf(" deg/sec\n");

  printf("MPU Acc: X=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_X);
  print_mpu_reading(value);
  printf(" G\n");

  printf("MPU Acc: Y=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Y);
  print_mpu_reading(value);
  printf(" G\n");

  printf("MPU Acc: Z=");
  value = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Z);
  print_mpu_reading(value);
  printf(" G\n");

  ctimer_set(&mpu_timer, next, init_mpu_reading, NULL);
}

static void
init_mpu_reading(void *not_used)
{
  mpu_9250_sensor.configure(SENSORS_ACTIVE, MPU_9250_SENSOR_TYPE_ALL);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sound_process, ev, data)
{
  PROCESS_BEGIN();

  
  etimer_set(&et, LOOP_INTERVAL);

  init_mpu_reading(NULL);

  while(1) 
  {
    PROCESS_YIELD();
    if(ev == PROCESS_EVENT_TIMER) {
      if(data == &et) {
        etimer_set(&et, LOOP_INTERVAL);
      }
    } else if(ev == sensors_event && data == &mpu_9250_sensor) {
      get_mpu_reading();
    }

    if (data == BUTTON_LEFT) {
      leds_toggle(LEDS_RED); // toggle led
      if (buzzer_state()) { // toggle buzzer
        buzzer_stop();
      } else {
        buzzer_start(1000);
      }
    }
  }

  PROCESS_END();
}