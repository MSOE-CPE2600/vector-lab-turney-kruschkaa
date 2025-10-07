

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vect.h"

vect newvec(char name[30], float x, float y, float z)
{
    vect newVector;
    strcpy(newVector.name, name);
    newVector.x = x;
    newVector.y = y;
    newVector.z = z;
    return newVector;
}

int getvec(char name[30], vect vects[10], int total_vectors)
{
    int vectIndex = -1;
    for (int i = 0; i < total_vectors; i++)
    {
        if (!strcmp(name, vects[i].name))
        {
            vectIndex = i;
        }
    }
    return vectIndex;
}

int printvec(vect vector)
{
    printf("%10s:%10.3f,%10.3f,%10.3f\n", vector.name, vector.x, vector.y, vector.z);
    return 0;
}

vect addvec(char name[30], vect a, vect b)
{
    return newvec(name, a.x + b.x, a.y + b.y, a.z + b.z);
}

vect subvec(char name[30], vect a, vect b)
{
    return newvec(name, a.x - b.x, a.y - b.y, a.z - b.z);
}

vect scalarmult(char name[30], vect a, double scalar)
{
    return newvec(name, a.x * scalar, a.y * scalar, a.z * scalar);
}

vect dotvec(char name[30], vect a, vect b)
{
    
    return newvec(name, (a.x * b.x) + (a.y * b.y) + (a.z * b.z), 0, 0);
}

vect crossvec(char name[30], vect a, vect b)
{
    double new_x = (a.y * b.z) - (a.z * b.y);
    double new_y = (a.z * b.x) - (a.x * b.z);
    double new_z = (a.x * b.y) - (a.y * b.x);
    return newvec(name, new_x, new_y, new_z);
}

int list(vect *vects, int total_vectors)
{
    for (int i = 0; i < total_vectors; i++)
    {
        vect vector = *(vects+i);
        printvec(vector);
    }

    return 0;
}

int clear(vect *vects, int total_vectors)
{
    char empty_name[30] = "";
    
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
    printf("To create a vector or modify from existing vectors, you may type: varname = varname OR: varname = varname1 OP varname2\n");
    printf("To see the outcome of an operation without saving, just type the operation like this: varname1 OP varname2\n");
    printf("Type 'list' to list all vectors, 'clear' to clear all vectors, 'help' to see this again, or 'quit' to exit the program.\n");
    return 0;
}