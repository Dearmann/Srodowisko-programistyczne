//#define _CRTDBG_MAP_ALLOC
#ifdef _WIN32
#else
#error This is Windows program only
#endif
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "functions.h"
#include "structs.h"
#include <conio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char** argv)
{
    int errorCode = 0;
    char projectLocation[261];
    GetCurrentDirectoryA(261, projectLocation);
    solution* newSolution = NULL;
    char solutionName[100];
    char projectName[100];
    char fileName[100];
    char directoryLocation[261];
    char choice = '1';
    do
    {
        errorCode = 0;
        printf("------------------------------\n");
        printf("Menu:\n1: New solution\n2: Add project\n3: Add file\n4: Delete project\n5: Delete file\n6: Save solution\n7: Load solution\n8: Load solution from directory\n9: Generate solution\n0: Quit\n");
        printf("------------------------------\n");
        display_solution(newSolution);
        choice = _getch();
        switch (choice)
        {
        case '1':
            delete_solution(&newSolution);
            printf("\nSolution name to create: ");
            if (scanf("%99s", solutionName) != EOF)
            {
                newSolution = new_solution(solutionName);
            }
            else
                printf("Error loading solution name\n");
            break;
        case '2':
            printf("Project name to create: ");
            if (scanf("%99s", projectName) != EOF)
            {
                new_project(newSolution, projectName);
            }
            else
                printf("Error loading project name\n");
            break;
        case '3':
            printf("To which project (name): ");
            if (scanf("%99s", projectName) != EOF)
            {
                printf("File name to create: ");
                if (scanf("%99s", fileName) != EOF)
                {
                    if (new_file(newSolution, projectName, fileName))
                        printf("\nProject \"%s\" not found.\n", projectName);
                }
                else
                    printf("Error loading file name\n");
            }
            else
                printf("Error loading project name\n");
            break;
        case '4':
            printf("Which project to delete: ");
            if (scanf("%99s", projectName) != EOF)
            {
                if (delete_project(newSolution, projectName))
                    printf("\nProject \"%s\" not found.\n", projectName);
            }
            else
                printf("Error loading project name\n");
            break;
        case '5':
            printf("From which project: ");
            if (scanf("%99s", projectName) != EOF)
            {
                printf("File name to delete: ");
                if (scanf("%99s", fileName) != EOF)
                {
                    errorCode = delete_file(newSolution, projectName, fileName);
                    if (errorCode == 1)
                        printf("\nProject \"%s\" not found.\n", projectName);
                    else if (errorCode == 2)
                        printf("\nFile \"%s\" in \"%s\" project not found.\n", fileName, projectName);
                }
                else
                    printf("Error loading file name\n");
            }
            else
                printf("Error loading project name\n");
            break;
        case '6':
            if (newSolution)
            {
                if (saveSolution(newSolution))
                    printf("\nWriting binary file failed!\n");
                else
                    printf("Solution saved as %s.save\n", newSolution->solutionname);
            }
            else
                printf("\nThere is no solution to save\n");
            break;
        case '7':
            printf("\nSolution name to load: ");
            if (scanf("%99s", solutionName) != EOF)
            {
                newSolution = loadSolution(solutionName);
                if (newSolution == NULL)
                    printf("\nReading binary file failed!\n");
            }
            else
                printf("Error loading solution name\n");
            break;
        case '8':
            printf("Copy and paste location of solution you want to load: ");
            if (scanf("%260s", directoryLocation) != EOF)
            {
                delete_solution(&newSolution);
                printf("\nName new solution: ");
                if (scanf("%99s", solutionName) != EOF)
                {
                    newSolution = new_solution(solutionName);
                }
                else
                {
                    printf("Error loading solution name\n");
                    break;
                }
                if (loadSolutionAlreadyCreated(newSolution, directoryLocation))
                    printf("Path not found: %s\n", directoryLocation);
            }
            else
                printf("Error loading solution location\n");
            break;
        case '9':
            SetCurrentDirectoryA(projectLocation);
            printf("Set location you want to generate your solution: ");
            if (scanf("%260s", directoryLocation) != EOF)
            {
                createSolutionDirectories(newSolution, directoryLocation);
                printf("Solution generated in %s\n", directoryLocation);
            }
            else
                printf("Error loading solution location\n");
            break;
        case '0':
            delete_solution(&newSolution);
            return 0;
        }
    } while (1);

    // Memory leak check
    //solution* solutionn = loadSolution("sol2");
    //display_solution(solutionn);
    //delete_solution(&solutionn);
    //display_solution(solutionn);
    //_CrtDumpMemoryLeaks();
}