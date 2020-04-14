// list.h -- linked list macros

#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

// Insert node in front of the linked list
#define LIST_PUSH(list, node) { \
  node->next = list; \
  node->prev = NULL; \
  if (list != NULL) \
    list->prev = node; \
  list = node; \
}; \

#define LIST_REMOVE(list, node) { \
  if (node->next) node->next->prev = node->prev; \
  if (node->prev) node->prev->next = node->next; \
  else list = node->next; \
}; \

#define LIST_MOVE(list, to_list, node)

#define LIST_CLEAR(list) { \
  typeof(list) node = list; \
  while (list) { \
    node = list; \
    LIST_REMOVE(list, node); \
    free(node); \
  } \
} \

#endif