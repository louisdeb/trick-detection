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

#include "mpu_reader.h"

#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL (CLOCK_SECOND * 2)
#define BUTTON_LEFT &button_left_sensor
#define SENSOR_READING_PERIOD (CLOCK_SECOND * 2)
#define SENSOR_READING_RANDOM (CLOCK_SECOND << 4) 

/*---------------------------------------------------------------------------*/

static struct etimer et;

/*---------------------------------------------------------------------------*/


PROCESS(sound_process, "sound process");
AUTOSTART_PROCESSES(&sound_process);

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
    }
    // } else if(ev == sensors_event && data == &mpu_9250_sensor) {
      
    // }

    if (data == BUTTON_LEFT) {
      leds_toggle(LEDS_RED); // toggle led
      mpu_values values = get_mpu_reading();
      if (buzzer_state()) { // toggle buzzer
        buzzer_stop();
      } else {
        int freq = abs(values.a_x) * 100;
        printf("Freq: %d", freq);
        buzzer_start(freq);
      }
    }
  }

  PROCESS_END();
}
