#pragma once
#include "bb_buffer.h"
#include "bb_def.h"

// bb_render_function_t will be updated to use outside compiled shader code
// you can pass buffer size or eventual multiple dimensions by generic_args
typedef bb_result_t (*bb_render_function_t)(void *item, size_t item_index,
                                            void *generic_args);

// a rendering step contains the following info:
// - number of items a single thread should process,
// - the maximum number of threads to be called,
// - the function a thread should run on its items,
// - a pointer to the generic_args the render function requires, which should be
//   allocated on the heap.

// rendering steps are contained in a rendering chain: an object which contains
// an arbitrary number of rendering steps and holds the threads the rendering is
// going to run on.

// the rendering chain is by default implemented as a linked list: a vector
// version may be added in the future.
typedef struct bb_render_chain bb_render_chain_t;

// a rendering chain can be in one of two states: locked and unlocked.
// while the chain is unlocked it can be edited and rendering steps can be
// pushed onto it, but it cannot be run on a buffer.
