#include "contiki.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "button-sensor.h"
#include "rf-core/rf-ble.h"

#include "ti-lib.h"
#include <stdio.h>
#include <stdint.h>

#include "motion_detection.h"
#include "comms.h"
#include "scale.h"

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

/* Not having state checks for playing and stopping the buzzer causes
   the tag to crash. */
void play_frequency(int freq)
{
  if (!buzzer_state()) {
    buzzer_start(freq);
  }
}

void stop_buzzer()
{
  if (buzzer_state()) {
    buzzer_stop();
  }
}

int oscillation_to_frequency(int oscillation)
{
  return oscillation * 50; // turn some oscillation value into some frequency
  // might also use frequencies given to it from other nodes so that it
  // can harmonise
  // that would give this function purpose enough to have its own file
  // where we can also store information from other nodes
}

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
    int oscillation = get_oscillation(mpu_reading);
    printf("got oscillation value: %d\n", oscillation);

    if (oscillation > OSCILLATION_THRESHOLD) {
      int frequency = oscillation_to_frequency(oscillation);

      comms_packet packet;
      packet.oscillation_value = oscillation;
      comms_broadcast(packet);

      play_frequency(frequency);
    } else {
      stop_buzzer();
    }

  } // end-while

  PROCESS_END();
}
