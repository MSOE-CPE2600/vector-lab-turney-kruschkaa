/**
* @file: file_io.h
* @brief Declaring functions to read and write vectors in csv files
* 
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Author: Alexander Kruschka
* Date: 10/21/2025
*/

#ifndef FILE_IO
#define FILE_IO

#include "vect.h"

/**
 * @brief Reads a file and returns a new array of vectors building off of the original
 * by replacing already present vectors or adding new vectors to the array
 * 
 * @param file_name The name of the file to read
 * @param vects The original vector array to add on overwrite
 * @param num_vects The pointer to the number of vectors currently in the array
 * @return The pointer of the newly creaated vector array
 */
vect* read_file(char file_name[100], vect *vects, int *num_vects);

/**
 * @brief Writes all of the current vectors in the program to a user specified file
 * @param file_name The name of the file to write to
 * @param vects The array of vectors to be written
 * @param num_vects The total number of vectors to be written
 * @return 0 if the file was successfully created and written to
 */
int write_file(char file_name[100], vect *vects, int num_vects);

#endif