## Duże zadanie, część 1

# Zadanie gamma, część 1

Tegoroczne duże zadanie polega na zaimplementowaniu gry gamma. Grę rozgrywa się na prostokątnej planszy,
która składa się z jednakowych kwadratowych pól. Pola sąsiadujące na planszy to takie, które stykają się bokami.
Pól stykających się tylko rogami nie uważamy za sąsiadujące. Pola tworzą obszar, jeśli z każdego z nich można
dojść do innego, przechodząc jedynie przez pola sąsiadujące. Pojedyncze pole też jest obszarem. Grać może
jedna lub więcej osób. Na początku gry plansza jest pusta. Gracze kolejno zajmują po jednym polu, stawiając na
nim swój pionek. Gracz może zająć dowolne niezajęte pole, przestrzegając jedynie zasady, że zbiór pól zajętych
przez tego samego gracza nie może w żadnej fazie gry składać się z więcej niż, będącej parametrem gry,
maksymalnej liczby obszarów. Każdy gracz jeden raz w całej rozgrywce może wykonać złoty ruch, który polega
na zabraniu z planszy pionka innego gracza i postawieniu w jego miejsce swojego pionka, ale ten ruch nadal nie
może naruszać zasady maksymalnej liczby zajętych obszarów przez żadnego z graczy. Gracz, który nie jest w
stanie wykonać ruchu zgodnego z powyższą zasadą, wypada z gry, ale może wrócić do gry po jakimś złotym
ruchu innego gracza. Gra kończy się, gdy już żaden gracz nie może wykonać ruchu. Wygrywa gracz, który zajmie
największą liczbę pól.

Jako pierwszą część zadania należy zaimplementować moduł „silnika” gry. Opis interfejsu modułu znajduje się w
pliku `src/gamma.h` w formacie komentarzy dla programu doxygen. Przykład użycia znajduje się w pliku
`src/gamma_test.c`.

Kolejne części zadania będą polegały na rozbudowywaniu tego silnika i dodaniu do niego interfejsu (tekstowego).

## Dostarczamy

- `src/gamma.h` – deklaracja interfejsu modułu wraz z jego dokumentacją w formacie doxygen,
- `src/gamma_test.c` – przykład użycia modułu,
- `CMakeLists.txt` – plik konfiguracyjny programu cmake,
- `Doxyfile.in` – plik konfiguracyjny programu doxygen,
- `MainPage.dox` – strona główna dokumentacji w formacie doxygen.

Zastrzegamy sobie możliwość nanoszenia poprawek do tego szablonu. Będziemy je umieszczać w gałęzi
template/part1. Lista poprawek:
- na razie nie ma żadnych poprawek.

## Wymagamy

Jako rozwiązanie części 1 zadania wymagamy:

- stworzenia pliku `src/gamma.c` z implementacją modułu,
- uzupełnienia dokumentacji w formacie doxygen tak, aby była przydatna dla programistów rozwijających moduł.

Powinna być możliwość skompilowania rozwiązania w dwóch wersjach: release i debug. Wersję release
kompiluje się za pomocą sekwencji poleceń:
```
mkdir release
cd release
cmake ..
make
make doc
```
Wersję debug kompiluje się za pomocą sekwencji poleceń:
```
mkdir debug
cd debug
cmake -D CMAKE_BUILD_TYPE=Debug ..
make
make doc
```

W wyniku kompilacji odpowiednio w katalogu `release` lub `debug` powinien powstać plik wykonywalny `gamma`
oraz dokumentacja. W poleceniu cmake powinno być również możliwe jawne określenie wariantu release
budowania pliku wynikowego:

```
cmake -D CMAKE_BUILD_TYPE=Release ..
```

Zawartość dostarczonych przez nas plików można modyfikować, o ile nie zmienia to interfejsu modułu i
zachowuje wymagania podane w treści zadania, przy czym nie wolno usuwać opcji kompilacji:
`-std=c11 -Wall -Wextra`. Zmiany mogą dotyczyć np. stylu, dokumentacji, deklaracji typedef, włączania plików
nagłówkowych, implementacji funkcji jako `static inline`. Inne pliki źródłowe, będące częścią rozwiązania,
należy umieścić w katalogu `src`. Funkcja `main` programu musi znajdować się w pliku `src/gamma_test.c`, ale
zawartość tego pliku nie będzie oceniana w tej części zadania.

## Oddawanie rozwiązania


Rozwiązanie należy oddawać przez wspomniane wyżej repozytorium git. W repozytorium mają się znaleźć
wszystkie pliki niezbędne do zbudowania pliku wykonywalnego oraz dokumentacji. W repozytorium nie wolno
umieszczać plików binarnych ani tymczasowych. W Moodle'u jako rozwiązanie należy umieścić tekst zawierający
identyfikator commitu finalnej wersji rozwiązania, na przykład:

```
518507a7e9ea50e099b33cb6ca3d3141bc1d
```

Rozwiązanie należy zatwierdzić (`git commit`) i wysłać do repozytorium (`git push`) przed terminem podanym
w Moodle'u.
