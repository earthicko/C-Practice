#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
};

struct node* create_node(int data);
struct node* insert_node(struct node* current_node, int data);
void destroy_node(struct node* target, struct node* head);
int count_node(struct node* head);
int has_node(struct node* head, struct node* search);

void print_nodes(struct node* head);

int main(int argc, char** argv) {
  struct node* current_node;
  struct node* node0 = create_node(100);
  struct node* node1 = insert_node(node0, 200);
  struct node* node2 = insert_node(node1, 300);

  printf("Initial State=====================\n");
  print_nodes(node0);
  printf("Number of nodes: %d\n", count_node(node0));
  printf("Has node: node0: %d\n", has_node(node0, node0));
  printf("Has node: node1: %d\n", has_node(node0, node1));
  printf("Has node: node2: %d\n", has_node(node0, node2));

  struct node* node_a = insert_node(node1, 250);
  printf("After Insertion=====================\n");
  print_nodes(node0);
  printf("Number of nodes: %d\n", count_node(node0));
  printf("Has node: node0: %d\n", has_node(node0, node0));
  printf("Has node: node1: %d\n", has_node(node0, node1));
  printf("Has node: node2: %d\n", has_node(node0, node2));
  printf("Has node: nodea: %d\n", has_node(node0, node_a));

  destroy_node(node1, node0);
  printf("After Destruction=====================\n");
  print_nodes(node0);
  printf("Number of nodes: %d\n", count_node(node0));
  printf("Has node: node0: %d\n", has_node(node0, node0));
  printf("Has node: node1: %d\n", has_node(node0, node1));
  printf("Has node: node2: %d\n", has_node(node0, node2));
  printf("Has node: nodea: %d\n", has_node(node0, node_a));

  return 0;
}

struct node* create_node(int data) {
  struct node* next_node = (struct node*)malloc(sizeof(struct node));

  next_node->data = data;
  next_node->next = NULL;

  return next_node;
}

struct node* insert_node(struct node* current_node, int data) {
  struct node* next = current_node->next;

  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = data;
  new_node->next = next;

  current_node->next = new_node;

  return new_node;
}

void destroy_node(struct node* target, struct node* head) {
  struct node* test = head;
  if (test == target) {
    free(head);
    return;
  }

  while (test) {
    // break when test->next == NULL
    if (test->next == target) {
      break;
    }
    test = test->next;
  }
  test->next = target->next;
  free(target);
}

void print_nodes(struct node* head) {
  struct node* current_node = head;

  int i = 0;
  while (current_node) {
    printf("node%d: %d\n", i, current_node->data);
    i++;
    current_node = current_node->next;
  }
}

int count_node(struct node* head) {
  struct node* counter = head;
  int num_nodes = 1;
  while (1) {
    if (counter->next == NULL) return num_nodes;
    counter = counter->next;
    num_nodes++;
  }
}

int has_node(struct node* head, struct node* search) {
  struct node* finder = head;
  while (1) {
    if (finder->data == search->data) return 1;
    finder = finder->next;
    if (finder == NULL) break;
  }
  return 0;
}