
#ifndef FILE_IO
#define FILE_IO

#include "vect.h"

vect* read_file(char file_name[100], vect *vects, int *num_vects);

int write_file(char file_name[100], vect *vects, int num_vects);

#endif