#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "md5.h"
int arrsize;
const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5
    char *ghash= md5(guess, strlen(guess));
 
    if(strcmp (hash, ghash)==0 )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    // Compare the two hashes

    // Free any malloc'd memory

    //return 0;
}

// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.

char **read_dictionary(char *filename, int *size)
{
    int pass;
    struct stat info; 
    
    if (stat(filename, &info)== -1) return NULL;
    else pass= info.st_size;
    
    char *contents= malloc (pass);
    
    FILE *f= fopen(filename, "r");
    if (!f)
    {
        printf("Can`t open the file for reading \n");
        exit (1);
    }
    fread(contents, 1, pass, f);
    fclose (f);
    
    int numpasswords=0;
    
    for (int i =0; i< pass; i++)
    {
        if (contents [i]== '\n')
        {
            numpasswords++;
            contents[i]= '\0';
        }
    }

    char **passwords= malloc ( numpasswords* sizeof(char *));
    
    passwords[0]= contents;
    int j=1;
    
    for (int i=0; i< pass-1; i++)
    {
        if (contents [i]== '\0')
        {
            passwords [j]= &contents[i+1];
            j++;
        }
    }
    /*for (int i=0; i < numpasswords; i++)
    {
        printf ("%d %s\n", i, passwords[i]); // for printing the array
    }*/
    
     *size = numpasswords;
     arrsize= numpasswords;
     
    return passwords;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the dictionary file into an array of strings.
    
    int dlen;
 
    char **dict = read_dictionary(argv[2], &dlen);
    
     // Open the hash file for reading.
    FILE *h= fopen(argv[1], "r");
    if (!h)
    {
        printf("Unable to open the hashes file for reading. \n");
        exit (1);
    }
    
    char line [100];
    char *ghash ;
    
    while (fgets(line,100,h)!=NULL)
    {
        
        line[32]= '\0';
        
        for (int i=0; i<arrsize ; i++)
        {
            if(tryguess(line, dict[i])==1)
            {
                printf("%s\n", dict[i]);
            }
        }

    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    // Need two nested loops.
    }
}