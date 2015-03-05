#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define COMPACITY_FACTOR 2

struct stack
{
    int *data;
    int compacity;
    int pos;    
};

struct stack *create_stack(int compacity)
{
    struct stack *s;
    if (!(s = malloc(sizeof(struct stack)))) {
        return NULL;
    }
    if (!(s->data = malloc(sizeof(int) * compacity))) {
        return NULL;
    }

    s->compacity = compacity;
    s->pos = 0;

    return s;
}

struct stack *push(struct stack *s, int value)
{
    if (s->pos >= s->compacity) {
        int *new = realloc(s->data, sizeof(int) * s->compacity * COMPACITY_FACTOR);
        if (!new) {
            return NULL;
        }

        s->compacity *= COMPACITY_FACTOR;
        s->data = new;
    }

    s->data[s->pos++] = value;
    return s;
}

int pop(struct stack *s)
{
    if (!s || !s->pos)
        return -1;

    return s->data[--s->pos];
}

void destroy(struct stack *s)
{
    free(s->data);
    free(s);
}

int main()
{
    struct stack *s;
    if (!(s = create_stack(5))) {
        printf("Create stack failed");
        return 1;
    }

    push(s, 111);
    push(s, 222);
    push(s, 333);

    assert(333 == pop(s));
    assert(222 == pop(s));
    assert(111 == pop(s));

    destroy(s);

    return 0;
}
