#include "sys/ctimer.h"
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

  clock_time_t next = SENSOR_READING_PERIOD;

  values.g_x = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_X) / 100;

  values.g_y = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Y) / 100;

  values.g_z = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Z) / 100;

  values.a_x = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_X);

  values.a_y = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Y);

  values.a_z = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_ACC_Z);

  ctimer_set(&mpu_timer, next, init_mpu_reading, NULL);

  return values;
}

void print_mpu_reading(char* label, int reading) 
{
  printf("%s: %d\n", label, reading);
}

void print_mpu_readings(mpu_values values)
{
  printf("MPU READINGS:\n");
  print_mpu_reading("Gyro X", (int) values.g_x);
  print_mpu_reading("Gyro Y", (int) values.g_y);
  print_mpu_reading("Gyro Z", (int) values.g_z);
  print_mpu_reading("Acc X", (int) values.a_x);
  print_mpu_reading("Acc Y", (int) values.a_y);
  print_mpu_reading("Acc Z", (int) values.a_z);
  printf("\n");
}