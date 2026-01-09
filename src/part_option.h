#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>




gboolean UgOptVersion = FALSE;
gboolean UgOptWindow = FALSE;

GOptionEntry UgOptionentry[] = {
    {"version", 'v',    0,  G_OPTION_ARG_NONE,      &UgOptVersion,
        "Version",  NULL},
    {"window",  'w',    0,  G_OPTION_ARG_NONE,      &UgOptWindow,
        "Window",   NULL},
    {NULL}
};


    int
FiOption(GApplication *UgApplication,
        GApplicationCommandLine *UgCommandline)
{
    int ViOptArgs;
    char **AcOptArgs;

    AcOptArgs = g_application_command_line_get_arguments(UgCommandline,
            &ViOptArgs);

    if (UgOptVersion) {
        printf("Version");
        return EXIT_SUCCESS;
    }

    if (UgOptWindow && ViOptArgs > 1) {
        FvGtkActivate(GTK_APPLICATION(UgApplication),
                AcOptArgs);
    }

    return EXIT_SUCCESS;
}

