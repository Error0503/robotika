#include "main.h"

void setup()
{
  randomSeed(analogRead(A0));

  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  int i = 1;
  for (Node *n = tail; n->next != NULL; n = n->next)
  {
    n->x = playerX;
    n->y = playerY - i;
    i++;
  }

  // playAnimation(lc, 15, 100, testAnimation);
}

void loop()
{
  if (isRunning)
  {
    gameLogic(input());
    spawnFruit();
    render();
    delay(200);
  }
  else
  {
    lc.clearDisplay(0);
  }
}

Directions input()
{
  int axisX = readAxis(A0);
  int axisY = readAxis(A1);

  if (axisX < 0)
  {
    lastDirection = LEFT;
    return LEFT;
  }
  if (axisX > 0)
  {
    lastDirection = RIGHT;
    return RIGHT;
  }
  if (axisY < 0)
  {
    lastDirection = DOWN;
    return DOWN;
  }
  if (axisY > 0)
  {
    lastDirection = UP;
    return UP;
  }
  return lastDirection;
}

void gameLogic(Directions direction)
{
  tail = addHead(tail, playerX, playerY);
  if (playerX == fruitX && playerY == fruitY)
  {
    fruitX = -1;
    fruitY = -1;
    tailLength++;
  }
  else
  {
    removeLast(tail);
  }

  switch (direction)
  {
  case LEFT:
    playerX--;
    break;
  case RIGHT:
    playerX++;
    break;
  case DOWN:
    playerY--;
    break;
  case UP:
    playerY++;
    break;
  }

  playerX = playerX % 8;
  playerY = playerY % 8;

  if (playerX == -1)
    playerX = 7;
  if (playerY == -1)
    playerY = 7;

  if (contains(tail, playerX, playerY))
  {
    isRunning = false;
  }
}

void spawnFruit()
{
  if (fruitX == -1 && fruitY == -1)
  {
    fruitX = random() % 8;
    fruitY = random() % 8;
  }
}

void render()
{
  lc.clearDisplay(0);
  lc.setLed(0, playerX, playerY, true);
  lc.setLed(0, fruitX, fruitY, true);

  for (Node *n = tail; n->next != NULL; n = n->next)
  {
    lc.setLed(0, n->x, n->y, true);
  }
}
