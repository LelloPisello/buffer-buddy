#include "../include/bb_buffer.h"
#include <stdlib.h>

// contains fundamental data about the buffer
struct bb_buffer {
  void *_location;
  size_t _height, _width, _element_size;
  bb_bool_t _is_coupled;
};

/***
 *    ███████ ███████ ████████ ████████ ███████ ██████  ███████
 *    ██      ██         ██       ██    ██      ██   ██ ██
 *    ███████ █████      ██       ██    █████   ██████  ███████
 *         ██ ██         ██       ██    ██      ██   ██      ██
 *    ███████ ███████    ██       ██    ███████ ██   ██ ███████
 *
 *
 */

// creates empty buffer, nothing pointing
bb_buffer_t *bb_buffer_create() {
  bb_buffer_t *allocation;
  allocation = malloc(sizeof(struct bb_buffer));
  allocation->_element_size = 0;
  allocation->_height = 0;
  allocation->_width = 0;
  allocation->_is_coupled = BB_FALSE;
  allocation->_location = NULL;
  return allocation;
}

// remove from heap if present, then free handle
bb_result_t bb_buffer_destroy(bb_buffer_t *target) {
  // if target == NULL return BB_FAILURE
  if (!target)
    return BB_FAILURE;
  // check whether target is binded, if it is don't destroy underlying array
  if (target->_is_coupled == BB_FALSE && target->_location) {
    free(target->_location);
  }
  free(target);
  return BB_SUCCESS;
}

// return BB_FAILURE if any of the parameters don't make sense
bb_result_t bb_buffer_bind(bb_buffer_t *target, void *to_be_binded,
                           size_t width, size_t height, size_t element_size) {
  if (!target || !to_be_binded || !width || !height || !element_size)
    return BB_FAILURE;
  target->_is_coupled = BB_TRUE;
  target->_location = to_be_binded;
  target->_width = width;
  target->_height = height;
  target->_element_size = element_size;
  return BB_SUCCESS;
}

// unbind buffer and reset handle
bb_result_t bb_buffer_unbind(bb_buffer_t *target) {
  if (!target)
    return BB_FAILURE;
  target->_is_coupled = BB_FALSE;
  target->_location = NULL;
  target->_element_size = 0;
  target->_height = 0;
  target->_width = 0;
  return BB_SUCCESS;
}

// allocate a buffer for the handle or return BB_FAILURE on error
bb_result_t bb_buffer_allocate(bb_buffer_t *target, size_t width, size_t height,
                               size_t element_size) {
  if (!target || !width || !height || !element_size)
    return BB_FAILURE;
  // delete current array if target is not binded
  if (target->_is_coupled == BB_FALSE) {
    free(target->_location);
  }
  target->_width = width;
  target->_height = height;
  target->_element_size = element_size;
  target->_is_coupled = BB_FALSE;
  target->_location = calloc(width * height, element_size);
  return BB_SUCCESS;
}

// free malloc buffer is buffer is not binded and reset handle
bb_result_t bb_buffer_deallocate(bb_buffer_t *target) {
  // if target is binded or non existent return error
  if (!target || target->_is_coupled == BB_TRUE || !target->_location)
    return BB_FAILURE;
  free(target->_location);
  target->_location = NULL;
  target->_is_coupled = BB_FALSE;
  target->_element_size = 0;
  target->_height = 0;
  target->_width = 0;
  return BB_SUCCESS;
}

/***
 *     ██████  ███████ ████████ ████████ ███████ ██████  ███████
 *    ██       ██         ██       ██    ██      ██   ██ ██
 *    ██   ███ █████      ██       ██    █████   ██████  ███████
 *    ██    ██ ██         ██       ██    ██      ██   ██      ██
 *     ██████  ███████    ██       ██    ███████ ██   ██ ███████
 *
 *
 */

// get buffer element size
size_t bb_buffer_element_size(const bb_buffer_t *target) {
  return target ? target->_element_size : 0;
}

// get buffer width / height
size_t bb_buffer_width(const bb_buffer_t *target) {
  return target ? target->_width : 0;
}
size_t bb_buffer_height(const bb_buffer_t *target) {
  return target ? target->_height : 0;
}

// check if buffer is binded
bb_bool_t bb_buffer_is_binded(const bb_buffer_t *target) {
  return target ? target->_is_coupled : 0;
}

// return target buffer data start
void *bb_buffer_data(bb_buffer_t *target) {
  return target ? target->_location : NULL;
}
