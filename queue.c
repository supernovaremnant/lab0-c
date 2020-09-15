#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

// From "Common vulnerabilities guide for C programmers"
// Use strlcpy instead of strcpy to avoid overwrite
// https://security.web.cern.ch/recommendations/en/codetools/c.shtml
#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    // strlen calculates the lenght of C string
    //(without including the terminating null character itself).
    int strLen = strlen(s) + 1;
    list_ele_t *newHead = (list_ele_t *) malloc(sizeof(list_ele_t));
    char *val = (char *) malloc(sizeof(char) * strLen);

    // either one of malloc fail to allocate memory
    if (!newHead || !val) {
        free(newHead);
        free(val);
        return false;
    }

    strlcpy(val, s, strLen);

    newHead->value = val;
    newHead->next = q->head;
    q->head = newHead;
    if (q->size == 0) {  // empty queue
        q->tail = newHead;
    }
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;

    int strLen = strlen(s) + 1;
    list_ele_t *newTail = (list_ele_t *) malloc(sizeof(list_ele_t));
    char *val = (char *) malloc(sizeof(char) * strLen);

    if (!newTail || !val) {
        free(newTail);
        free(val);
        return false;
    }

    strlcpy(val, s, strLen);

    newTail->value = val;
    newTail->next = NULL;

    if (q->size == 0) {  // empty queue
        q->head = newTail;
    } else {
        q->tail->next = newTail;
    }
    q->tail = newTail;
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !sp || !q->head)
        return false;

    list_ele_t *rmElem = q->head;
    int strLen = strlen(rmElem->value) + 1;
    size_t realBufSize = bufsize > strLen ? strLen : bufsize;

    strlcpy(sp, rmElem->value, realBufSize);

    q->head = q->head->next;
    q->size--;

    free(rmElem->value);
    free(rmElem);

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    else
        return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
