#include <stdio.h>
#include "include/colors.h"

const int run(int day)
{
    switch (day)
    {
    case 1:
        printf("Hello World");
        break;

    default:
        printf("Not yet implemented");
        return 1;
    }
    return 0;
}

const int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        
    }
    else
    {
        printf("%s\nAdvent of C\n\nUsage:\n  aoc [year] [day(s)]\n\n%s", BHRED, COLOR_RESET);
        return 1;
    };
    return 0;
}
