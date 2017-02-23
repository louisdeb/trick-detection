#include "contiki.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "button-sensor.h"
#include "batmon-sensor.h"
#include "board-peripherals.h"

#include "ti-lib.h"

#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL (CLOCK_SECOND * 20) // shouldn't be required in sounds.c
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

  while(1) 
  {
    PROCESS_YIELD();
    etimer_set(&et, LOOP_INTERVAL);

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