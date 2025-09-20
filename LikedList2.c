//
// Created by jpmar on 30/07/2025.
//
// Linked List
// You will extend the previous assignment with list_add() and list_find() and add a function called list_delete() that
// will find and remove the node containing the integer value if it is in the list.

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
    struct lnode *list_find();
    void list_remove();

    struct list mylist;
    struct lnode * mynode;

    mylist.head = NULL;
    mylist.tail = NULL;

    list_add(&mylist, 10);
    list_add(&mylist, 20);
    list_add(&mylist, 30);
    list_dump(&mylist);

    list_remove(&mylist, 42);

    list_remove(&mylist, 10);
    list_dump(&mylist);

    list_remove(&mylist, 30);
    list_dump(&mylist);

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

    printf("Adicionado %d\n", value);
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

void list_remove(lst, value)
    struct list *lst;
int value;
{
    /* Remove the value from the linked list. */
    struct lnode *cur;
    struct lnode *prev;
    prev = NULL;
    cur = lst->head;


    while(cur != NULL){
        if (cur->value == value) {
            if (prev == NULL) {
                lst->head = cur->next; //Removendo o primeiro elemento da lista
            }
            else {
                prev->next = cur->next; //Removendo o elemento do meio da lista
            }
            if (cur == lst->tail) {
                lst->tail = prev; // Removendo o elemento no fim da lista
            }
        }
        prev = cur;
        cur = cur->next;



        printf("\nRemovido %d\n", value);
    }
}

