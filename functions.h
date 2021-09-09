/** @file */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include "structs.h"

/**
 * @brief Funkcja tworząca nową solucje.
 * 
 * @param solutionname nazwa nowej solucji
 * @return solution* wskaźnik na nowo stworzoną solucje
 */
solution* new_solution(char* solutionname);

/**
 * @brief Funkcja tworząca nowy projekt.
 * 
 * @param solution wskaźnik na solucje do której będzie należał projekt
 * @param name nazwa nowego projektu
 */
void new_project(solution* solution, char* name);

/**
 * @brief Funkcja tworząca nowy plik.
 * 
 * @param solution wskaźnik na solucje do której będzie należał plik
 * @param project_name nazwa projektu w którym zostanie stworzony plik
 * @param file_name nazwa nowego pliku
 * @return int - numer błędu. 0 - brak błędu   1 - nie znaleziono projektu
 */
int new_file(solution* solution, char* project_name, char* file_name);

/**
 * @brief Funkcja usuwająca plik.
 * 
 * @param solution wskaźnik na solucje z której będzie usuwany plik
 * @param project_name nazwa projektu z którego zostanie usunięty plik
 * @param file_name nazwa usuwanego pliku
 * @return int - numer błędu. 0 - brak błędu   1 - nie znaleziono projektu   2 - nie znaleziono pliku
 */
int delete_file(solution* solution, char* project_name, char* file_name);

/**
 * @brief Usuwa wszystkie pliki. Wywoływana w delete_all_projects().
 * 
 * @param file wskaźnik na wskaźnik listy plików
 */
void delete_all_files(files** file);

/**
 * @brief Usuwa wszystkie projekty. Wywoływana w delete_solution().
 * 
 * @param project wskaźnik na wskaźnik listy projektów
 */
void delete_all_projects(projects** project);

/**
 * @brief Usuwa solucje wraz z jej projektami i plikami.
 * 
 * @param solution wskaźnik na wskaźnik solucji
 */
void delete_solution(solution** solution);

/**
 * @brief Usuwa projekt o podanej nazwie wraz z plikami.
 * 
 * @param solution wskaźnik na solucje z której zostanie usunięty projekt
 * @param name nazwa usuwanego pliku
 * @return int - numer błędu. 0 - brak błędu   1 - nie znaleziono projektu
 */
int delete_project(solution* solution, char* name);

/**
 * @brief Wyświetla liste plików w konsoli. Wywoływana w display_projects().
 * 
 * @param files wskaźnik na liste plików do wyświetlenia
 */
void display_files(files* files);

/**
 * @brief Wyświetla liste projektów w konsoli wraz z jej plikami. Wywoływana w display_solution().
 * 
 * @param pHead wskaźnik na liste projektów do wyświetlenia
 */
void display_projects(projects* pHead);

/**
 * @brief Wyświetla solucje wraz z jej projektami i plikami.
 * 
 * @param solution wskaźnik na solucje do wyświetlenia
 */
void display_solution(solution* solution);

/**
 * @brief Zapisuje pliki projektu w pliku binarnym.
 * 
 * @param file wskaźnik na pierwszy plik projektu
 * @param fptr wskaźnik na zmienną plikową
 * @param numberOfFiles liczba plików w projekcie
 */
void saveFiles(files* file, FILE* fptr, int numberOfFiles);

/**
 * @brief Zapisuje projekty solucji w pliku binarnym wraz z plikami projektu.
 * 
 * @param project wskaźnik na pierwszy projekt solucji
 * @param fptr wskaźnik na zmienną plikową
 * @param numberOfProjects  liczba projektów w solucji
 */
void saveProjects(projects* project, FILE* fptr, int numberOfProjects);

/**
 * @brief Zapisuje solucje w pliku binarnym wraz z jej projektami i plikami.
 * 
 * @param solution wskaźnik na solucje
 * @return int - numer błędu. 0 - brak błędu   1 - nie udało się zapisać pliku binarnego
 */
int saveSolution(solution* solution);

/**
 * @brief Wczytuje pliki projektu z pliku binarnego i tworzy ich strukture w programie.
 * 
 * @param solutionStructure wskaźnik na solucje do której zostaną wczytane pliki
 * @param projectName wskaźnik projektu do którego zostaną wczytane pliki
 * @param fptr wskaźnik na zmienną plikową
 * @param numberOfFiles liczba plików w projekcie
 */
void loadFiles(solution* solutionStructure, char* projectName, FILE* fptr, int numberOfFiles);

/**
 * @brief Wczytuje projekty solucji z pliku binarnego wraz z plikami projektu i tworzy ich strukture w programie.
 * 
 * @param solutionStrucutre wskaźnik na solucje do której zostaną wczytane projekty
 * @param numberOfProjects liczba projektów w solucji
 * @param fptr wskaźnik na zmienną plikową
 */
void loadProjects(solution* solutionStrucutre, int numberOfProjects, FILE* fptr);

/**
 * @brief Wczytuje solucje z pliku binarnego wraz z jej projektami i plikami oraz tworzy ich strukture w pamięci programu.
 * 
 * @param savedSolutionName nazwa solucji do wczytania
 * @return solution* wskaźnik na nowo stworzoną solucje
 */
solution* loadSolution(char* savedSolutionName);

/**
 * @brief Tworzy pliki w folderze projektu.
 * 
 * @param project wskaźnik na projekt w którym tworzone są pliki
 */
void createFiles(projects* project);

/**
 * @brief Tworzy foldery projektów w folderze solucji.
 * 
 * @param project wskaźnik na liste projektów do stworzenia
 */
void createProjectsDirectories(projects* project);

/**
 * @brief Tworzy folder solucji wraz z jej projektami i plikami
 * 
 * @param solutionStructure wskaźnik na solucje
 * @param destination ścieżka na której zostanie stworzona solucja
 */
void createSolutionDirectories(solution* solutionStructure, char* destination);

/**
 * @brief Funkcja szuka plików w podanej lokacji i tworzy liste tych plików w projekcie.
 * 
 * @param solutionStructure wskaźnik na solucje na której stworzony zostanie projekt z plikami
 * @param projectName wskaźnik na projekt do którego zostaną stworzone pliki
 * @param destination ścieżka w której pliki będą wyszukiwane
 */
void loadFilesAlreadyCreated(solution* solutionStructure, char* projectName, char* destination);

/**
 * @brief Funkcja szuka folderów w podanej lokacji i tworzy liste projektów na podstawie znalezionych folderów.
 * 
 * @param solutionStructure wskaźnik na solucje w której zostaną stworzone projekty
 * @param destination ścieżka w której foldery będą wyszukiwane
 * @return int - numer błędu. 0 - brak błędu   1 - nie znaleziono ścieżki solucji
 */
int loadSolutionAlreadyCreated(solution* solutionStructure, char* destination);

#endif