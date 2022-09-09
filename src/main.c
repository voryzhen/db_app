#include "cmd.h"
#include <stdio.h>

int main (int argc, char* argv[])
{
    char* filename;
    if (argc < 2)
    {
        printf("DB filename is not provided. Using db.dat.\n");
        filename = "db.dat";
    }
    else
    {
        filename = argv[1];
    }

    run_db_app(filename);
}
