#include "../include/bb_buffer.h"
#include <stdlib.h>

// contains fundamental data about the buffer
struct bb_buffer {
  void *_location;
  size_t _length, _element_size;
  bb_bool_t _is_coupled, _is_locked;
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
  allocation->_length = 0;
  allocation->_is_coupled = BB_FALSE;
  allocation->_is_locked = BB_FALSE;
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
                           size_t length, size_t element_size) {
  if (!target || target->_is_locked == BB_TRUE || !to_be_binded || !length ||
      !element_size)
    return BB_FAILURE;
  target->_is_coupled = BB_TRUE;
  target->_location = to_be_binded;
  target->_length = length;
  target->_element_size = element_size;
  return BB_SUCCESS;
}

// unbind buffer and reset handle
bb_result_t bb_buffer_unbind(bb_buffer_t *target) {
  if (!target || target->_is_locked == BB_TRUE)
    return BB_FAILURE;
  target->_is_coupled = BB_FALSE;
  target->_location = NULL;
  target->_element_size = 0;
  target->_length = 0;
  return BB_SUCCESS;
}

// allocate a buffer for the handle or return BB_FAILURE on error
bb_result_t bb_buffer_allocate(bb_buffer_t *target, size_t length,
                               size_t element_size) {
  if (!target || target->_is_locked == BB_TRUE || !length || !element_size)
    return BB_FAILURE;
  // delete current array if target is not binded
  if (target->_is_coupled == BB_FALSE) {
    free(target->_location);
  }
  target->_length = length;
  target->_element_size = element_size;
  target->_is_coupled = BB_FALSE;
  target->_location = calloc(length, element_size);
  return BB_SUCCESS;
}

// free malloc buffer is buffer is not binded and reset handle
bb_result_t bb_buffer_deallocate(bb_buffer_t *target) {
  // if target is binded or non existent return error
  if (!target || target->_is_locked == BB_TRUE ||
      target->_is_coupled == BB_TRUE || !target->_location)
    return BB_FAILURE;
  free(target->_location);
  target->_location = NULL;
  target->_is_coupled = BB_FALSE;
  target->_element_size = 0;
  target->_length = 0;
  return BB_SUCCESS;
}

bb_result_t bb_buffer_lock(bb_buffer_t *target) {
  if (!target || target->_is_locked)
    return BB_FAILURE;
  target->_is_locked = BB_TRUE;
  return BB_SUCCESS;
}

bb_result_t bb_buffer_unlock(bb_buffer_t *target) {
  if (!target || !target->_is_locked)
    return BB_FAILURE;
  target->_is_locked = BB_FALSE;
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

size_t bb_buffer_length(const bb_buffer_t *target) {
  return target ? target->_length : 0;
}

// get buffer width / height
size_t bb_buffer_size(const bb_buffer_t *target) {
  return target ? target->_length * target->_element_size : 0;
}

// check if buffer is binded
bb_bool_t bb_buffer_is_binded(const bb_buffer_t *target) {
  return target ? target->_is_coupled : 0;
}

// return target buffer data start if target is not locked
void *bb_buffer_data(bb_buffer_t *target) {
  return target ? target->_location : NULL;
}

// return buffer locking status
bb_bool_t bb_buffer_is_locked(const bb_buffer_t *buffer) {
  return buffer->_is_locked;
}
