#include "bufferbuddy.h"
#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

struct bb_buffer {
  void *_buffer_location;
  size_t _buffer_format_size;
  size_t _buffer_width;
  size_t _buffer_height;
  uint8_t _is_bound;
};
