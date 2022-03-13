# sw
zadanie1.c
Program przełączający cyklicznie 9 podprogramów (następny program po 9 to 1, a poprzedni względem 1 to 9)
Przycisk RB3 – następny program
Przycisk RB4 – poprzedni program
Podprogramy:
1. 8 bitowy licznik binarny zliczający w górę (0…255)
2. 8 bitowy licznik binarny zliczający w dół (255…0)
3. 8 bitowy licznik w kodzie Graya zliczający w górę (repr. 0…255)
4. 8 bitowy licznik w kodzie Graya zliczający w dół (repr. 255…0)
5. 2x4 bitowy licznik w kodzie BCD zliczający w górę (0…99)
6. 2x4 bitowy licznik w kodzie BCD zliczający w dół (99…0)
7. 3 bitowy wężyk poruszający się lewo-prawo
8. Kolejka
9. 6 bitowy generator liczb pseudolosowych oparty o konfigurację 1110011

zadanie2.c
Program przełączający cyklicznie 2 podprogramy z zadania 1 (różne co do zasady działania)*
Przycisk RB3 – następny program
Przycisk RB4 – poprzedni program
Częstotliwość zmiany stanów w podprogramach ma być sterowana przy pomocy potencjometru P2 – 5 różnych prędkości.

zadanie3.c
Alarm!
Jako źródło danych należy wziąć potencjometr P1, nastawę – wartość po przekroczeniu której alarm załącza się – ustawić na połowę zakresu potencjometru.
Po przekroczeniu wartości nastawy – przez pierwsze 5 sekund mruga jedna dioda, a potem zapalone są wszystkie.
Jeśli alarm jest załączony (mruganie, zapalone wszystkie diody) – to po ustawieniu potencjometru poniżej nastawy alarmowej – alarm należy wyłączyć (przerwać mruganie, zgasić diody)
Wyłączenie alarmu – przycisk RB3

zadanie4.c
Kontroler kuchenki mikrofalowej.
RB5 – wybór mocy 800W, 600W, 350W, 200W
RB4 – dodanie czasu 1min
RB3 – dodanie czasu 10s
RB2 – Start/Stop
RB1 – Reset

zadanie5.c
Zegar szachowy dla dwóch graczy
odmierzający czas SD (Sudden Death – całkowity czas na wykonanie ruchów w partii). Naciśnięcie przycisku pierwszego gracza powoduje odmierzanie czasu drugiego gracza, a naciśnięcie przycisku drugiego gracza – odmierzanie czasu pierwszego. Gra toczy się do poddania partii, ustalenia remisu, Mata – to są jednak zdarzenia, których nie odnotowujemy na zegarze. Zegar ma wyświetlić czas każdego z graczy i w razie gdy któryś z graczy nie wykona ruchu w pozostałym mu czasie wyświetlić komunikat, że gracz przegrał grę przez czas.
Nastawa czasu – na podstawie potencjometru P2, 3 ustawienia czasu: 5min, 3min, 1 min
RB3 – pierwszy gracz
RB5 – drugi gracz
