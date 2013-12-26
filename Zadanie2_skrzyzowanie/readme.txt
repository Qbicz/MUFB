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

Sygnalizacja inteligentna:
Proponuję dodać zmienna czas_opóznienia do kazdego typu skrzyzowania. 
Chodzi mi o to, że zmiana świateł w rzeczywistości zajmuje czas. Stąd, żeby inteligentne nie puszczały po jednym auteczku dałbym ją jako 2 sekundy 
(po prostu GetTime zwracałaby czas: greenTime - czas_opóźnienia)

Jednocześnie rozwiąże to problem skrzyżowania bez świateł:
-- bez świateł:
--- wybiera, które auto ma najktótszy czas_przejazdu i puszcza to auto jako pierwsze - (w praktyce też tak jest, że najszybsze auto pierwsze przejedzie)
--- puszcza pozostałe 3 auta po kolei (najprościej jak się da?) - inne propozycje?
--- czeka czas_opóźnienia (kierowcy decydują kto teraz - reguła lewej ręki i takei tam) - czas ten jest krótszy od światłowego!
--- otwiera nową kolejkę 

Bez świateł to zabawa z czasem oczekiwania (stałoczasówka daje go w granicach 400-500 (maximum))


  
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
