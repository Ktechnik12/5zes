# Program do rysowania figur na kanwie

Ten program umożliwia rysowanie różnych figur geometrycznych na kanwie oraz zapisywanie ich do pliku.

## Wymagania

Aby uruchomić program, musisz mieć zainstalowany kompilator języka C++ oraz bibliotekę standardową.

## Konfiguracja

Program wymaga podania pliku konfiguracyjnego jako argument przy uruchamianiu. Plik konfiguracyjny powinien zawierać następujące informacje:

- `canvas_width`: szerokość kanwy w pikselach
- `canvas_height`: wysokość kanwy w pikselach
- `output_filename`: nazwa pliku, do którego zostanie zapisana kanwa
- `empty_symbol`: symbol reprezentujący puste miejsce na kanwie

Ponadto, w pliku konfiguracyjnym można zdefiniować figury do narysowania na kanwie. Każda figura powinna mieć określony typ, współrzędne x i y, rozmiar oraz symbol reprezentujący figurę.

## Uruchomienie

Aby uruchomić program, użyj następującej komendy w terminalu:

./program nazwa_pliku_konfiguracyjnego <nazwa_pliku_konfiguracyjnego>

## Przykładowy plik konfiguracyjny

Poniżej przedstawiam przykład pliku konfiguracyjnego:

Plik konfiguracyjny dla programu rysującego figury na kanwie
canvas_width 30
canvas_height 20
output_filename output.txt
empty_symbol ' '

figure square 3 5 4 #
figure circle 15 10 2 *
figure triangle3 10 14 6 *
figure triangle4 10 14 6 *
figure triangle1 10 14 6 *
figure triangle2 10 14 6 *


W powyższym przykładzie definiujemy kanwę o szerokości 30 pikseli i wysokości 20 pikseli. Wyjściowy plik zostanie zapisany jako `output.txt`, a puste miejsca na kanwie będą reprezentowane przez spacje (` `).

Następnie definiujemy figury: kwadrat, koło oraz cztery rodzaje trójkątów. Każda figura ma określone współrzędne środka, rozmiar oraz symbol.

## Wyjście

Po uruchomieniu programu zostanie wygenerowana kanwa z narysowanymi figurami, która zostanie wyświetlona w konsoli. Ponadto, kanwa zostanie zapisana do pliku o nazwie i lokalizacji podanej w pliku konfiguracyjnym.

