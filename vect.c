/**
* @file: vect.c
* @brief Defining functions to perform vector calculations as well as various other functions for table interfacing
* 
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Author: Alexander Kruschka
* Date: 10/07/2025
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "vect.h"

vect newvec(char name[30], float x, float y, float z)
{
    // Initialize new vector
    vect newVector;

    // Add values to vector struct
    strcpy(newVector.name, name);
    newVector.x = x;
    newVector.y = y;
    newVector.z = z;

    // Return new vector
    return newVector;
}

int getvec(char name[30], vect *vects, int total_vectors)
{
    // Initialize index to -1, assuming it doesn't find vector in array
    int vectIndex = -1;

    // For each vector, if the name matches, set index to that location
    for (int i = 0; i < total_vectors; i++)
    {
        if (!strcmp(name, vects[i].name))
        {
            vectIndex = i;
        }
    }

    // Return index
    return vectIndex;
}

int printvec(vect vector)
{
    // Print each component of the array with spacing and three decimal points of precision
    printf("%10s:%10.3f,%10.3f,%10.3f\n", vector.name, vector.x, vector.y, vector.z);
    return 0;
}

vect sumvec(char name[30], vect a, vect b)
{
    // Add vector components together in a new vector and return that result
    return newvec(name, a.x + b.x, a.y + b.y, a.z + b.z);
}

vect subvec(char name[30], vect a, vect b)
{
    // Subtract vector components together in a new vector and return that result
    return newvec(name, a.x - b.x, a.y - b.y, a.z - b.z);
}

vect scalarmult(char name[30], vect a, double scalar)
{
    // Multiple vector components with a scalar in a new vector and return that result
    return newvec(name, a.x * scalar, a.y * scalar, a.z * scalar);
}

vect dotvec(char name[30], vect a, vect b)
{
    // Dot product vector components together in a new vector and return that result
    return newvec(name, (a.x * b.x) + (a.y * b.y) + (a.z * b.z), 0, 0);
}

vect crossvec(char name[30], vect a, vect b)
{
    // Declare and calculate the cross product components and then return them in a new vector
    double new_x = (a.y * b.z) - (a.z * b.y);
    double new_y = (a.z * b.x) - (a.x * b.z);
    double new_z = (a.x * b.y) - (a.y * b.x);
    return newvec(name, new_x, new_y, new_z);
}

vect* addvec(vect **vects, int *total_vectors, vect a)
{
    // Determine if array already exists and get index if valid
    int existing_index = getvec(a.name, *vects, *total_vectors);

    // If it already exists, overwrite the current vector of the same name with new numbers,
    // otherwise add into a new index value of the array and increment index tracker with new memory
    if (existing_index != -1)
    {
        (*vects)[existing_index] = a;
    }
    else
    {
        // Increase vector count
        *total_vectors = *total_vectors + 1;

        // Allocate memory for an extra vector in array with error checking
        vect *new_vects = realloc(*vects, *total_vectors * sizeof(vect));
        if (new_vects != NULL)
        {
            *vects = new_vects;
            (*vects)[*total_vectors - 1] = a;
        }
        else
        {
            *total_vectors = *total_vectors - 1;
            printf("Error: Out of memory or failed to get new memory for array.");
        }
    }
    return *vects;
}

int list(vect *vects, int total_vectors)
{
    // For each vector in the vector array, print it with formatting
    for (int i = 0; i < total_vectors; i++)
    {
        vect vector = *(vects+i);
        printvec(vector);
    }

    return 0;
}

int clear(vect *vects, int total_vectors)
{
    // Declare necessary character name for vector name component
    char empty_name[30] = "";
    
    // For each vector in the array, overwrite with a new vector with a blank name and filled with 0s
    for (int i = 0; i < total_vectors; i++)
    {
        vect vector = newvec(empty_name, 0, 0, 0);
        *(vects+i) = vector;
    }

    return 0;
}

int help()
{
    printf("Help and Usage Information:\n");
    printf("IMPORTANT: For all commands listed below, you must have a space between the values.\n");
    printf("For reference, 'varname' is the name of a vector and 'OP' is an operand such as +, -, *, ., and x\n");
    printf("To create a new vector or override an existing vector, type: varname = VALx VALy VALz\n");
    printf("There are ten vector maximum and, when you have reached the limit, the 10th will be continuously overriden for new vectors.\n");
    printf("To create a vector or modify from existing vectors, you may type: varname = varname OR: varname = varname1 OP varname2\n");
    printf("To see the outcome of an operation without saving, just type the operation like this: varname1 OP varname2\n");
    printf("Type 'list' to list all vectors, 'clear' to clear all vectors, 'help' to see this again, or 'quit' to exit the program.\n");
    return 0;
}