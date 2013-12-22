#include "auto.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


/*!  konstruktor z generatorem
 *  wartością maksymalną (generator inicjalizowany wcześniej poprzez SetRandomSeed)
 **/

Auto::Auto(int max){
    czas_przejazdu = rand()%max;
}

int Auto::GetCzasPrzejazdu(){
    return czas_przejazdu;
}
