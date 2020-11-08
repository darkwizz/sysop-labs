#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct linked_list_node {
    double value;
    struct linked_list_node* next;
} list_node_t;


list_node_t* add_list_item(list_node_t* tail, double value) {
    list_node_t* new_item = NULL;
    new_item = (list_node_t*) malloc(sizeof(list_node_t));
    if (new_item == NULL) {
        return NULL;
    }

    new_item->value = value;
    tail->next = new_item;

    return new_item;
}

int main() {
    double value = 4.5232432415368;
    list_node_t* head = NULL;
    head = (list_node_t*) malloc(sizeof(list_node_t));
    head->value = value;
    
    list_node_t* tail;
    tail = head;

    int sleep_seconds;
    sleep_seconds = 2;
    while (1) {
        for (int i = 0; i < 5000; i++) {
            tail = add_list_item(tail, value);
        }
        sleep(sleep_seconds);
    }

    return 0;
}