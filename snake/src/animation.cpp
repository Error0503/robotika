#include "animation.h"

void playAnimation(LedControl lc, size_t frames, unsigned long wait, const byte arr[][8])
{
    for (size_t i = 0; i < frames; i++)
    {
        lc.clearDisplay(0);
        for (size_t j = 0; j < 8; j++)
        {
            lc.setRow(0, j, arr[i][j]);
        }
        delay(wait);
    }
}