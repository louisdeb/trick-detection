#include "contiki.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "button-sensor.h"
#include "rf-core/rf-ble.h"

#include "ti-lib.h"
#include <stdio.h>
#include <stdint.h>

#include "comms.h"

/*---------------------------------------------------------------------------*/

#define LOOP_INTERVAL           (CLOCK_SECOND * 2)
#define OSCILLATION_THRESHOLD   1

#define BUTTON_LEFT             &button_left_sensor

/*---------------------------------------------------------------------------*/

static struct etimer et;
static struct mpu_values mpu_reading;

/*---------------------------------------------------------------------------*/

PROCESS(sound_process, "sound process");
AUTOSTART_PROCESSES(&sound_process);

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(sound_process, ev, data)
{
  PROCESS_BEGIN();
  
  etimer_set(&et, LOOP_INTERVAL);

  init_mpu_reading(NULL);
  init_comms();

  while(1) 
  {
    PROCESS_YIELD();
    if(ev == PROCESS_EVENT_TIMER) {
      if(data == &et) {
        etimer_set(&et, LOOP_INTERVAL);
      }
    }
    
    mpu_reading = get_mpu_reading();
    comms_broadcast(mpu_reading);
  } // end-while

  PROCESS_END();
}
