#pragma once
#include "bb_buffer.h"
#include "bb_def.h"
typedef bb_result_t (*bb_render_function_t)(void *pixel, float Nx, float Ny,
                                            void *generic_args);

// define a structure containing a rendering chain, basically a series of passes
// the renderer should apply to a buffer

// contains everything regarding a rendering pass, meaning both the number of
// threads that should execute the render and the generic render arguments

// a rendering pass is defined by 3 things: number of threads that it runs on,
// the function which gets called when it is run, and generic arguments to that
// function.

// define a rendering sequence, a structure which contains a number of rendering
// passes, + options
typedef struct bb_rendersequence bb_rendersequence_t;

// uncomment to have the rendering sequence be implemented as a linked list.
#define BB_RENDERSEQUENCE_IS_LINKED
#ifndef BB_RENDERSEQUENCE_IS_LINKED
#define BB_RENDERSEQUENCE_IS_VECTOR
#endif

// create an empty render sequence
bb_rendersequence_t *bb_rendersequence_create(void);
// destroys a render sequence, BB_FAILURE on error
bb_result_t bb_rendersequence_destroy(bb_rendersequence_t *);

// pushes back on the sequence a rendering pass
bb_result_t bb_rendersequence_push_back(bb_rendersequence_t *target,
                                        size_t thread_number,
                                        bb_render_function_t pixel_function,
                                        void *generic_args);

// pops last rendering pass from the list
bb_result_t bb_rendersequence_pop_last(bb_rendersequence_t *target);

// inserts rendering pass at specified index
bb_result_t bb_rendersequence_insert(bb_rendersequence_t *target, size_t index,
                                     size_t thread_number,
                                     bb_render_function_t pixel_function,
                                     void *generic_args);

// resizes render sequence
bb_result_t bb_rendersequence_resize(bb_rendersequence_t *target,
                                     size_t new_size);

// resizes render sequence to 0
bb_result_t bb_rendersequence_empty(bb_rendersequence_t *);

// getters:
size_t bb_rendersequence_size(const bb_rendersequence_t *);
size_t bb_rendersequence_nthreads(const bb_rendersequence_t *target,
                                  size_t index);
bb_render_function_t
bb_rendersequence_pixelfunc(const bb_rendersequence_t *target, size_t index);
void *bb_rendersequence_genargs(const bb_rendersequence_t *target,
                                size_t index);
