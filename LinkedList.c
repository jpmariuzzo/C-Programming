//
// Created by jpmar on 30/07/2025.
//
// Linked List
// You will write a function list_add() to append an integer to the end of a linked list. You will also write a function
// called list_find() that will return the list node containing the integer value or NULL if the value is not in the list.

#include <stdio.h>
#include <stdlib.h>

struct lnode {
    int value;
    struct lnode *next;
};

struct list {
    struct lnode *head;
    struct lnode *tail;
};

int main()
{
    void list_add();
    void list_dump();
    struct lnode * list_find();

    struct list mylist;
    struct lnode * mynode;

    mylist.head = NULL; // NULL is a special pointer
    mylist.tail = NULL;

    list_add(&mylist, 10);
    list_add(&mylist, 20);
    list_add(&mylist, 30);
    list_dump(&mylist);

    mynode = list_find(&mylist, 42);  // mynode is an expected pointer
    if ( mynode == NULL ) {
        printf("Did not find 42\n");
    } else {
        printf("Looked for 42, found %d\n", mynode->value);
    }

    mynode = list_find(&mylist, 30);
    if ( mynode == NULL || mynode->value != 30) {
        printf("Did not find 30\n");
    } else {
        printf("Found 30\n");
    }

    list_add(&mylist, 40);
    list_dump(&mylist);

}

void list_dump(lst)
    struct list *lst;
{
    struct lnode *cur;
    printf("\nDump:\n");
    for(cur=lst->head; cur != NULL; cur=cur->next) {
        printf("  %d\n", cur->value);
    }
}

void list_add(lst, value)
    struct list *lst;
int value;
{
    /* Append the value to the end of the linked list. */
    struct lnode *new = (struct lnode *)malloc(sizeof(struct lnode));
    if (lst->tail != NULL) lst->tail->next = new;
    new->value = value;
    new->next = NULL;
    lst->tail = new;

    if (lst->head == NULL) lst->head = new;
}

struct lnode * list_find(lst, value)
    struct list *lst;
int value;
{
    struct lnode *cur;
    for(cur=lst->head; cur != NULL; cur=cur->next) {
        if (cur->value == value) {
            return cur;
        }
        }
    return NULL;
}
