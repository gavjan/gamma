## Duże zadanie, część 2

# Zadanie gamma, część 2

Jako drugą część dużego zadania należy zaimplementować program, który, korzystając z modułu silnika zaimplementowanego w części pierwszej, umożliwia przeprowadzanie rozgrywki. Interfejs programu ma być tekstowy. Program ma czytać dane ze standardowego wejścia, wyniki wypisywać na standardowe wyjście, a informacje o błędach na standardowe wyjście diagnostyczne. Program działa w dwóch trybach.

## Tryb wsadowy (ang. _batch mode_)

W trybie wsadowym program oczekuje poleceń, każde w osobnym wierszu. Rodzaj polecenia jest determinowany pierwszym znakiem wiersza. Jeśli polecenie wymaga podania parametru lub parametrów, to po tym znaku występuje odstęp składający się z co najmniej jednego białego znaku, a po tym odstępie pojawiają się kolejne parametry. Parametry polecenia są liczbami dziesiętnymi. Pomiędzy parametrami występuje odstęp składający się z co najmniej jednego białego znaku. Na końcu wiersza może wystąpić dowolna liczba białych znaków.

Na początku działania program oczekuje jednego z dwóch poleceń:

*   `B width height players areas`
*   `I width height players areas`

Polecenia te służą do utworzenia nowej gry za pomocą wywołania funkcji `gamma_new`. Poprawne wykonanie polecenia `B` jest kwitowane wypisaniem na standardowe wyjście komunikatu

`OK line`

gdzie `line` jest numerem wiersza, w którym pojawiło się to polecenie. Po czym program akceptuje polecenia:

*   `m player x y` – wywołuje funkcję `gamma_move`,
*   `g player x y` – wywołuje funkcję `gamma_golden_move`,
*   `b player` – wywołuje funkcję `gamma_busy_fields`,
*   `f player` – wywołuje funkcję `gamma_free_fields`,
*   `q player` – wywołuje funkcję `gamma_golden_possible`,
*   `p` – wywołuje funkcję `gamma_board`.

Program wypisuje wynik każdej z tych funkcji na standardowe wyjście. Wartość `false` wypisuje jako `0`, a wartość `true` jako `1`.

Program nie interpretuje pustych wierszy (składających się tylko ze znaku przejścia do nowego wiersza) oraz wierszy zaczynających się znakiem `#`.

Program kwituje każdy błędny wiersz (niepasujący do powyższego opisu) wypisaniem na standardowe wyjście diagnostyczne komunikatu

`ERROR line`

gdzie `line` jest numerem błędnego wiersza.

Wiersze na wejściu liczone są od jedynki. Liczone są wszystkie wiersze, łącznie z tymi, które nie są interpretowane.

W trybie wsadowym program kończy działanie, gdy skończą się dane na wejściu.

Dalsze szczegóły działania programu w trybie wsadowym można wydedukować, analizując załączone przykłady użycia.

Poprawne wykonanie polecenia `I` powoduje przejście do trybu interaktywnego.

## Tryb interaktywny (ang. _interactive mode_)

W trybie interaktywnym program wyświetla planszę, a pod planszą wiersz zachęcający gracza do wykonania ruchu. Program prosi o wykonanie ruchu kolejnych graczy, przy czym pomija graczy, dla których funkcja `gamma_free_fields` zwróciła `0` i funkcja `gamma_golden_possible` zwróciła `false`. Ruch wykonuje się, przesuwając kursor na wybrane pole za pomocą klawiszy ze strzałkami, a następnie wciskając klawisz `spacja`, aby wykonać zwykły ruch, lub klawisz `G`, aby wykonać złoty ruch. Gracz może zrezygnować z ruchu, wciskając klawisz `C`. Wciśnięcie klawiszy literowych powinno być rozpoznawane niezależnie od wciśnięcie klawisza `Shift` i stanu `CapsLock`.

Gra kończy się, gdy już żaden gracz nie może wykonać ruchu lub po jednokrotnym wciśnięciu kombinacji klawiszy `Ctrl-D`. Wtedy program wypisuje ostateczną planszę gry wraz z podsumowaniem, ile pól zajął każdy z graczy.

W trybie interaktywnym program powinien uniemożliwiać użytkownikom wykonywanie błędnych akcji.

Dalsze szczegóły działania programu w trybie interaktywnym można wydedukować, oglądając załączone animacje.

## Kończenie programu

Zasadniczo program powinien zakończyć się kodem 0, chyba że wystąpił jakiś krytyczny błąd – wtedy program powinien zakończyć się kodem 1. Przed zakończeniem działania program powinien jawnie zwolnić całą zaalokowaną pamięć, w szczególności powinien wywołać funkcję `gamma_delete`.

## Dostarczamy

Nie dostarczamy żadnego kodu źródłowego. Rozwiązanie drugiej części zadania powinno korzystać z własnego, ewentualnie samodzielnie zmodyfikowanego, rozwiązania części pierwszej.

## Wymagamy

Jako rozwiązanie części 2 zadania wymagamy:

*   umieszczenia kodu źródłowego implementacji w katalogu `src`,
*   uzupełnienia dokumentacji w formacie [doxygen](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21498 "Doxygen") tak, aby była przydatna dla programistów rozwijających program,
*   dostosowania pliku konfiguracyjnego dla programu [cmake](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21497 "CMake").

Gotowe rozwiązanie powinno się kompilować w dwóch wersjach: release i debug, jak to opisano w pierwszej części zadania.

**UWAGA 1: funkcja `main` programu musi znajdować się w pliku `src/gamma_main.c`.**

**UWAGA 2: w wyniku kompilacji powinien powstać plik wykonywalny `gamma`.**

## Oddawanie rozwiązania

Rozwiązanie należy oddawać, podobnie jak części 1, przez repozytorium [git](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21494 "Git"). W repozytorium mają się znaleźć wszystkie pliki niezbędne do zbudowania pliku wykonywalnego i dokumentacji oraz skrypt. _W repozytorium nie wolno umieszczać plików binarnych ani tymczasowych._ W Moodlu jako rozwiązanie należy umieścić tekst zawierający identyfikator commitu finalnej wersji rozwiązania, na przykład:

    518507a7e9ea50e099b33cb6ca3d3141bc1d6638

Rozwiązanie należy zatwierdzić ([git](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21494 "Git") commit) i wysłać do repozytorium ([git](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21494 "Git") push) przed terminem podanym w Moodlu.

## Wskazówki

Funkcje `scanf`, `atoi` itp. nie sprawdzają dokładnie poprawności wczytywanych wartości liczbowych. Lepiej zachowują się funkcje `strtoul`, `strtoull` lub tp.

Obsługę terminala Linuksowego w trybie interaktywnym można zrealizować za pomocą `ANSI escape codes`. Można też skorzystać z jakiejś biblioteki, o ile jest zainstalowana w laboratorium komputerowym.

## Punktacja

Za w pełni poprawną implementację programu można zdobyć maksymalnie 20 punktów. Od tej oceny będą odejmowane punkty za poniższe uchybienia:

*   Za problemy ze skompilowaniem rozwiązania można stracić wszystkie punkty.
*   Za każdy test, którego program nie przejdzie, traci się do 1 punktu.
*   Za problemy z zarządzaniem pamięcią można stracić do 6 punktów.
*   Za niezgodną ze specyfikacją strukturę plików w rozwiązaniu, niezgodne ze specyfikacją nazwy plików w rozwiązaniu lub umieszczenie w repozytorium niepotrzebnych albo tymczasowych plików można stracić do 4 punktów.
*   Za złą jakość kodu, brzydki [styl](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21479 "Styl") kodowania można stracić do 4 punktów.
*   Za ostrzeżenia wypisywane przez [kompilator](https://moodle.mimuw.edu.pl/mod/page/view.php?id=21482 "Kompilator") można stracić do 2 punktów.
*   Za braki w dokumentacji można stracić do 2 punktów.
*   Za „wrażenia nieartystyczne” z rozgrywki w trybie interaktywnym, czyli za ocenę wzrokową działania programu można stracić do 5 punktów.

**Rozwiązania należy implementować samodzielnie pod rygorem niezaliczenia przedmiotu.** z modułu silnika zaimplementowanego w części pierwszej, umożliwia przeprowadzanie rozgrywki. Interfejs programu ma być tekstowy. Program ma czytać dane ze standardowego wejścia, wyniki wypisywać na standardowe wyjście, a informacje o błędach na standardowe wyjście diagnostyczne. Program działa w dwóch trybach.
