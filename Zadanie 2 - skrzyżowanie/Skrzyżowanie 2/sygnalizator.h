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
    Sygnalizator(unsigned long greenT, unsigned long redT); //wirtualny konstruktor, ponieważ mamy klasy pochodne
    Sygnalizator(){};
    ~Sygnalizator();
    State getState();
    void change();
    void wykonaj_stan();


};

#endif // SYGNALIZATOR_H
