/* STUDENT COPY
 * printf() Debugging Lab
 *
 * Requirments:
 * -GCC
 * -CMake
 * -Make
 * -Cmocka library
 *
 * Instructions:
 * -Using printf(), debug this lab to determine why the test cases are failing.
 * -Repair the code.
 * -You may debug/view any portion of the project.
 * -If you are not using cLion:
 *  -In the same dir: run:       cmake . && cmake --build .
 *  -The output file will be the executable
 *  -You may also use GCC and link the Cmocka library via terminal
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool xo (const char* str)
{
    int len = strlen(str);
    int x = 0;
    int o = 0;

    for (; len > 0; len--) 
    {
        if (str[len] == 'x')
        {
            x++;
        }else if (str[len] == 'o')
        {
            o++;
        }
    }

    if (x == o)
    {
        return true;
    }
    return false;
}