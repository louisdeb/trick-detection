#include "mpu_reader.h"

/*---------------------------------------------------------------------------*/

static struct ctimer mpu_timer;

/*---------------------------------------------------------------------------*/

void
init_mpu_reading(void *not_used)
{
  mpu_9250_sensor.configure(SENSORS_ACTIVE, MPU_9250_SENSOR_TYPE_ALL);
}

mpu_values
get_mpu_reading(void)
{

  mpu_values values;

  clock_time_t next = SENSOR_READING_PERIOD +
    (random_rand() % SENSOR_READING_RANDOM);

  values.g_x = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_X);

  values.g_y = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Y);

  values.g_z = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Z);

  values.a_x = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_X);

  values.a_y = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Y);

  values.a_z = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Z);

  ctimer_set(&mpu_timer, next, init_mpu_reading, NULL);

  return values;
}

void print_mpu_reading(int reading) {
  printf("Reading: %d", reading);
}