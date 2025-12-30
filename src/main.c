#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "part_show.h"
#include "part_gtk.h"



    int
main(int ViArgs, char *AcArgs[])
{
    char *VcArg1;

    if (ViArgs < 2) {
        VcArg1 = "";
    }
    else {
        VcArg1 = AcArgs[1];
    }

    if (strncmp(VcArg1,
                "-v",
                sizeof(VcArg1)) == 0
            || strncmp(VcArg1,
                "--version",
                sizeof(VcArg1)) == 0)
    {
        FvShow("/usr/share/menshen/version");
    }
    else {
        FiGtk(ViArgs, AcArgs);
    }

    return EXIT_SUCCESS;
}
