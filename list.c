#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* L = (List*)malloc(sizeof(List));
    L->head = NULL;
    L->tail = NULL; 
    return L;
}

void * firstList(List * list) {
    if (list->head != NULL) {
        list->current = list->head;
        return list->current->data;
    }   
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL) {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL) {
        list->current = list->current->prev;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
    list->current = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * new = createNode(data);
    if (list->current == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->current->next;
        new->prev = list->current;
        if (list->current->next != NULL) {
            list->current->next->prev = new;
        } else {
            list->tail = new;
        }
        list->current->next = new;
    }
    list->current = new;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current != NULL) {
        Node * temp = list->current;
        void * data = temp->data;
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            list->head = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        } else {
            list->tail = temp->prev;
        }
        free(temp);
        return data;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}