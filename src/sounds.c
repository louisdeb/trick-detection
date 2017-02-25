#include "contiki.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "button-sensor.h"
#include "rf-core/rf-ble.h"

#include "ti-lib.h"
#include <stdio.h>
#include <stdint.h>

#include "mpu_reader.h"

/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL (CLOCK_SECOND * 2)
#define BUTTON_LEFT &button_left_sensor

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
    mpu_values values = get_mpu_reading();
    print_mpu_readings(values);

    if (data == BUTTON_LEFT) {
      leds_toggle(LEDS_RED); // toggle led
      
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
