//
// Created by jpmar on 06/08/2025.
//
// Iteration

// This assignment will add an iterator to your Map class. There is a good deal of discussion of iterators in the
// lecture materials associated with this assignment.

// A good starting point for this assignment is the code used for the previous assignment. This assignment will add a
// new feature to the previous assignment.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MapEntry {
    char *key;  /* public */
    int value;  /* public */
    struct MapEntry *__prev;
    struct MapEntry *__next;
};

struct MapIter {
   struct MapEntry *__current;

   struct MapEntry* (*next)(struct MapIter* self);
   void (*del)(struct MapIter* self);
};

struct Map {
   /* Attributes */
   struct MapEntry *__head;
   struct MapEntry *__tail;
   int __count;

   /* Methods */
   void (*put)(struct Map* self, char *key, int value);
   int (*get)(struct Map* self, char *key, int def);
   int (*size)(struct Map* self);
   void (*dump)(struct Map* self);
   struct MapIter* (*iter)(struct Map* self);
   void (*del)(struct Map* self);
};

void __Map_del(struct Map* self) {
    struct MapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        /* value is just part of the struct */
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void __MapIter_del(struct MapIter* self) {
    free((void *)self);
}

void __Map_dump(struct Map* self)
{
    struct MapEntry *cur;
    printf("Object Map count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
         printf("  %s=%d\n", cur->key, cur->value);
    }
}

struct MapEntry* __Map_find(struct Map* self, char *key)
{
    struct MapEntry *cur;
    if ( self == NULL || key == NULL ) return NULL;
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
        if(strcmp(key, cur->key) == 0 ) return cur;
    }
    return NULL;
}

int __Map_get(struct Map* self, char *key, int def)
{
    struct MapEntry *retval = __Map_find(self, key);
    if ( retval == NULL ) return def;
    return retval->value;
}

int __Map_size(struct Map* self)
{
    return self->__count;
}

/* Student code will be inserted here */
void __Map_put(struct Map* self, char *key, int value) {
    struct MapEntry *old, *new;
    char *new_key;
    if ( key == NULL ) return;

    old = __Map_find(self, key); //Update the value if it's already present
    if ( old != NULL ) {
        old->value = value;
        return;
    }

    new = malloc(sizeof(*new)); //Inserting the new key-value
    new_key = malloc(strlen(key) + 1);
    strcpy(new_key, key);

    //* TODO: Link new to the tail of the list */
    if (self->__tail != NULL) {
        self->__tail->__next = new;
    }
    new->key = new_key;
    new->value = value;
    new->__next = NULL;
    self->__tail = new;

    if (self->__head == NULL) {
        self->__head = new;
    }

    self->__count++;
}

struct MapEntry* __MapIter_next(struct MapIter* self)
{
    /* TODO: Advance the iterator */
    struct MapEntry *retval = self->__current;
    if (retval == NULL) {
        return NULL;
    }
    self->__current = self->__current->__next;
    return retval;

}

struct MapIter* __Map_iter(struct Map* self)
{
    struct MapIter *iter = malloc(sizeof(*iter));

    /* TODO: fill in the new iterator */
    iter->__current = self->__head;
    iter->next = &__MapIter_next;
    iter->del = &__MapIter_del;
    return iter;
}

struct Map * Map_new() {
    struct Map *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__tail = NULL;
    p->__count = 0;

    p->put = &__Map_put;
    p->get = &__Map_get;
    p->size = &__Map_size;
    p->dump = &__Map_dump;
    p->del = &__Map_del;
    p->iter = &__Map_iter;
    return p;
}


int main(void)
{
    struct Map * map = Map_new();
    struct MapEntry *cur;
    struct MapIter *iter;

    /* Make sure we see all output up to an error */
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Map test\n");
    map->put(map, "z", 8);
    map->put(map, "z", 1);
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map);

    printf("size=%d\n", map->size(map));

    printf("z=%d\n", map->get(map, "z", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    printf("\nIterate\n");
    iter = map->iter(map);
    while(1) {
        cur = iter->next(iter);
        if ( cur == NULL ) break;
	printf("%s=%d\n", cur->key, cur->value);
    }
    iter->del(iter);

    map->del(map);
}