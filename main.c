/**
 * @file main.c
 * @brief Main program to run minivec program, taking user input, assigning vectors, and calling vector math functions
 * 
 * Course: CPE2600
 * Section: 111
 * Assignment: Lab 5
 * Name: Alexander Kruschka
 * Date: 10/07/2025
 * Note: Compile with gcc main.c vect.c -Wall -o minivec OR make
 * 
 * Algorithm:
 * - Initiate values and variables
 * - If called with -h, print help and end program
 * - While user has not indicated to quit:
 *  - Declare and reset variable values
 *  - Get user input and parse it into an array
 *  - If just on value and is the name of a vector, print that vector
 *  - If custom word command, perform the function
 *  - Otherwise, assume vector assignment or math
 *   - Parse user input depending on input structure with operators
 *   - Assign resultant each argument as a float assuming no overriding
 *   - Check if each operation and perform corresponding math if needed
 *   - Add vector to new or overriding position is '=' is invoked
 *   - Print the resultant
 * - End program when user enters 'quit'
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vect.h"
#define TOTAL_VECTORS 10

int main(int argc, char *argv[])
{
    // Declaring general variables and vector array
    static vect vects[TOTAL_VECTORS];
    bool quit = false;
    int vector_index = 0;

    // If invoked with -h, print help and exit program immediately
    if (argc > 1 && !strcmp(argv[1], "-h"))
    {
        printf("To run the program normally, run the executable without the '-h' flag.\n");
        help();
        quit = true;
    }

    while (!quit)
    {
        // Declaring variabes to be used within scope
        vect resultant;
        vect vector1;
        vect vector2;
        char operator[30];
        char input[100];
        char vector_name[30];
        char *args[6];
        char *token;
        char term1[30];
        char term2[30];
        int vect_1_index;
        int vect_2_index;

        // Printing prompt for each user input
        printf("minivec> ");

        // Get user input
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // If user input is empty, ignore jump to end and restart loop from beginning
        if (input[0] == '\0') {
            printf("Invalid input, please enter a command.");
            continue;
        }

        // Parse the input into an argument array for easy future access
        int i = 0;
        token = strtok(input, ", ");
        while (token != NULL)
        {
            args[i] = token;
            token = strtok(NULL, ", ");
            i++;
        }

        // Exit program if user enters 'quit'
        if (!strcmp(args[0], "quit"))
        {
            printf("Exiting program.\n");
            quit = true;
        }
        
        // Display help when user enters 'help'
        if (!strcmp(args[0], "help"))
        {
            help();
        }
        
        // List all ten vectors when 'list' is entered
        if (!strcmp(args[0], "list"))
        {
            list(vects, TOTAL_VECTORS);
        }
        
        // Clear and reset all vectors when 'clear' is entered as well as current vector index tracker in array
        if (!strcmp(args[0], "clear"))
        {
            printf("Clearing vectors.\n");
            clear(vects, TOTAL_VECTORS);
            vector_index = 0;
        }
        
        // Handle all other user commands involving vectors while not exiting program
        if (!quit && i > 1)
        {
            // Is the second term an '=' sign? If so, use a = b OP c, otherwise use a OP b
            if (!strcmp(args[1], "="))
            {
                // Gather equation data using the template: a = b OP c
                strcpy(vector_name, args[0]);
                strcpy(operator, args[3]);
                strcpy(term1, args[2]);
                strcpy(term2, args[4]);

                // Calculate the index of each vector b and c in the equation, if they exist
                vect_1_index = getvec(term1, vects, TOTAL_VECTORS);
                vect_2_index = getvec(term2, vects, TOTAL_VECTORS);

                // Error check for invalid vectors for b and c and an invalid operatorusing ASCII, if so, error
                if ((vect_1_index == -1 || vect_2_index == -1) && (int)operator[0] > 57)
                {
                    printf("Error, undeclared vectors or invalid operator included.\n");
                    continue;
                }

                // Error check for invalid vector assignment using a = x y z template and ASCII conversion
                if (((int)term1[0] > 57 || (int)term2[0] > 57) && ((int)operator[0] > 47 && (int)operator[0] < 58))
                {
                    printf("Error, invalid vector assignment, please use numbers.\n");
                    continue;
                }
            } else {
                // Gather equation data using the template: a OP b
                strcpy(vector_name, "Result");
                strcpy(operator, args[1]);
                strcpy(term1, args[0]);
                strcpy(term2, args[2]);

                // Calculate the index of each vector a and b in the equation, if they exist
                vect_1_index = getvec(term1, vects, TOTAL_VECTORS);
                vect_2_index = getvec(term2, vects, TOTAL_VECTORS);

                // Error checking for invalid input parameters around argument
                // Are both numbers?
                if (((int)term1[0] < 58 && (int)term2[0] < 58))
                {
                    printf("Error, invalid input, type 'help' for more info.\n");
                    continue;
                }

                // Error checking for valid input parameters around specific arguments
                if (!strcmp(operator, "*"))
                {
                    if ((vect_1_index == -1 && vect_2_index == -1) || ((int)term1[0] > 57 && (int)term2[0] > 57))
                    {
                        printf("Error, invalid input, type 'help' for more info.\n");
                        continue;
                    }
                } else if (vect_1_index == -1 || vect_2_index == -1) {
                    printf("Error, invalid input, type 'help' for more info.\n");
                    continue;
                }
            }

            // Final error checking for invalid operator
            if ((int)operator[0] > 57 && (int)operator[0] != 120)
            {
                printf("Invalid operator entered, type 'help' for info.\n");
                continue;
            }
            
            // Get the vectors to be used in calculations from the vector array
            vector1 = vects[vect_1_index];
            vector2 = vects[vect_2_index];

            // Create a new vector that will not be overriden and added to array if no operand is detected
            // using the template of a = x y z
            resultant = newvec(vector_name, atof(args[2]), atof(args[3]), atof(args[4]));

            // If operand is addition, carry out function and overwrite resultant with result
            if (!strcmp(operator, "+"))
            {
                resultant = addvec(vector_name, vector1, vector2);
            }
            
            // If operand is subtraction, carry out function and overwrite resultant with result
            if (!strcmp(operator, "-"))
            {
                resultant = subvec(vector_name, vector1, vector2);
            }
            
            // If operand is scalar multiplication, carry out function and overwrite resultant with result
            if (!strcmp(operator, "*"))
            {
                // If the first vector index is -1, then it doesn't exist and must be the scalar. Otherwise, flip it
                if (vect_1_index == -1)
                {
                    resultant = scalarmult(vector_name, vector2, atof(term1));
                } else if (vect_2_index == -1) {
                    resultant = scalarmult(vector_name, vector1, atof(term2));
                }     
            }
            
            // If operand is dot product, carry out function and overwrite resultant with result
            if (!strcmp(operator, "."))
            {
                resultant = dotvec(vector_name, vector1, vector2);
            }
            
            // If operand is cross multiplication, carry out function and overwrite resultant with result
            if (!strcmp(operator, "x"))
            {
                resultant = crossvec(vector_name, vector1, vector2);
            }

            // If the vector name isn't 'Result', then it is an assignment to be added to array, otherwise skip
            if (strcmp(vector_name, "Result"))
            {
                // Declare and calculate index of potentially already existing vector
                int existing_index = getvec(vector_name, vects, TOTAL_VECTORS);

                // If it already exists, overwrite the current vector of the same name with new numbers,
                // otherwise add into a new index value of the array and increment index tracker
                if (existing_index != -1)
                {
                    vects[existing_index] = resultant;
                }
                else
                {
                    vects[vector_index] = resultant;
                    
                    // If full, do not increment and overwrite the 10th vector with resultant
                    if (vector_index < TOTAL_VECTORS - 1)
                    {
                        vector_index++;
                    } else {
                        printf("Warning: Max vectors have been reached; writing over 10th vector.\n");
                    }
                }
            }

            // Print the vector with formatting into console as final product for user
            printvec(resultant);
        }
        // If user entered a single input and matches an existing vector name, then print that vector
        else if (getvec(args[0], vects, TOTAL_VECTORS) != -1)
        {
            printvec(vects[getvec(args[0], vects, TOTAL_VECTORS)]);
        }
    }
    return 0;
}