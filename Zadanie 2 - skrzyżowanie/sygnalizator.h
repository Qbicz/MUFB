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
    Sygnalizator(unsigned long greenT,
                 unsigned long redT);
    ~Sygnalizator();
    getState();
    change();
    wykonaj_stan();


};

#endif // SYGNALIZATOR_H
