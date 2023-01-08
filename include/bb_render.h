#pragma once
#include "bb_buffer.h"
#include "bb_def.h"
typedef bb_result_t (*bb_render_function_t)(void *pixel, float Nx, float Ny,
                                            void *generic_args);

// IMPORTANT: CONSIDER RENDERING THE RENDER PASS STRUCTURE VISIBLE, SO THAT
// RENDERING SEQUENCES CAN BE CHANGED

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
extern bb_rendersequence_t *bb_rendersequence_create(void);
// destroys a render sequence, BB_FAILURE on error
extern bb_result_t bb_rendersequence_destroy(bb_rendersequence_t *);

// pushes back on the sequence a rendering pass
extern bb_result_t
bb_rendersequence_push_back(bb_rendersequence_t *target, size_t thread_number,
                            bb_render_function_t pixel_function,
                            void *generic_args);

// pops last rendering pass from the list
extern bb_result_t bb_rendersequence_pop_last(bb_rendersequence_t *target);

// inserts rendering pass at specified index
extern bb_result_t bb_rendersequence_insert(bb_rendersequence_t *target,
                                            size_t index, size_t thread_number,
                                            bb_render_function_t pixel_function,
                                            void *generic_args);

// resizes render sequence
extern bb_result_t bb_rendersequence_resize(bb_rendersequence_t *target,
                                            size_t new_size);

// resizes render sequence to 0
extern bb_result_t bb_rendersequence_empty(bb_rendersequence_t *);

// getters:
extern size_t bb_rendersequence_size(const bb_rendersequence_t *);
extern size_t bb_rendersequence_nthreads(const bb_rendersequence_t *target,
                                         size_t index);
extern bb_render_function_t
bb_rendersequence_pixelfunc(const bb_rendersequence_t *target, size_t index);
extern void *bb_rendersequence_genargs(const bb_rendersequence_t *target,
                                       size_t index);
