#pragma once

#include "bb_def.h"
typedef struct bb_buffer bb_buffer_t;

// translate the whole 2D buffer thing to a single array

// buffers are strictly 2 dimensional
// creates an empty buffer handle
extern bb_buffer_t *bb_buffer_create(void);
// returns BB_SUCCESS on deallocation and BB_FAILURE on unsuccesful deallocation
extern bb_result_t bb_buffer_destroy(bb_buffer_t *);
// binding
// binds a buffer handle to an existing buffer, returns BB_FAILURE if any
// parameter is 0 or NULL
extern bb_result_t bb_buffer_bind(bb_buffer_t *target, void *to_be_binded,
                                  size_t length, size_t element_size);
// decouples the handle from the buffer to which it was bounded, BB_FAILURE if
// target is NULL or if target is not binded
extern bb_result_t bb_buffer_unbind(bb_buffer_t *target);
// allocates a buffer on the heap with the specified size
extern bb_result_t bb_buffer_allocate(bb_buffer_t *target, size_t length,
                                      size_t element_size);
// returns BB_FAILURE if parameter is NULL, or if target is binded or not
// allocated, otherwise deallocates the buffer to which it points and resets the
// handle
extern bb_result_t bb_buffer_deallocate(bb_buffer_t *);
// returns BB_FAILURE if parameter is NULL, otherwise destroys both buffer and
// handle. buffer does not get destroyed if it is binded.
extern bb_bool_t bb_buffer_is_binded(const bb_buffer_t *);
// returns buffer number of elements
extern size_t bb_buffer_length(const bb_buffer_t *);
// returns buffer size in bytes
extern size_t bb_buffer_size(const bb_buffer_t *);
// returns buffer element size
extern size_t bb_buffer_element_size(const bb_buffer_t *);
// returns buffer data
extern void *bb_buffer_data(bb_buffer_t *);
