#ifndef SYGNALIZATOR_H
#define SYGNALIZATOR_H

//Sygnalizator swietlny jako maszyna stanow
enum State {red, green};

/*!
 * \brief The Kierunek enum
 *  określa, w którą stronę aktualnie mogą przejechać samochody
 *  pion - zielone dla góry i dołu
 *  poziom - zielone dla lewo-prawo
 */
enum Kierunek {pion, poziom};

/*!
* \brief The Sygnalizator class
*   Klasa opisuje sygnalizatory świetlne i posiada czasy światła zielonego i czerwonego -
*  czasy przepusczania na pionie i poziomie
*/

class Sygnalizator
{
    State state;
    Kierunek  kierunek;
    unsigned long greenTime; //czas w milisekundach
    unsigned long redTime;

public:
    Sygnalizator(unsigned long greenT, unsigned long redT);
    Sygnalizator();
    virtual ~Sygnalizator();
    State getState();
    Kierunek getKierunek();
    int getTime();
    void changeState();
    void changeKierunek();
    void setTime(int time);
    /* metoda wykonaj stan nie jest potrzebna,
    jesli program nie bedzie dzialac w czasie rzeczywistym */


};

#endif // SYGNALIZATOR_H
