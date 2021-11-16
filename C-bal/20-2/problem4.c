#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* prev;
    struct node* next;
};

struct node* create_node(int data);
struct node* insert_node(struct node* head, struct node* target, int data,
                         int reversed);
void destroy_node(struct node* target, struct node* head);
int count_nodes(struct node* head);
int has_node(struct node* head, struct node* search);
void print_node_from(struct node* head, int reversed);

int main(int argc, char** argv) {
    struct node* head = create_node(100);
    struct node* nodes[100];

    printf("Inserted 200 after head\n");
    nodes[0] = insert_node(head, head, 200, 0);
    print_node_from(head, 0);

    printf("Inserted 0 before head\n");
    nodes[1] = insert_node(head, head, 0, 1);
    print_node_from(nodes[1], 0);

    printf("Inserted 300~600 after 200\n");
    nodes[2] = insert_node(head, nodes[0], 300, 0);
    nodes[3] = insert_node(head, nodes[2], 400, 0);
    nodes[4] = insert_node(head, nodes[3], 500, 0);
    nodes[5] = insert_node(head, nodes[4], 600, 0);
    print_node_from(nodes[1], 0);

    printf("Deleted 400\n");
    destroy_node(nodes[3], nodes[1]);
    print_node_from(nodes[1], 0);

    printf("Deleted 200\n");
    destroy_node(nodes[0], nodes[1]);
    print_node_from(nodes[1], 0);

    return 0;
}

struct node* create_node(int data) {
    struct node* output = (struct node*)malloc(sizeof(struct node));
    output->data = data;
    output->prev = output->next = NULL;
    return output;
}

struct node* insert_node(struct node* head, struct node* target, int data,
                         int reversed) {
    // reversed==0 -> after, reversed==1 -> before
    struct node* finder = head;
    struct node* output = (struct node*)malloc(sizeof(struct node));
    output->data = data;
    while (1) {
        if (finder == target) {
            if (reversed) {
                struct node* before = finder->prev;
                finder->prev = output;
                output->next = finder;
                output->prev = before;
                if (before != NULL) before->next = before;
            } else {
                struct node* after = finder->next;
                finder->next = output;
                output->prev = finder;
                output->next = after;
                if (after != NULL) after->prev = output;
            }
            break;
        }
        finder = finder->next;
    }
    return output;
}

void print_node_from(struct node* head, int reversed) {
    while (1) {
        printf("node%p: %d\n", head, head->data);
        if (reversed)
            head = head->prev;
        else
            head = head->next;
        if (head == NULL) return;
    }
}

void destroy_node(struct node* target, struct node* head) {
    while (1) {
        if (target == head) {
            if (target->prev != NULL)
                target->prev->next = target->next;
            else
                target->next->prev = NULL;
            if (target->next != NULL)
                target->next->prev = target->prev;
            else
                target->prev->next = NULL;
            free(target);
            return;
        }
        head = head->next;
    }
}

int count_nodes(struct node* head) {
    int i = 1;
    while (head != NULL) {
        i++;
        head = head->next;
    }
    return i;
}

int has_node(struct node* head, struct node* search) {
    while (head != NULL) {
        if (head->data == search->data) return 1;
        head = head->next;
    }
    return 0;
}