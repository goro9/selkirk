#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "ngx-queue.h"

#define ngx_queue_move(h, x)                                                                    \
    (h)->next = (x)->next;                                                                      \
    (h)->prev = (x)->prev;                                                                      \
    (h)->next->prev = h;                                                                        \
    (h)->prev->next = h

typedef struct {
    uint8_t sample8;
    ngx_queue_t queue;
} sample_queue_a_t;

typedef struct {
    uint16_t sample16;
    uint8_t sample8;
    ngx_queue_t queue;
} sample_queue_b_t;

static ngx_queue_t s_que;

void create_queue(ngx_queue_t *que) {
    ngx_queue_init(que);

    sample_queue_a_t *sample_a1 = malloc(sizeof(sample_queue_a_t));
    ngx_queue_init(&sample_a1->queue);
    sample_a1->sample8 = 1;
    ngx_queue_insert_tail(que, &sample_a1->queue);

    sample_queue_a_t *sample_a2 = malloc(sizeof(sample_queue_a_t));
    ngx_queue_init(&sample_a2->queue);
    sample_a2->sample8 = 2;
    ngx_queue_insert_tail(que, &sample_a2->queue);   
}

void release_queue(ngx_queue_t *que) {
    while (!ngx_queue_empty(que)) {
        ngx_queue_t *q = ngx_queue_head(que);
        sample_queue_a_t *a = ngx_queue_data(q, sample_queue_a_t, queue);
        ngx_queue_remove(q);
        free(a);
    }
}

int main(int argc, char* argv[]) {
    ngx_queue_init(&s_que);

    ngx_queue_t que;
    create_queue(&que);

    // ngx_queue_t *last = NULL;
    // ngx_queue_t *q;
    // ngx_queue_foreach(q, &que)
    // {
    //     if(q->next == &que) {
    //         last = q;
    //     }
    // }
    // s_que = que;
    // s_que.next->prev = &s_que;
    // last->next = &s_que;

    // ngx_queue_move(&s_que, &que);
    ngx_queue_insert_tail(&s_que, &que);

    ngx_queue_t *q;
    ngx_queue_foreach(q, &s_que)
    {
        sample_queue_a_t *a = ngx_queue_data(q, sample_queue_a_t, queue);
        printf("%d\n", a->sample8);
    }

    release_queue(&s_que);

    return 0;
}
