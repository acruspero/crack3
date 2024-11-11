#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

// qsort compare function
int strcomp(const void *a, const void *b)
{
    char **aa = (char **)a;
    char **bb = (char **)b;
    return strcmp(*aa, *bb);
}

// bsearch compare function
int strsearch(const void *target, const void *elem)
{
    char *tt = (char *)target;
    char **ee = (char **)elem;
    
    return strcmp(tt , *ee);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // Read the hashes file into an array.
    // Use the loadFile function from fileutil.c
    int size;

    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char*), strcomp);

    // Open the password file for reading.
    FILE *in = fopen(argv[2], "r");
	if (!in)
	{
	    printf("Can't open password file for reading\n");
	    exit(1);
	}

    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    char password[PASS_LEN];
    int count = 0;

    while (fgets(password, PASS_LEN, in) != NULL)
    {
        // trim newline
        char *nl = strrchr(password, '\n');
        if (nl != NULL) *nl = '\0';
        //printf("<%s>\n", password);

        // hash each password
        char *hashedPassword = md5(password, strlen(password));
        //printf("%s\n", hashedPassword);

        // linear search
        //char *match = stringSearchAA(hashedPassword, hashes, size);

        // CHALLENGE1: Use binary search instead of linear search.
        char **match = bsearch(hashedPassword, hashes, size, sizeof(char*), strsearch);

        // If there's a match, display the password and its hash
        if (match)
        {
            // Ex: 5d41402abc4b2a76b9719d911017c592 hello
            printf("%s %s\n", password, *match);
            count++;
        }
        free(hashedPassword); // free malloc memory returned by md5
    }

    // Close the file and free memory
    fclose(in);
    freeAA(hashes, size);

    // Display the number of hashes found.
    printf("Hashes cracked: %d\n", count);
}
