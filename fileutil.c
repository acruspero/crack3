#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	int capacity = 1;
	*size = 0;

	// Allocate memory for an array of strings (arr)
	char **arr = malloc(capacity * sizeof(char *));

	// Read the file line by line
	char input[1000];
    while (fgets(input, 1000, in) != NULL)
	{
		// Expand array if necessary (realloc)
		if (*size == capacity)
		{
			capacity *= 2;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		// Trim newline
		char *nl = strrchr(input, '\n');
        if (nl != NULL) *nl = '\0';

		// Allocate memory for the string (str)
		int length = strlen(input);
		char *str = malloc(length + 1);

		// Copy each line into the string (use strcpy)
		strcpy(str, input);
		//printf("<%s>\n", str);

		// Attach the string to the large array
		arr[*size] = str;

		(*size)++;
	}
    // Close the file
	fclose(in);

	// Return pointer to the array of strings
	return arr;
}

char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	int capacity = 1;
	*size = 0;
	
	// Allocate memory for an 2D array, using COLS as the width
	char (*arr)[COLS] = malloc(capacity * sizeof(char[COLS]));

	// Read the file line by line into a buffer
	char input[1000];
    while (fgets(input, 1000, in) != NULL)
	{
		// Trim newline
		char *nl = strrchr(input, '\n');
        if (nl != NULL) *nl = '\0';

		// Expand array if necessary (realloc)
		if (*size == capacity)
		{
			capacity *= 2;
			arr = realloc(arr, capacity * sizeof(char[COLS]));
		}

		// Copy each line from the buffer into the array (use strcpy)
		strcpy(arr[*size], input);
		//printf("<%s>\n", arr[*size]);
		(*size)++;
	}
	
	// Close the file
	fclose(in);

	// Return pointer to the array
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (strstr(lines[i], target)) return lines[i];
	}
	return NULL;
}

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    for (int i = 0; i < size; i++)
	{
		if (!strstr(lines[i], target)) return lines[i];
	}
	return NULL;
}

char * stringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(lines[i], target)) return lines[i];
	}
	return NULL;
}

char * stringSearch2D(char *target, char (*lines)[COLS], int size)
{
    for (int i = 0; i < size; i++)
	{
		if (!strcmp(lines[i], target)) return lines[i];
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		// free each individual string
		free(arr[i]);
	}
	// free the main array
	free(arr);
}


void free2D(char (*arr)[COLS])
{
	free(arr); // free main array
}