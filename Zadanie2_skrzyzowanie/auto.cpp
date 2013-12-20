#include "auto.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


Auto::Auto()
{
    czas_przejazdu = 0;
    srand (time(NULL));
}

Auto::Auto(int max){

    czas_przejazdu = rand()%max;
}
