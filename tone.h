#ifndef _TONE
#define _TONE

#include <pthread.h>

typedef enum {D0 = 0x01,
              D1 = 0x02,
              D2 = 0x04,
              D3 = 0x08,
              D4 = 0x10,
              D5 = 0x20,
              D6 = 0x40,
              D7 = 0x80}
    parallel_pin;

void lpt_init ();

void tone (int freq, double duration, parallel_pin pin);

#endif

