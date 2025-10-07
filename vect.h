/**
* @file: vect.h
* @brief Declaring functions to perform vector calculations as well as various other functions for table interfacing
* 
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Author: Alexander Kruschka
* Date: 10/06/2025
*/

#ifndef VECT_H
#define VECT_H

/**
 * @struct vect
 * @brief A structure for a 3D vector with a name and each axis
 */
typedef struct vect
{
    char name[30];
    float x;
    float y;
    float z;
} vect;

/**
 * @brief Creates a vector from the given components
 * @param name The name of the vector
 * @param x The x-value of the vector
 * @param y The y-value of the vector
 * @param z The z-value of the vector
 * @return The creaated vector in the struct of vect
 */
vect newvec(char name[30], float x, float y, float z);

/**
 * @brief Converts a decimal number into a hex string
 * @param name Name of the vector to search for
 * @param vects The array of vectors to search in
 * @param total_vectors The number of vectors to search through
 * @return The index of the vector in the array or -1 if not found
 */
int getvec(char name[30], vect vects[10], int total_vectors);

/**
 * @brief Prints the individual components of a given array
 * @param vector The vector to print
 * @return 0 if successful
 */
int printvec(vect vector);

/**
 * @brief Adds the components of two vectors together and returns the result
 * @param name Name of the vector to return
 * @param a The first vector to add
 * @param b The second vector to add
 * @return The resultant vector of the sum
 */
vect addvec(char name[30], vect a, vect b);

/**
 * @brief Subtracts the components of two vectors together and returns the result
 * @param name Name of the vector to return
 * @param a The first vector to subtract
 * @param b The second vector to subtract
 * @return The resultant vector of the difference
 */
vect subvec(char name[30], vect a, vect b);

/**
 * @brief Multiplies the components of a vector by a scalar and return the result
 * @param name Name of the vector to return
 * @param a The vector to multiply
 * @param scalar The factor to multiply each component by
 * @return The resultant vector of the scalar
 */
vect scalarmult(char name[30], vect a, double scalar);

/**
 * @brief Finds the dot product of two vectors and returns it in the x component of a new vector
 * @param name Name of the vector to return
 * @param a The first vector to put in dot equation
 * @param b The second vector to put in dot equation
 * @return The result of the operation in the x component
 */
vect dotvec(char name[30], vect a, vect b);

/**
 * @brief Finds the cross vector of two vectors and returns it as a new vector
 * @param name Name of the vector to return
 * @param a The first vector to put in cross vector equation
 * @param b The second vector to put in cross vector equation
 * @return The resultant vector of the cross
 */
vect crossvec(char name[30], vect a, vect b);

/**
 * @brief Prints out the array of vectors
 * @param vects The array of vectors to print
 * @param total_vectors The total number of vectors to print
 * @return 0 if successful
 */
int list(vect *vects, int total_vectors);

/**
 * @brief Clears all vectors in the array
 * @param vects The array of vectors to clear
 * @param total_vectors The total number of vectors to clear
 * @return 0 if successful
 */
int clear(vect *vects, int total_vectors);

/**
 * @brief Prints out the help information to console
 * @return 0 if successful
 */
int help();

#endif