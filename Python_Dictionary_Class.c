//
// Created by jpmar on 05/08/2025.
//

// Python Dictionary Class

// You will a set of supporting functions using the following structure to implement a subset of the Python dict class
// in C. Some code and method signatures have been provided for you as well as a main() program and some support routines
// from the lecture slides. There is a good deal of discussion of this application in the lecture materials associated
// with this assignment.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode {
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict {
    struct dnode *head;
    struct dnode *tail;
    int count;
};

/* Constructor - dct = dict() */
struct pydict * pydict_new() {
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Destructor - del(dct) */
void pydict_del(struct pydict* self) {
    struct dnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}



/* print(dct) */
/* {'z': 'W', 'y': 'B', 'c': 'C', 'a': 'D'} */
void pydict_print(struct pydict* self)
{
    struct dnode *cur, *next;
    cur = self->head;
    printf("{");
    while(cur) {
        printf("'%s': '%s'", cur->key, cur->value);
        if (cur->next != NULL) {
            printf(", ");
        }
        next = cur->next;
        cur = next;
    }
    printf("}\n");
}

int pydict_len(const struct pydict* self)
{
    return self->count;
}

/* find a node - used in get and put */
struct dnode* pydict_find(struct pydict* self, char *key)
{
    struct dnode *cur;
    for (cur = self->head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->key, key) == 0) {
            return cur;
        }
    }
    return NULL;
}

/* x.get(key) - Returns NULL if not found */
char* pydict_get(struct pydict* self, char *key){
    struct dnode *entry;
    char* not_found ="(null)";
    entry = pydict_find(self, key);
    if (entry == NULL){
        return not_found;
    }
    return entry->value;
}

/* x[key] = value; Insert or replace the value associated with a key */
void pydict_put(struct pydict* self, char *key, char *value) {
    char *save_key= (char *) malloc(strlen(key) + 1);
    strcpy(save_key, key);
    char *save_value= (char *) malloc(strlen(value) + 1);
    strcpy(save_value, value);

    struct dnode *existing = pydict_find(self, save_key);

    if (existing != NULL) {
        free(existing->value);
        existing->value = save_value;
        return;
    }

    struct dnode *new_node = (struct dnode *) malloc(sizeof(*new_node));

    if ((self->tail)!= NULL) {
        self->tail->next = new_node;
    }
    new_node->key = save_key;
    new_node->value = save_value;
    new_node->next = NULL;
    self->tail = new_node;

    if (self->head == NULL) {
        self->head = new_node;
    }
    self->count++;
}

int main(void)
{
    struct dnode * cur;
    struct pydict * dct = pydict_new();

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    pydict_put(dct, "z", "Catch phrase");
    pydict_print(dct);
    pydict_put(dct, "z", "W");
    pydict_print(dct);
    pydict_put(dct, "y", "B");
    pydict_put(dct, "c", "C");
    pydict_put(dct, "a", "D");
    pydict_print(dct);
    printf("Length =%d\n",pydict_len(dct));

    printf("z=%s\n", pydict_get(dct, "z"));
    printf("x=%s\n", pydict_get(dct, "x"));

    printf("\nDump\n");
    for(cur = dct->head; cur != NULL ; cur = cur->next ) {
        printf("%s=%s\n", cur->key, cur->value);
    }

    pydict_del(dct);
}











