#include "scale.h"

/*---------------------------------------------------------------------------*/

static float ratios[13] = {1.0, 1.05946, 1.12246, 1.18921, 1.25992, 1.33483, 
                           1.41421, 1.49831, 1.58740, 1.68179, 1.78180, 1.88775, 
                           2.0};

static int major[8] = {0, 2, 4, 5, 7, 9, 11, 12};

float get_note(float root_frequency, int note_index)
{
  return root_frequency * ratios[major[note_index]];
}