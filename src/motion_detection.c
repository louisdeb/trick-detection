#include "motion_detection.h"
#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/

static float previous_error = 0.0;
// static float integral = 0.0;

// static double k_p = 0.5;
// static double k_i = 0.5;
// static double k_d = 2;

/*---------------------------------------------------------------------------*/

/* Currently returns the derivative value. It's ok for detecting oscillations
   but it doesn't accurately describe the frequency etc. */
// When printing floats, cast them to ints. Don't know why it's broken.
// This could be a PID function, the only thing that matters atm is derivative.
int get_oscillation(mpu_values reading)
{
  // print_mpu_readings(reading);

  float error = -reading.g_y;
  // integral = integral + error * SENSOR_READING_PERIOD;
  float derivative = (error - previous_error) * 100 / SENSOR_READING_PERIOD;
  // float pid = k_p*error + /* k_i*integral + */ k_d*derivative;
  previous_error = error;

  return (int) abs(derivative);
}