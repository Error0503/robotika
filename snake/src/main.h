#ifndef main_included
#define main_included

#include <Arduino.h>
#include <LedControl.h>
#include "LinkedList.h"
#include "joystick.h"
#include "animation.h"

enum Directions
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

int playerX = 4;
int playerY = 5;
int fruitX = -1;
int fruitY = -1;
int tailLength = 3;

Node *tail = LinkedList(tailLength);

/*
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 */
LedControl lc = LedControl(12, 11, 10, 1);

Directions input();
void gameLogic(Directions direction);
void spawnFruit();
void render();

#endif