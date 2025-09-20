//
// Created by jpmar on 12/08/2025.
//
// LinkedTreeMap

// There is a good deal of discussion of this assignment in the lecture materials associated with this assignment.

/* You have to build everything except the main program here
 * You should not need to write any new code - just gather your
 * working TreeMap code and the supplied code together from the previous
 * assignment and combine them together.
 */
// Expected output from your program: the 7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #include "student.c"

/* TREE NODE */
struct TreeMapEntry {
    char *key;
    int value;
    struct TreeMapEntry *__next; // Next node, similar structure
    struct TreeMapEntry *__left; // Left node, similar structure
    struct TreeMapEntry *__right; //  Right node, similar structure
};

/* TREE STRUCT */
struct TreeMap {
    int debug;

    struct TreeMapEntry *__head;
    struct TreeMapEntry *__root;

    /* METHODS */
    void (*put)(struct TreeMap *self, char *key, int value);
    struct TreeMapIter* (*iter)(struct TreeMap *self);
    int (*get)(struct TreeMap *self, char *key, int def);
    void (*del)(struct TreeMap *self);
};

/* ITERATOR */
struct TreeMapIter {
    struct TreeMapEntry *__current;

    /* METHODS */
    struct TreeMapEntry* (*next)(struct TreeMapIter* self);
    void (*del)(struct TreeMapIter* self);
};

/* METHODS */
void __TreeMap_put(struct TreeMap *self, char *key, int value) {
    struct TreeMapEntry *cur, *left, *right, *new;
    int cmp;
    char *new_key;

    cur = self->__root;
    while (cur != NULL) {
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            cur->value = value;
            return;
        }
        if (cmp < 0) {
            right = cur;
            cur = cur->__left;
        }
        else {
            left = cur;
            cur = cur->__right;
        }
    }

    new = malloc(sizeof(*new));
    new_key = malloc(strlen(key) + 1);
    strcpy(new_key, key);

    new->key = new_key;
    new->value = value;
    new->__left = new->__right = new->__next = NULL;


    if ( self->__head == NULL ) {
        self->__head = new;
        self->__root = new;
        return;
    }

}

/* METHODS */
int __TreeMap_get(struct TreeMap* self, char *key, int def)
{
    int cmp;
    struct TreeMapEntry *cur;

    if ( self == NULL || key == NULL || self->__root == NULL ) return def;

    cur = self->__root;

    /* TODO: scan down the tree and if the key is found, return the value.
     * If the key is not found, return the default value (def).
     */
    while (cur != NULL) {
        cmp = strcmp(key, cur->key);
        if ( cmp == 0 ) {
            return cur->value;
        }
        else if ( cmp < 0 ) {
            cur = cur->__left;
        }
        else {
            cur = cur->__right;
        }
    }

    return def;
}

/* METHODS */
struct TreeMapEntry* __TreeMapIter_next(struct TreeMapIter* self)
{
    /* Advance the iterator.  Recall that when we first
     * create the iterator __current points to the first item
     * so we must return an item and then advance the iterator.
     */
    struct TreeMapEntry *retval = self->__current;
    if (retval == NULL) {
        return NULL;
    }
    self->__current = self->__current->__next;
    return retval;
}

/* DESTRUCTOR DEL for TreeMap */
void __TreeMap_del(struct TreeMap* self) {
    struct TreeMapEntry *cur, *next;
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

/* DESTRUCTOR DEL for TreeMapIter */
void __TreeMapIter_del(struct TreeMapIter* self) {
    free((void *)self);
}

/* ITER CONSTRUCTOR */
struct TreeMapIter* __TreeMap_iter(struct TreeMap* self)
{
    struct TreeMapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head;
    iter->next = &__TreeMapIter_next;
    iter->del = &__TreeMapIter_del;
    return iter;
}

/* CONSTRUCTOR */
// Initialize the struct, defining initial values, mapping the functions address with "&"
struct TreeMap * TreeMap_new() {
    struct TreeMap *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__root = NULL;
    p->debug = 0;

    p->put = &__TreeMap_put;
    p->get = &__TreeMap_get;
    p->iter = &__TreeMap_iter;
    p->del = &__TreeMap_del;
    return p;
}


/**
 * The main program to read, parse, and count words
 */
int main(void)
{
    struct TreeMap * map = TreeMap_new();
    struct TreeMapEntry *cur;
    struct TreeMapIter *iter;
    char word[100];  /* Yes, this is dangerous */
    int i,j;
    int count, maxvalue;
    char *maxkey;

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    /* Turn off debug */
    map->debug = 0;

    /* Loop over each word in the file */
    while (scanf("%s", word) != EOF) {
        for (i=0, j=0; word[i] != '\0'; i++) {
            if ( ! isalpha(word[i]) ) continue;
            word[j++] = tolower(word[i]);
        }
        word[j] = '\0';
        count = map->get(map, word, 0);
        map->put(map, word, count+1);
    }

    maxkey = NULL;
    maxvalue = -1;
    iter = map->iter(map);
    while(1) {
        cur = iter->next(iter);
        if ( cur == NULL ) break;
        if ( maxkey == NULL || cur->value > maxvalue ) {
            maxkey = cur->key;
            maxvalue = cur->value;
        }
    }
    iter->del(iter);
    printf("\n%s %d\n", maxkey, maxvalue);

    map->del(map);
}