#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "structs.h"
#include <windows.h>

solution* new_solution(char* solutionname)
{
	int length = strlen(solutionname);
	solution* newsolution = (solution*) malloc(sizeof(solution));
	strcpy(newsolution->solutionname, solutionname);
	newsolution->numberOfProjects = 0;
	newsolution->projectlist = NULL;
	return newsolution;
}

void new_project(solution* solution, char* name)
{
	if (solution)
	{
		if (!solution->projectlist)
		{
			solution->projectlist = (projects*)malloc(sizeof(projects));
			solution->numberOfProjects++;
			strcpy(solution->projectlist->projectname, name);
			solution->projectlist->numberOfFiles = 0;
			solution->projectlist->next = NULL;
			solution->projectlist->filelist = NULL;
		}
		else
		{
			projects* p = solution->projectlist;
			while (p->next)
				p = p->next;
			p->next = (projects*)malloc(sizeof(projects));
			solution->numberOfProjects++;
			strcpy(p->next->projectname, name);
			p->next->numberOfFiles = 0;
			p->next->next = NULL;
			p->next->filelist = NULL;
		}
	}

}

int new_file(solution* solution, char* project_name, char* file_name)
{
	if (solution)
	{
		projects* project = solution->projectlist;
		while (project)
		{
			if (!strcmp(project->projectname, project_name))
			{
				int length = strlen(file_name) + 1;
				if (!project->filelist)
				{
					project->filelist = (files*)malloc(sizeof(files));
					project->numberOfFiles++;
					strcpy(project->filelist->filename, file_name);
					strcpy(project->filelist->file_in_projectname, project_name);
					project->filelist->next = NULL;
				}
				else
				{
					files* p = project->filelist;
					while (p->next)
						p = p->next;
					p->next = (files*)malloc(sizeof(files));
					project->numberOfFiles++;
					strcpy(p->next->filename, file_name);
					strcpy(p->next->file_in_projectname, project_name);
					p->next->next = NULL;
				}
				return 0;
			}
			project = project->next;
		}
		return 1;
	}
}

int delete_file(solution* solution, char* project_name, char* file_name)
{
	if (solution)
	{
		projects* project = solution->projectlist;
		while (project)
		{
			if (!strcmp(project->projectname, project_name))
			{
				if (project->filelist)
				{
					// deleting first element
					if (!strcmp(project->filelist->filename, file_name))
					{
						project->numberOfFiles--;
						files* temp = project->filelist->next;
						free(project->filelist);
						project->filelist = temp;
						return 0;
					}
					// deleting element in the middle/last
					if (project->filelist->next)
					{
						files* p = project->filelist;
						while (p->next != NULL)
						{
							if (!strcmp(p->next->filename, file_name))
							{
								project->numberOfFiles--;
								if (p->next->next == NULL) // element is last
								{
									free(p->next);
									p->next = NULL;
									return 0;
								}
								else // element is in the middle
								{
									files* temp = p->next->next;
									free(p->next);
									p->next = temp;
									return 0;
								}
							}
							p = p->next;
						}
					}
					return 2;
				}
			}
			project = project->next;
		}
		return 1;
	}

}

void delete_all_files(files** file)
{
	if (*file)
	{
		files* file2 = (*file)->next;
		delete_all_files(&file2);
		free(*file);
		*file = NULL;
	}
}

void delete_all_projects(projects** project)
{
	if (*project)
	{
		files* file = (*project)->filelist;
		projects* project2 = (*project)->next;
		delete_all_projects(&project2);
		delete_all_files(&file);
		free(*project);
		*project = NULL;
	}
}

void delete_solution(solution** solution)
{
	if (*solution)
	{
		projects* project = (*solution)->projectlist;
		delete_all_projects(&project);
		free(*solution);
		*solution = NULL;
	}
}

int delete_project(solution* solution, char* name)
{
	if (solution)
	{
		if (solution->projectlist)
		{
			// deleting first element
			if (!strcmp(solution->projectlist->projectname, name))
			{
				solution->numberOfProjects--;
				files* file = solution->projectlist->filelist;
				delete_all_files(&file);
				projects* temp = solution->projectlist->next;
				free(solution->projectlist);
				solution->projectlist = temp;
				return 0;
			}
			// deleting element in the middle/last
			if (solution->projectlist->next)
			{
				projects* p = solution->projectlist;
				while (p->next != NULL)
				{
					if (!strcmp(p->next->projectname, name))
					{
						solution->numberOfProjects--;
						files* file = p->next->filelist;
						if (p->next->next == NULL) // element is last
						{
							delete_all_files(&file);
							free(p->next);
							p->next = NULL;
							return 0;
						}
						else // element is in the middle
						{
							delete_all_files(&file);
							projects* temp = p->next->next;
							free(p->next);
							p->next = temp;
							return 0;
						}
					}
					p = p->next;
				}
			}
			return 1;
		}
	}
}

void display_files(files* files)
{
	while (files)
	{
		printf("\n         *%s", files->filename);
		files = files->next;
	}
}

void display_projects(projects* pHead)
{
	while (pHead)
	{
		printf("\n      -%s", pHead->projectname);
		if (pHead->filelist)
			display_files(pHead->filelist);
		pHead = pHead->next;
	}
}

void display_solution(solution* solution)
{
	if (solution)
	{
		printf("Solution:\n");
		printf("   +%s", solution->solutionname);
		display_projects(solution->projectlist);
		printf("\n");
	}
}

void saveFiles(files* file, FILE* fptr, int numberOfFiles)
{
	for (int i = 0; i < numberOfFiles; i++)
	{
		fwrite(&file->filename, sizeof(file->filename), 1, fptr);
		file = file->next;
	}
}

void saveProjects(projects* project, FILE* fptr, int numberOfProjects)
{
	for (int i = 0; i < numberOfProjects; i++)
	{
		fwrite(&project->projectname, sizeof(project->projectname), 1, fptr);
		fwrite(&project->numberOfFiles, sizeof(project->numberOfFiles), 1, fptr);
		saveFiles(project->filelist, fptr, project->numberOfFiles);
		project = project->next;
	}
}

int saveSolution(solution* solution)
{
	char saveFileName[100];
	FILE* fptr = NULL;
	sprintf(saveFileName, "%s.save", solution->solutionname);
	fptr = fopen(saveFileName, "wb");
	if (fptr == NULL)
		return 1;
	fwrite(&solution->solutionname, sizeof(solution->solutionname), 1, fptr);
	fwrite(&solution->numberOfProjects, sizeof(solution->numberOfProjects), 1, fptr);
	saveProjects(solution->projectlist, fptr, solution->numberOfProjects);
	fclose(fptr);
	return 0;
}

void loadFiles(solution* solutionStructure, char* projectName, FILE* fptr, int numberOfFiles)
{
	char fileName[100];
	for (int i = 0; i < numberOfFiles; i++)
	{
		fread(fileName, sizeof(fileName), 1, fptr);
		new_file(solutionStructure, projectName, fileName);
	}
}

void loadProjects(solution* solutionStrucutre, int numberOfProjects, FILE* fptr)
{
	char projectName[100];
	int numberOfFiles;
	//projects* currentProject;
	for (int i = 0; i < numberOfProjects; i++)
	{
		fread(projectName, sizeof(projectName), 1, fptr);
		fread(&numberOfFiles, sizeof(numberOfFiles), 1, fptr);
		new_project(solutionStrucutre, projectName);
		loadFiles(solutionStrucutre, projectName, fptr, numberOfFiles);
	}
}

solution* loadSolution(char* savedSolutionName)
{
	char saveFileName[100];
	char solutionName[100];
	int numberOfProjects;
	solution* solutionStructure = NULL;
	FILE* fptr = NULL;
	sprintf(saveFileName, "%s.save", savedSolutionName);
	fptr = fopen(saveFileName, "rb");
	if (fptr == NULL)
		return NULL;
	fread(solutionName, sizeof(solutionName), 1, fptr);
	fread(&numberOfProjects, sizeof(numberOfProjects), 1, fptr);
	solutionStructure = new_solution(solutionName);
	loadProjects(solutionStructure, numberOfProjects, fptr);
	fclose(fptr);
	return solutionStructure;
}

void createFiles(projects* project)
{
	if (project->filelist)
	{
		files* file = project->filelist;
		char solutionDirectory[261];		// 260 characters is maximum length of path in windows 10
		GetCurrentDirectoryA(261, solutionDirectory);
		char projectDirectory[261];
		strcpy(projectDirectory, solutionDirectory);
		strcat(projectDirectory, "/");
		strcat(projectDirectory, project->projectname);
		SetCurrentDirectoryA(projectDirectory);
		CreateFileA(file->filename, GENERIC_WRITE, 0, NULL, 2, FILE_ATTRIBUTE_NORMAL, GENERIC_READ);
		while (file->next)
		{
			file = file->next;
			CreateFileA(file->filename, GENERIC_WRITE, 0, NULL, 2, FILE_ATTRIBUTE_NORMAL, GENERIC_READ);
		}
		SetCurrentDirectoryA(solutionDirectory);
	}
}

void createProjectsDirectories(projects* project)
{
	if (project)
	{
		CreateDirectoryA(project->projectname, NULL);
		createFiles(project);
		while (project->next)
		{
			project = project->next;
			CreateDirectoryA(project->projectname, NULL);
			createFiles(project);
		}
	}
}

void createSolutionDirectories(solution* solutionStructure, char* destination)
{
	SetCurrentDirectoryA(destination);
	CreateDirectoryA(solutionStructure->solutionname, NULL);
	strcat(destination, "/");
	strcat(destination, solutionStructure->solutionname);
	SetCurrentDirectoryA(destination);
	createProjectsDirectories(solutionStructure->projectlist);
}

void loadFilesAlreadyCreated(solution* solutionStructure, char* projectName, char* destination)
{
	WIN32_FIND_DATA fileFound;
	HANDLE h = NULL;
	char destinationToSearch[261];
	sprintf(destinationToSearch, "%s/*.*", destination);
	h = FindFirstFileA(destinationToSearch, &fileFound);
	if (h == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (strcmp(fileFound.cFileName, ".") != 0 && strcmp(fileFound.cFileName, "..") != 0)
		{
			if (!(fileFound.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				new_file(solutionStructure, projectName, fileFound.cFileName);
			}
		}
	} while (FindNextFileA(h, &fileFound));
}

int loadSolutionAlreadyCreated(solution* solutionStructure, char* destination)
{
	WIN32_FIND_DATA fileFound;
	HANDLE h = NULL;
	char destinationToSearch[261];
	char destinationToSearchForFiles[261];
	sprintf(destinationToSearch, "%s/*.*", destination);
	h = FindFirstFileA(destinationToSearch, &fileFound);
	if (h == INVALID_HANDLE_VALUE)
		return 1;
	do
	{
		if (strcmp(fileFound.cFileName, ".") != 0 && strcmp(fileFound.cFileName, "..") != 0)
		{
			if (fileFound.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				new_project(solutionStructure, fileFound.cFileName);
				sprintf(destinationToSearchForFiles, "%s/%s", destination, fileFound.cFileName);
				loadFilesAlreadyCreated(solutionStructure, fileFound.cFileName, destinationToSearchForFiles);
			}
		}
	} while (FindNextFileA(h, &fileFound));
	return 0;
}