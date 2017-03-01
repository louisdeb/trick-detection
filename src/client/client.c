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

#define LOOP_INTERVAL           CLOCK_SECOND
#define NODE_ID                 FRONT

/*---------------------------------------------------------------------------*/

static struct etimer et;
static struct mpu_values mpu_reading; // current mpu reading

/*---------------------------------------------------------------------------*/

PROCESS(client_process, "client process");
AUTOSTART_PROCESSES(&client_process);

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(client_process, ev, data)
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

    comms_packet packet;
    packet.node_id = NODE_ID;
    packet.mpu_reading = mpu_reading;
    comms_broadcast(packet);
  } // end-while

  PROCESS_END();
}
