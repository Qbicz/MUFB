#include "auto.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


/*!  konstruktor z generatorem
 *  wartością maksymalną (generator inicjalizowany wcześniej poprzez SetRandomSeed)
 **/

Auto::Auto(int max, int min, int CzasOczekiwania){
    if(max!=0){
        czas_przejazdu = rand() % (max - min + 1) + min;
    }
    else
        czas_przejazdu = 0; //auta błyskawiczne

    czas_oczekiwania = CzasOczekiwania;
}

int Auto::GetCzasPrzejazdu(){
    return czas_przejazdu;
}

int Auto::GetCzasOczekiwania(){
    return czas_oczekiwania;
}

void Auto::SetCzasOczekiwania(int a){
    czas_oczekiwania = a;
}

Auto::~Auto(){
    czas_przejazdu = 0;
    czas_oczekiwania = 0;
}

/*!
 * \brief Auto::Reset
 *      Resetuje czas przejazdu na 0.
 */
void Auto::Reset(){
    czas_przejazdu = 0;
    czas_oczekiwania = 0;
}
