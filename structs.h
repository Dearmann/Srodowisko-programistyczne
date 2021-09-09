/** @file */

#ifndef STRUCTS_H
#define STRUCTS_H

/** Struktura reprezentująca pliki w projekcie */
typedef struct files_
{
	char filename[100];					///< nazwa pliku
	char file_in_projectname[100];		///< nazwa projektu w którym znajduje się plik
	struct files_* next;				///< wskaźnik na następny plik
}files;

/** Struktura reprezentująca projekty w solucji */
typedef struct projects_
{
	char projectname[100];				///< nazwa projektu
	int numberOfFiles;					///< liczba plików w projekcie
	struct projects_* next;				///< wskaźnik na następny projekt
	files* filelist;					///< wskaźnik na liste plików
}projects;

/** Struktura reprezentująca solucje */
typedef struct solution_
{
	char solutionname[100];				///< nazwa solucji
	int numberOfProjects;				///< liczba projektów w solucji
	projects* projectlist;				///< wskaźnik na liste projektów
}solution;

#endif