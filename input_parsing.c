/**
* @file: input_parsing.c
* @brief Defining functions to aid in parsing user input from main
* 
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Author: Alexander Kruschka
* Date: 10/21/2025
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_number(char string[30])
{
    // Declaring variable to be used
    bool is_num;

    // If the string is 0 or can be converted into a float, then it is a number
    if (!strcmp(string, "0"))
    {
        is_num = true;
    }
    else if (atof(string) != 0)
    {
        is_num = true;
    }
    else
    {
        is_num = false;
    }

    // Return result of boolean
    return is_num;
}