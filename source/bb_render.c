#include "../include/bb_render.h"
#include <stdlib.h>

// if render sequence should be a linked list add _next
struct rendersequencenode {
#ifdef BB_RENDERSEQUENCE_IS_LINKED
  struct rendersequencenode *_next;
#endif
  size_t _thread_number;
  bb_render_function_t _pixel_function;
  void *_generic_args;
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

// data structure
struct bb_rendersequence {
#ifdef BB_RENDERSEQUENCE_IS_LINKED
  struct rendersequencenode *_head;
#endif
#ifdef BB_RENDERSEQUENCE_IS_VECTOR
  struct rendersequencenode *head, *tail;
#endif
};

// create render sequence (independent)
bb_rendersequence_t *bb_rendersequence_create(void) {
  bb_rendersequence_t *allocation = calloc(1, sizeof(struct bb_rendersequence));
  return allocation;
}

// delete every rendering sequence rendering pass, if they exist
bb_result_t bb_rendersequence_empty(bb_rendersequence_t *target) {
  if (!target)
    return BB_FAILURE;
#ifdef BB_RENDERSEQUENCE_IS_LINKED
  if (!target->_head)
    return BB_FAILURE;
  while (target->_head->_next) {
    struct rendersequencenode *p;
    for (p = target->_head; p->_next; p = p->_next)
      ;
    free(p->_next);
    p->_next = NULL;
  }
  free(target->_head);
  target->_head = NULL;
#endif
#ifdef BB_RENDERSEQUENCE_IS_VECTOR
  if (!target->_head || !target->tail)
    return BB_FAILURE;
  free(target->_head);
  target->_head = NULL;
  target->_tail = NULL;
#endif
  return BB_SUCCESS;
}

bb_result_t bb_rendersequence_destroy(bb_rendersequence_t *target) {
  if (!target)
    return BB_FAILURE;
  bb_rendersequence_empty(target);
  free(target);
  return BB_SUCCESS;
}
