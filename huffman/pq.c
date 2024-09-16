//written by Isabella Shapland
#include "pq.h"

#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    if (pq == NULL)
        return NULL;
    pq->list = NULL;
    return pq;
}
void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        if ((*q)->list != NULL && (*q)->list->tree != NULL) {
            node_free(&((*q)->list->tree));
        }
        free(*q);
        *q = NULL;
    }
}
bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL || q == NULL) {
        return true;
    }
    return false;
}
bool pq_size_is_1(PriorityQueue *q) {
    if (q->list != NULL && q->list->next == NULL) {
        return true;
    }
    return false;
}
bool pq_less_than(ListElement *e1, ListElement *e2) {
    if ((e1)->tree->weight < (e2)->tree->weight) {
        return true;
    } else if ((e1)->tree->weight == (e2)->tree->weight) {
        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}
void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new = (ListElement *) calloc(1, sizeof(ListElement));
    if (new == NULL) {
        fprintf(stderr, "list element not allocated");
        return;
    }
    new->tree = tree;
    new->next = NULL;
    if (pq_is_empty(q)) {
        q->list = new;
    } else if (pq_less_than(new, q->list)) {
        new->next = q->list;
        q->list = new;
    } else {
        ListElement *e2 = q->list;
        while (e2->next != NULL && !pq_less_than(new, e2->next)) {
            e2 = e2->next;
        }
        new->next = e2->next;
        e2->next = new;
        if (new->next == NULL) {
            e2->next = new;
        }
    }
}
Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return NULL;
    } else {
        ListElement *temp = q->list;
        Node *returnval = q->list->tree;
        q->list = q->list->next;
        free(temp);
        return returnval;
    }
}
void pq_print(PriorityQueue *q) {
    if (q == NULL) {
        return;
    }
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("===========================================\n");
        } else {
            printf("-------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("===========================================\n");
}
