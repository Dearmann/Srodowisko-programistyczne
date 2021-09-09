# Srodowisko-programistyczne
Projekt semestr 2, Programowanie Komputerów

# Treść zadania
Proszę napisać program do zarządzania strukturą plików środowiska programistycznego. Każdy z plików znajduje się w dokładnie jednym projekcie. Projekty zgrupowane są w solucji. 
Program powinien umożliwiać: 
1. przechowywanie powyższej struktury w pamięci oraz jej modyfikację (dodawanie i usuwanie elementów), 
2. import oraz eksport struktury z/do pliku binarnego, 
3. utworzenie struktury katalogów i plików na dysku we wskazanej przez użytkownika lokalizacji, odpowiadającej strukturze solucji, 
4. utworzenie struktury na bazie istniejącej struktury katalogów i plików we wskazanej przez użytkownika lokalizacji.  

Uwagi techniczne: Sugerowana struktura danych - lista projektów, której każdy element zawiera podwieszoną listę plików. W środowisku Windows do pobierania zawartości katalogu oraz tworzenia katalogów można wykorzystać funkcje WinAPI (niestandardowa biblioteka windows.h).

# Analiza zadania
Zagadnienie przedstawia problem tworzenia list i odczytu konkretnych danych z tych list do celów przedstawionych w treści zadania.

# Struktury danych
W programie wykorzystano strukturę solucji, która zawiera listę jednokierunkową projektów, które zawierają listę jednokierunkową plików. 
Taka struktura umożliwia łatwe przyporządkowanie projektów solucji i plików projektom.

# Algorytmy
Program wyszukuje określone elementy solucji, porównując szukaną nazwę elementu do nazwy elementu znalezionego i jeśli pasują, wykonuje określoną operację np. stworzenie pliku w znalezionym projekcie. Jeśli nie jest to szukany element to przechodzi do następnego poprzez wskaźnik next. Algorytm kończy się na wskaźniku NULL.
Usuwanie solucji realizowane jest przez rekurencyjne przejście przez listę.

# Specyfikacja zewnętrzna
Program uruchamiany jest z pliku devenv.exe po uruchomieniu którego ukazuje się menu z 10 opcjami.

![menu](https://user-images.githubusercontent.com/49723341/132547694-24e4a3e0-6726-4120-8e53-26b403dd4fbc.png)

Opcje 1-5 zmieniają strukturę solucji zapisaną tylko w pamięci programu.
Szósta opcja - Save solution zapisuje strukturę solucji w pliku o rozszerzeniu .save w miejscu uruchomienia programu. Opcja Load solution wczytuje solucje z lokacji uruchomienia programu o nazwie podanej przez użytkownika.
Opcja ósma i dziewiąta oczekują od użytkownika podanie ścieżki do wczytania lub generacji solucji.

# Specyfikacja wewnętrzna
Program został zrealizowany zgodnie z paradygmatem strukturalnym. W programie rozdzielono interfejs (komunikację z użytkownikiem) od logiki aplikacji - modyfikacji list, generowania i wczytywania plików binarnych, generowania katalogów i wczytywania z już istniejących.

# Ogólna struktura programu
W funkcji głównej znajduje się instrukcja wyboru, której fraza wywołana zależy od wyboru użytkownika. Fraza 1 wywołuje funkcję new_solution, fraza 2 funkcję new_project, fraza 3 funkcję new_file, fraza 4 funkcję delete_project a fraza 5 funkcję delete_file. Każda z fraz sprawdza, czy nazwa solucji/projektu/pliku podana przez użytkownika jest poprawna.
Fraza 6 zawiera funkcję wytwarzającą plik binarny ze strukturą solucji - saveSolution która zwraca 0 gdy zostanie wywołana poprawnie lub 1 gdy nie uda się stworzyć pliku binarnego. Fraza 7 wczytuje zapisany plik binarny ze strukturą solucji przy użyciu funkcji loadSolution, która zwraca NULL przy nieudanej próbie odczytu i właściwy wskaźnik przy udanej.
Fraza 8 tak samo jak fraza  1 wywołuje new_solution, po czym wywołuje swoją własną funkcję - loadSolutionAlreadyCreated która zwraca 1 przy nieznalezieniu ścieżki i 0 przy znalezieniu.
Fraza 9 wywołuje funkcję createSolutionDirectories, która tworzy katalogi solucji zapisanej w pamięci programu.
Fraza 0 usuwa z pamięci solucje wraz z jej projektami i plikami przy użyciu funkcji delete_solution, po czym zamyka program, zwracając 0.

# Szczegółowy opis typów i funkcji
Szczegółowy opis typów i funkcji zawarty w pliku "Dokumentacja - Środowisko programistyczne.pdf".

# Testowanie
Program został przetestowany, wprowadzając różnej długości nazwy solucji/projektów/plików, które może wprowadzić użytkownik. Zbyt długie nazwy zostają ucięte do ich maksymalnej długości. Niepoprawne ścieżki wyświetlają odpowiedni komunikat nieistnienia takiej lokacji. Próba wczytania solucji z nieistniejącego pliku binarnego wyświetla użytkownikowi odpowiedni komunikat o nieistnieniu takiego pliku. Zapisanie nieistniejącej solucji w pliku binarnym również kończy się odpowiednim komunikatem. 
Program został sprawdzony pod kątem wycieków pamięci.

# Wnioski
Program “Środowisko programistyczne” jest prostym programem, który wykorzystuje nieskomplikowaną strukturę listy jednokierunkowej w liście jednokierunkowej. Jednak wymaga użycia dużej ilości funkcji przez wiele operacji wykonywanych na wyżej wymienionej strukturze. Trudne okazały się operacje na tekstowym typie danych przez konieczność użycia specyficznych funkcji dla języka C do modyfikacji tego typu danych. Problematyczne okazały się ścieżki wprowadzane przez użytkownika, które zawierały znaki białe, co wymagało rozważenie innej funkcji odczytującej dane.

# Literatura
https://docs.microsoft.com/en-us/windows/win32/fileio/directory-management-functions

https://docs.microsoft.com/en-us/windows/win32/api/fileapi/

https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows

https://docs.microsoft.com/pl-pl/cpp/cpp/lvalue-reference-declarator-amp?view=vs-2019
