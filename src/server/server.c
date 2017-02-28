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
  init_comms();

  PROCESS_END();
}