## Duże zadanie, część 3

# Zadanie gamma, część 3

Celem trzeciej części zadania jest dokończenie projektu gry gamma. Oczekujemy poprawienia ewentualnych błędów z poprzednich części zadania oraz zmodyfikowania programu. Obowiązują ustalenia z treści poprzednich części zadania i z forum dyskusyjnego dla studentów.

## Modyfikacja silnika gry

Należy poprawić działanie funkcji `gamma_golden_possible`, aby dawała wynik `true` wtedy i tylko wtedy, gdy gracz o numerze `player` może wykonać złoty ruch. Należy też stosownie zmodyfikować dokumentację tej funkcji.

## Modyfikacja trybu interaktywnego

Należy uatrakcyjnić wygląd planszy w trybie interaktywnym. Przykładowe pomysły:

*   dodanie kolorów, na przykład w celu wyróżnienia pól gracza, który ma wykonać ruch albo w celu odróżniania pól, gdy gracze mają wielocyfrowe numery i na planszy nie ma żadnego separatora między polami,
*   ulepszenie komunikatów pojawiających się pod planszą w trakcie gry i po jej zakończeniu,
*   jeśli pole gry zajmuje więcej niż jeden znak i na tym polu stoi kursor, to całe pole wyświetlane jest w negatywie,
*   sprawdzanie rozmiaru okna terminala i niedopuszczanie do gry (ze stosownym komunikatem), gdy jest za małe.

## Modyfikacja skryptu budującego

Należy dodać możliwość utworzenia pliku wykonywalnego z testami silnika gry. Czyli na przykład po wykonaniu:

    mkdir release
    cd release
    cmake ..

*   polecenie `make` tworzy plik wykonywalny `gamma` całej gry,
*   polecenie `make test` tworzy plik wykonywalny `gamma_test` z testami silnika gry,
*   polecenie `make doc` tworzy dokumentację w formacie `doxygen`.

Jak poprzednio funkcja `main` gry ma się znajdować w pliku `src/gamma_main.c`. Funkcja `main` uruchamiająca testy silnika gry ma się znajdować w pliku `src/gamma_test.c` – może to być plik, który został udostępniony w szablonie do części 1 zadania, lub plik z oficjalnymi testami do części 1 zadania. Można do tego pliku dodać własne testy.

Wskazówka: W pliku `CMakeList.txt` można dodać polecenie

    # Wskazujemy plik wykonywalny dla testów silnika.
    add_executable(gamma_test EXCLUDE_FROM_ALL ${TEST_SOURCE_FILES})

definiując uprzednio zmienną `TEST_SOURCE_FILES`.

## Dostarczamy

Rozwiązanie części 3 zadania powinno korzystać z własnego rozwiązania poprzednich jego części.

## Wymagamy

Jako rozwiązanie części 3 zadania wymagamy:

*   zachowania lub poprawienia struktury plików z poprzednich części,
*   zachowania lub poprawienia plików źródłowych z poprzednich części rozwiązania,
*   uzupełnienia pliku konfiguracyjnego dla programu `cmake`,
*   uzupełnienia dokumentacji w formacie `doxygen` tak, aby była przydatna dla programistów rozwijających program.

Gotowe rozwiązanie powinno się kompilować w dwóch wersjach: `release` i `debug`, jak to opisano w pierwszej części zadania.

**Uwaga: Niezmiernie istotne jest, aby przestrzegać opisanej specyfikacji nazw plików.**

## Oddawanie rozwiązania

Rozwiązanie należy oddawać, podobnie jak części 1 i 2, przez repozytorium git. W repozytorium mają się znaleźć wszystkie pliki niezbędne do zbudowania plików wykonywalnych i dokumentacji, i tylko te pliki. _W repozytorium nie wolno umieszczać plików binarnych ani tymczasowych._ W Moodlu jako rozwiązanie należy umieścić tekst zawierający identyfikator commitu finalnej wersji rozwiązania, na przykład:

    518507a7e9ea50e099b33cb6ca3d3141bc1d6638

Rozwiązanie należy zatwierdzić (`git commit`) i wysłać do repozytorium (`git push`) przed terminem podanym w Moodlu.

## Punktacja

Za w pełni poprawną implementację programu można zdobyć maksymalnie 20 punktów. Od tej oceny będą odejmowane punkty za poniższe uchybienia:

*   Za problemy ze skompilowaniem rozwiązania można stracić wszystkie punkty.
*   Za każdy test, którego program nie przejdzie, traci się do 1 punktu.
*   Za problemy z zarządzaniem pamięcią można stracić do 6 punktów.
*   Za niezgodną ze specyfikacją strukturę plików w rozwiązaniu, niezgodne ze specyfikacją nazwy plików w rozwiązaniu lub umieszczenie w repozytorium niepotrzebnych albo tymczasowych plików można stracić do 4 punktów.
*   Za złą jakość kodu, brzydki styl kodowania można stracić do 4 punktów.
*   Za ostrzeżenia wypisywane przez kompilator można stracić do 2 punktów.
*   Za braki w dokumentacji można stracić do 2 punktów.
*   Za nieuatrakcyjnienie wyglądu planszy w trybie interaktywnym można stracić do 3 punktów.

**Rozwiązania należy implementować samodzielnie pod rygorem niezaliczenia przedmiotu. Zarówno korzystanie z cudzego kodu, jak i prywatne lub publiczne udostępnianie własnego kodu jest zabronione.**
