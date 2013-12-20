
do zaimplementowania w sygnalizajci mozna użyć zależnośći: if (t2<t1) t2 = t1; else t2 = t2 + (t2-t1);  
xx czas wjazdu na skrzyzowanie wzgledem czasu globalnego (potrzebne do policzenia czasu oczekiwania na skrzyzowaniu)
xx [opcjonalnie] czas zjazdu / czas oczekiwania
xx [opcjonalnie] wygląd

Skrzyżowanie:
--operuje na kolejkach i wywołuje sygnalizację
--obiekty: 4xfifo, sygnalizacja, sygnaly do QT


Sygnalizacja: (zmiennoczasowa dziedziczy po stałoczasowej)
-- stan
-- czas do konca
--funkcja przejazdu przez skrzyzowanie zwraca wartosci zaleznie od stanu (1 moze jechac kolejny, 0 stop, -1 kolizja)
-- przelicza czas jaki samochod spedzi na skrzyzowaniu po zgaszeniu zielonego i na jego podstawie zwraca kolizję lub nie
-- funkcja przelacz()

funckje:
--generowanie samochodów
-- zapis do pliku 

