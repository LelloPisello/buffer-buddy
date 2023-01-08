#pragma once
#include <stddef.h>

#define BB_FALSE 0
#define BB_TRUE 1
#define BB_SUCCESS 0
#define BB_FAILURE 1

// contains buffer and info, such as size and format
typedef struct bb_buffer bb_buffer_t;

// prototype for rendering a single pixel from normalized screen coordinates,
// pixel info and general info
typedef int (*bb_funcrender_t)(float Nx, float Ny, void *pixel,
                               void *customargs);

// allocates and empty buffer handle
bb_buffer_t *bb_buffer_create(void);

// binds handle->buffer to an existing buffer,
int bb_buffer_bind(size_t element_size, void *binded_buffer,
                   size_t buffer_height, size_t buffer_width);
// allocates new data buffer in specified size and format, does not deallocate
// previous buffer if it was set
int bb_buffer_allocate(bb_buffer_t *buffer, size_t new_height, size_t new_width,
                       size_t element_size);
// unbinds handle from buffer to which it is bound - RM_FAILURE if buffer was
// not bound
int bb_buffer_unbind(bb_buffer_t *);
// deallocates the buffer referred to by the handle and resets format and size -
// RM_FAILURE if buffer was not allocated or if it was bound
int bb_buffer_deallocate(bb_buffer_t *);
// returns whether buffer is bound RM_TRUE / RM_FALSE
int bb_buffer_is_bound(const bb_buffer_t *);
// returns size of buffer, meaning total size in bytes
size_t bb_buffer_size(const bb_buffer_t *);
// returns width / height of buffer
size_t bb_buffer_width(const bb_buffer_t *);
size_t bb_buffer_height(const bb_buffer_t *);
// destroys rm_buffer, deallocates buffer if it is not bound but set -
// RM_FAILURE if argument passed is NULL
int bb_buffer_destroy(bb_buffer_t *);

// generic_args makes it simple to create your own rendering logic inside a
// rm_funcrender_t function
int bb_buffer_render(bb_buffer_t *buffer, bb_funcrender_t function,
                     void *generic_args);
// same as buffer_render but runs on multiple threads
int bb_buffer_render_threaded(bb_buffer_t *buffer, bb_funcrender_t function,
                              void *generic_args, size_t thread_number);
