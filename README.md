# Minivec (Vector Lab) 

A small CLI based program meant for working with three dimensional vectors in a similar method to MATLAB.
  
## Description
  
Minivec is primarily meant to manipulate 3D vectors and can both input and output arrays into a file for storage. You can manually enter vectors into the program to be stored, then using the given commands (see: Supported Commands) modify and change them using constant and other vectors. Vectors with the same name will be overridden if a new vector with the same name is added.

Minivec used dynamic memory allocation of the vector array to ensure that the vector array can be as large as needed. Malloc is used to first initialize, then realloc is used to expand it. If memory isn't acquired properly, it will fallback to last vector array without update.

## Getting Started

### Installing
  
* Clone the repo into a chosen directory

* Compile with 'make' or manually with 'gcc main.c vect.c input_parsing.c file_io.c -s -Wall -o minivec'
  
### Executing program

* To just see help, run by typing './minivec -h'

* For normal operation, type './minivec' in a command window

* Add a vector manually or through file input using commands

* Use commands to manipulate vectors

## Supported Commands

Input:

 - Add or override existing vector: 'name = x y z'

Math: 

> Note: all below operations can be saved to a vector by typing '(vector name here) = ...' and a, b are vector names.
> Spaces are required.

 - Sum: 'a + b'
 - Difference: 'a - b'
 - Scalar: 'a * num' OR 'num * a'
 - Dot Product: 'a . b'
 - Cross Product: 'a x b'

Others:

> For file loading and saving, only the filename is required, not the extension

 - List all current vectors: 'list'
 - Print help and list of commands: 'help'
 - Clear all current vectors: 'clear'
 - Load a list of vectors from a file: 'load [filename]'
 - Save all current vectors to a file: 'save [filename]'
 - Quit program: 'quit'

## Authors

Alexander Kruschka [@kruschkaa]

## Version History

* 2.0
    * Dynamic memory for vector array
    * File reading and writing support
    * Various bug fixes and optimizations
* 1.0
    * Initial Release