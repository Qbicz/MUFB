-Aktualny stan idei początkowej:
 --- piszemy w C++ w QTCreator -> interfejs graficzny
 --- system kolejkowy samochodów stojących na światłach
 --- algorytm obsługi stałoczasowej świateł
 
 -Dalsze pomysły na rozwój:
 --- dodać drogę
 --- inteligentna obsługa skrzyżowania
 
 -Parametry klasy auto (minimalizm):
 --- typ (zwykły, nauka jazdy)
 --- prędkość, przyspieszenie (maksymalne) - czas przejazdy przez skrzyzowanie od tego zależy (czas obsługi)
 --- czas reakcji ! (kolejny samochod nie przejedzie szybciej niz poprzedni!)
 -xx czas wjazdu na skrzyzowanie wzgledem czasu globalnego (potrzebne do policzenia czasu oczekiwania na skrzyzowaniu)
 -xx [opcjonalnie] czas zjazdu / czas oczekiwania
 -xx [opcjonalnie] wygląd

  do zaimplementowania czasu przejazdu w sygnalizajci mozna użyć zależnośći: if (t2<t1) t2 = t1; else t2 = t2 + (t2-t1);
  gdzie t1 to czas przejazdu samochodu wjezdzajacego wczesniej a t2 samochodu kolejnego.

  
  Skrzyżowanie:
--operuje na kolejkach i ywołuje syganlizację
--obiekty: 4xfifo, sygnalizacja, sygnaly do QT
  
 --Ilość potrzebnych list kolejkowych:
 -- zaczynamy od 4, ale dojdziemy do 8 z lewoskrętami


Sygnalizacja: (zmiennoczasowa dziedziczy po stałoczasowej)
-- stan
-- czas do konca
--funkcja przejazdu przez skrzyzowanie zwraca wartosci zaleznie od stanu (1 moze jechac kolejny, 0 stop, -1 kolizja)
-- przelicza czas jaki samochod spedzi na skrzyzowaniu po zgaszeniu zielonego i na jego podstawie zwraca kolizję lub nie
-- funkcja przelacz()

funckje:
--generowanie samochodów
-- zapis do pliku 

Czas globalny:
-- potrzebny do wyliczania czaus oczekiwania samochodów, 
-- czas wjazdu samochodów najprawdopodobniej synchroniczny z okresem sygnalizacji
