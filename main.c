/**
 * @file main.c
 * @brief Main program to run minivec program, taking user input, assigning vectors, and calling vector math functions
 * 
 * Course: CPE2600
 * Section: 111
 * Assignment: Lab 5
 * Name: Alexander Kruschka
 * Date: 10/07/2025
 * Note: Compile with gcc main.c vect.c input_parsing.c file_io.c -s -Wall -o minivec OR make
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
#include "input_parsing.h"
#include "file_io.h"

int main(int argc, char *argv[])
{
    // Declaring general variables and vector array
    vect *vects = (vect *)malloc(sizeof(vect));
    bool quit = false;
    int total_vects = 0;

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
            free(vects);
            quit = true;
            continue;
        }

        // Read file into vector array if user enters 'load'
        if (!strcmp(args[0], "load"))
        {
            if (args[1] != NULL)
            {
                vects = read_file(args[1], vects, &total_vects);
            }
            else
            {
                printf("Please enter a file name.");
                continue;
            }
        }
        
        // Display help when user enters 'help'
        if (!strcmp(args[0], "help"))
        {
            help();
        }
        
        // List all ten vectors when 'list' is entered
        if (!strcmp(args[0], "list"))
        {
            list(vects, total_vects);
        }
        
        // Clear and reset all vectors when 'clear' is entered as well as current vector index tracker in array
        if (!strcmp(args[0], "clear"))
        {
            printf("Clearing vectors.\n");
            clear(vects, total_vects);
            total_vects = 0;
        }
        
        // Handle all other user commands involving vectors while not exiting program
        if (!quit && i > 2)
        {
            // Is the second term an '=' sign? If so, use a = b OP c, otherwise use a OP b
            if (!strcmp(args[1], "="))
            {
                // Gather equation data using the template: a = b OP c
                strcpy(vector_name, args[0]);
                strcpy(term1, args[2]);
                strcpy(operator, args[3]);
                strcpy(term2, args[4]);

                // Calculate the index of each vector b and c in the equation, if they exist
                vect_1_index = getvec(term1, vects, total_vects);
                vect_2_index = getvec(term2, vects, total_vects);

                // Error check for invalid vectors for b and c and an invalid operator, if so, error
                if ((vect_1_index == -1 || vect_2_index == -1) && !is_number(operator))
                {
                    printf("Error, undeclared vectors or invalid operator included.\n");
                    continue;
                }

                // Error check for invalid vector assignment using a = x y z template
                if ((!is_number(term1) || !is_number(term2)) && is_number(operator))
                {
                    printf("Error, invalid vector assignment, please use numbers.\n");
                    continue;
                }
            } else {
                // Gather equation data using the template: a OP b
                strcpy(vector_name, "Result");
                strcpy(term1, args[0]);
                strcpy(operator, args[1]);
                strcpy(term2, args[2]);

                // Calculate the index of each vector a and b in the equation, if they exist
                vect_1_index = getvec(term1, vects, total_vects);
                vect_2_index = getvec(term2, vects, total_vects);

                // Error checking for invalid input parameters around argument
                if (is_number(term1) && is_number(term2))
                {
                    printf("Error, invalid input, type 'help' for more info.\n");
                    continue;
                }

                // Error checking for valid input parameters around specific arguments
                if (!strcmp(operator, "*"))
                {
                    if ((vect_1_index == -1 && vect_2_index == -1) || (!is_number(term1) && !is_number(term2)))
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
            
            // Get the vectors to be used in calculations from the vector array if present
            if (vect_1_index != -1)
            {
                vector1 = vects[vect_1_index];
            }
            if (vect_2_index != -1)
            {
                vector2 = vects[vect_2_index];
            }
            
            // Create a new vector that will not be overriden and added to array if no operand is detected
            // using the template of a = x y z
            resultant = newvec(vector_name, atof(args[2]), atof(args[3]), atof(args[4]));

            // If operand is addition, carry out function and overwrite resultant with result
            if (!strcmp(operator, "+"))
            {
                resultant = sumvec(vector_name, vector1, vector2);
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
                addvec(&vects, &total_vects, resultant);
                printf("%d", total_vects);
                /*
                // Declare and calculate index of potentially already existing vector
                int existing_index = getvec(vector_name, vects, total_vects);

                // If it already exists, overwrite the current vector of the same name with new numbers,
                // otherwise add into a new index value of the array and increment index tracker with new memory
                if (existing_index != -1)
                {
                    vects[existing_index] = resultant;
                }
                else
                {
                    total_vects++;
                    vects = addvec(vects, total_vects, resultant);
                }*/
            }

            // Print the vector with formatting into console as final product for user
            printvec(resultant);
        }
        // If user entered a single input and matches an existing vector name, then print that vector
        else if (getvec(args[0], vects, total_vects) != -1)
        {
            printvec(vects[getvec(args[0], vects, total_vects)]);
        }
    }
    return 0;
}