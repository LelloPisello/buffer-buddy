#pragma once
#include "bb_buffer.h"
#include "bb_def.h"
typedef bb_result_t (*bb_render_function_t)(void *pixel, float Nx, float Ny,
                                            void *generic_args);

// define a structure containing a rendering chain, basically a series of passes
// the renderer should apply to a buffer
