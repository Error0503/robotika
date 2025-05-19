#ifndef ll_included
#define ll_included

#include <stddef.h>
#include <stdlib.h>

typedef struct Node
{
    int x;
    int y;
    Node *next;
} Node;

constexpr size_t NODE_SIZE = sizeof(Node);

Node *LinkedList(int len);

Node* addHead(Node* head, int x, int y);
void removeLast(Node* head);
bool contains(Node *head, int x, int y);
void printLinkedList(Node* head);

#endif