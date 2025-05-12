#include "LinkedList.h"

#include <Arduino.h>

Node *LinkedList(int len)
{
    Node *head = (Node *)malloc(NODE_SIZE);
    head->x = 0;
    head->y = 0;

    Node *prev = head;
    for (int i = 1; i <= len; i++)
    {
        Node *newNode = (Node *)malloc(NODE_SIZE);
        newNode->x = 0;
        newNode->y = 0;

        prev->next = newNode;

        if (i == len)
        {
            newNode->next = NULL;
        }

        prev = newNode;
    }

    return head;
}

Node *addHead(Node *head, int x, int y)
{
    Node *newHead = (Node *)malloc(NODE_SIZE);
    newHead->next = head->next;
    newHead->x = x;
    newHead->y = y;
    return newHead;
}

void removeLast(Node *head)
{
    Node *prev = head;
    for (Node *current = head->next; true; current = current->next)
    {
        if (current->next == NULL)
        {
            prev->next = NULL;
            free(current);
            return;
        }
        prev = current;
    }
}

bool contains(Node *head, int x, int y)
{
    for (Node *current = head; current->next != NULL; current = current->next)
    {
        if (current->x == x && current->y == y)
            return true;
    }
    return false;
}

void printLinkedList(Node *head)
{
    for (Node *n = head; n->next != NULL; n = n->next)
    {
        Serial.print("x:");
        Serial.print(n->x);
        Serial.print(", y:");
        Serial.println(n->y);
    }
    Serial.println();
}