
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_number(char string[30])
{
    bool is_num;

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

    return is_num;
}