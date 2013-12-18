#ifndef SYGNALIZATOR_H
#define SYGNALIZATOR_H

//Sygnalizator swietlny jako maszyna stanow
enum State {red, green};

class Sygnalizator
{
    State state;
    unsigned long greenTime; //czas w milisekundach
    unsigned long redTime;

public:
    Sygnalizator(unsigned long greenT, unsigned long redT);
    Sygnalizator(){};
    virtual ~Sygnalizator();
    State getState();
    void change();
    /* metoda wykonaj stan nie jest potrzebna,
    jesli program nie bedzie dzialac w czasie rzeczywistym */


};

#endif // SYGNALIZATOR_H
