/*---------------------------------------------------------------------------*/

// Variables identify where the sensortag is on the board
#define FRONT                   0
#define BACK                    1

/*---------------------------------------------------------------------------*/

struct mpu_values
{
  unsigned long read_time;
  
  float g_x;
  float g_y;
  float g_z;

  int a_x;
  int a_y;
  int a_z;
};

typedef struct mpu_values mpu_values;

/*---------------------------------------------------------------------------*/

struct comms_packet 
{
  int node_id;
  struct mpu_values mpu_reading;
};

typedef struct comms_packet comms_packet;

/*---------------------------------------------------------------------------*/