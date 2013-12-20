Aktualny stan idei pocz�tkowej:
-- piszemy w C++ w QTCreator -> interfejs graficzny
-- system kolejkowy samochod�w stoj�cych na �wiat�ach
-- algorytm obs�ugi sta�oczasowej �wiate�

Dalsze pomys�y na rozw�j:
-- doda� drog�
-- inteligentna obs�uga skrzy�owania

Parametry klasy auto (minimalizm):
-- typ (zwyk�y, nauka jazdy)
-- pr�dko��, przyspieszenie (maksymalne) - czas przejazdy przez skrzyzowanie od tego zale�y (czas obs�ugi)
-- czas reakcji ! (kolejny samochod nie przejedzie szybciej niz poprzedni!)
do zaimplementowania w sygnalizajci mozna użyć zależnośći: if (t2<t1) t2 = t1; else t2 = t2 + (t2-t1);  
xx czas wjazdu na skrzyzowanie wzgledem czasu globalnego (potrzebne do policzenia czasu oczekiwania na skrzyzowaniu)
xx [opcjonalnie] czas zjazdu / czas oczekiwania
xx [opcjonalnie] wygląd

Skrzyżowanie:
--operuje na kolejkach i ywołuje syganlizację
--obiekty: 4xfifo, sygnalizacja, sygnaly do QT

Ilo�c potrzebnych list kolejkowych:
-- zaczynamy od 4, ale dojdziemy do 8 z lewoskr�tami


Sygnalizacja: (zmiennoczasowa dziedziczy po stałoczasowej)
-- stan
-- czas do konca
--funkcja przejazdu przez skrzyzowanie zwraca wartosci zaleznie od stanu (1 moze jechac kolejny, 0 stop, -1 kolizja)
-- przelicza czas jaki samochod spedzi na skrzyzowaniu po zgaszeniu zielonego i na jego podstawie zwraca kolizję lub nie
-- funkcja przelacz()

funckje:
--generowanie samochodów
-- zapis do pliku 

