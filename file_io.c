/**
* @file: file_io.c
* @brief Defining functions to read and write vectors in csv files
* 
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Author: Alexander Kruschka
* Date: 10/21/2025
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "file_io.h"
#include "vect.h"

#define MAX_LINE_LENGTH 256

vect* read_file(char file_name[100], vect *vects, int *num_vects)
{
    // Declaring variables to be used
    FILE *fp;
    vect *new_vects;
    char line[MAX_LINE_LENGTH];
    char vect_name[30];
    char *token;
    float vect_comps[4];

    // If '.csv' isn't present in file name, append it
    if (strstr(file_name, ".csv") == NULL)
    {
        file_name = strcat(file_name, ".csv");
    }

    // Open the file
    fp = fopen(file_name, "r");

    // If null, print error and return with NULL to be handled accordingly in main
    if (!fp)
    {
        printf("Error opening file.\n");
        perror("File Error");
        return NULL;
    }

    // Read through each line of the .csv file
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        // Use strtok to split the line by the comma delimiter
        token = strtok(line, ", ");

        // Get the name of the vector
        if (token != NULL)
        {
            strcpy(vect_name, token);
        }

        // Get the next token
        token = strtok(NULL, ", ");

        // Go through the next three tokens for x, y, and z of vector
        for (int i = 0; i < 3; i++)
        {
            // Error checking for invalid vectors and return NULL to be handled in main
            if (token == NULL)
            {
                printf("Error reading vector.");
                return NULL;
            }

            // Add float of x, y, or z to vector components array
            vect_comps[i] = atof(token);

            // Get the next token
            token = strtok(NULL, ",");
        }

        // Create and print the vector using the name and acquired components
        vect vector = newvec(vect_name, vect_comps[0], vect_comps[1], vect_comps[2]);
        printvec(vector);

        // Add the vector to the array with error checking for failed memory acquisition
        if ((new_vects = addvec(&vects, num_vects, vector)) != NULL)
        {
            vects = new_vects;
        }
    }
    // Close file pointer and return the pointer to the new array of vectors
    fclose(fp);
    return vects;
}

int write_file(char file_name[100], vect *vects, int num_vects)
{
    // Declaring file pointer to be used
    FILE *fp;

    // Append .csv to file name if not present
    if (strstr(file_name, ".csv") == NULL)
    {
        file_name = strcat(file_name, ".csv");
    }
    
    // Open or create the file to write into
    fp = fopen(file_name, "w");

    // If opening fails, print error and return error code 1
    if (!fp)
    {
        printf("Error writing file.\n");
        perror("File Error");
        return 1;
    }

    // Go through each vector in array and print each formatted on a new line
    for (int line = 0; line < num_vects; line++)
    {
        vect vector = vects[line];
        fprintf(fp, "%s,%f,%f,%f\n", vector.name, vector.x, vector.y, vector.z);
    }

    // Close the file pointer with a success message and return success
    fclose(fp);
    printf("File '%s' written and saved successfully.\n", file_name);
    return 0;
}