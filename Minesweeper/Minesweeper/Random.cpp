#include "Random.h"
#include <time.h>
#include <stdlib.h>

int Random::random(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}
