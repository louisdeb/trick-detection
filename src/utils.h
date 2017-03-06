/*---------------------------------------------------------------------------*/

// Variables identify where the sensortag is on the board
#define FRONT                   0
#define BACK                    1

// Communication broadcast channel
#define BROADCAST_CHANNEL 420

/*---------------------------------------------------------------------------*/

// A container for accelerometer readings
struct mpu_values
{  
  float g_x;
  float g_y;
  float g_z;

  int a_x;
  int a_y;
  int a_z;
};

typedef struct mpu_values mpu_values;

/*---------------------------------------------------------------------------*/

// A packet format, sent from node to node
struct comms_packet 
{
  int node_id;
  struct mpu_values mpu_reading;
};

typedef struct comms_packet comms_packet;

/*---------------------------------------------------------------------------*/