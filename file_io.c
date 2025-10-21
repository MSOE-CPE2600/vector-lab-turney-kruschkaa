

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "file_io.h"
#include "vect.h"

#define MAX_LINE_LENGTH 256

vect* read_file(char file_name[100], vect *vects, int *num_vects)
{
    FILE *fp;
    vect *new_vects;
    char line[MAX_LINE_LENGTH];
    char vect_name[30];
    char *token;
    float vect_comps[4];

    if (strstr(file_name, ".csv") == NULL)
    {
        file_name = strcat(file_name, ".csv");
    }

    fp = fopen(file_name, "r");

    if (!fp)
    {
        printf("Error opening file.\n");
        perror("File Error");
        return NULL;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        // Use strtok to split the line by the comma delimiter
        token = strtok(line, ",");

        // Add name 
        if (token != NULL)
        {
            strcpy(vect_name, token);
        }
        token = strtok(NULL, ","); // Get the next token
        // Process each token (field) in the line
        for (int i = 0; i < 3; i++)
        {
            if (token == NULL)
            {
                printf("Error reading vector.");
                return NULL;
            }

            vect_comps[i] = atof(token);

            token = strtok(NULL, ","); // Get the next token
        }

        vect vector = newvec(vect_name, vect_comps[0], vect_comps[1], vect_comps[2]);
        printvec(vector);

        if ((new_vects = addvec(&vects, num_vects, vector)) != NULL)
        {
            vects = new_vects;
        }
    }
    fclose(fp);
    return vects;
}

int write_file(char file_name[100], vect *vects)
{
    return 0;
}