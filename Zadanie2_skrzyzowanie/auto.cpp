#include "auto.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


/*!  konstruktor z generatorem
 *  wartością maksymalną (generator inicjalizowany wcześniej poprzez SetRandomSeed)
 **/

Auto::Auto(int max, int min){
    czas_przejazdu = rand() % (max - min + 1) + min;
}

int Auto::GetCzasPrzejazdu(){
    return czas_przejazdu;
}

/*!
 * \brief Auto::Reset
 *      Resetuje czas przejazdu na 0.
 */
void Auto::Reset(){
    czas_przejazdu = 0;
}
