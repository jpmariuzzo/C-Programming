//
// Created by jpmar on 04/08/2025.
//

// Python List Class

// You will a set of supporting functions using the following structures to implement a subset of the Python list class
// in C. Some code and method signatures have been provided for you as well as a main() program and some support routines
// from the lecture slides. There is a good deal of discussion of this application in the lecture materials associated
// with this assignment.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lnode {
    char *text;
    struct lnode *next;
};

struct pylist {
    struct lnode *head;
    struct lnode *tail;
    int count;
};

/* Constructor - lst = list() */
struct pylist * pylist_new() {
    struct pylist *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Destructor - del(lst) */
void pylist_del(struct pylist* self) {
    struct lnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->text);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    struct pylist * lst = pylist_new();
    pylist_append(lst, "Hello world");
    pylist_print(lst);
    pylist_append(lst, "Catch phrase");
    pylist_print(lst);
    pylist_append(lst, "Brian");
    pylist_print(lst);
    printf("Length = %d\n", pylist_len(lst));
    printf("Brian? %d\n", pylist_index(lst, "Brian"));
    printf("Bob? %d\n", pylist_index(lst, "Bob"));
    pylist_del(lst);
}

/* print(lst) */
void pylist_print(struct pylist* self)
{
    /* About 10 lines of code
       The output should match Python's
       list output

       ['Hello world', 'Catch phrase']

    Use printf cleverly, *not* string
    concatenation since this is C, not Python.
    */

    struct lnode *cur, *next;
    cur = self->head;
    printf("[");
    while(cur) {
        printf("'%s'", cur->text);
        if (cur->next != NULL) {
            printf(", ");
        }
        next = cur->next;
        cur = next;
    }
    printf("]\n");
}

/* len(lst) */
int pylist_len(const struct pylist* self)
{
    /* One line of code */
    return self->count;
}

/* lst.append("Hello world") */
void pylist_append(struct pylist* self, char *str) {
    /* Review: Chapter 6 lectures and assignments */
    char *save = (char *) malloc(strlen(str) + 1);
    struct lnode *new_node = (struct lnode *) malloc(sizeof(*new_node));
    strcpy(save, str);

    if ((self->tail)!= NULL) {
        self->tail->next = new_node;
    }
    new_node->text = save;
    new_node->next = NULL;
    self->tail = new_node;

    if (self->head == NULL) {
        self->head = new_node;
    }
    self->count++;
}


/* lst.index("Hello world") - if not found -1 */
int pylist_index(struct pylist* self, char *str)
{
    /* Seven or so lines of code */
    int i = 0;
    for (struct lnode *cur = self->head; cur != NULL; cur = cur->next, i++) {
        if (strcmp(cur->text, str) == 0) {
            return i;
        }
    }
    return -1;
}