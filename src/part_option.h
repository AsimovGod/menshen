#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>




    TgOption*
FgOptionInit()
{
    int ViOption;
    TgOption* UtOption;

    ViOption = 0;
    UtOption = g_new0(TgOption, 1);
    UtOption->optionN = 3;
    UtOption->option = g_new0(GOptionEntry, UtOption->optionN +1);

    UtOption->version = FALSE;
    UtOption->option[ViOption].long_name = "version";
    UtOption->option[ViOption].short_name = 'v';
    UtOption->option[ViOption].arg = G_OPTION_ARG_NONE;
    UtOption->option[ViOption].arg_data = &UtOption->version;
    UtOption->option[ViOption].description = "Version";
    ViOption = ViOption + 1;

    UtOption->mode = NULL;
    UtOption->option[ViOption].long_name = "mode";
    UtOption->option[ViOption].short_name = 'm';
    UtOption->option[ViOption].arg = G_OPTION_ARG_STRING;
    UtOption->option[ViOption].arg_data = &UtOption->mode;
    UtOption->option[ViOption].description = "Mode";
    ViOption = ViOption + 1;

    return UtOption;
}


    void
FvOptionFree(void* PvFree)
{
    TgOption* UtOption;

    UtOption = PvFree;

    if (! UtOption) return;

    g_free(UtOption->mode);
    g_free(UtOption->option);
    g_free(UtOption);
}


    int
FiOptionGlib(int ViArgs, char** AcArgs, TgOption* UtOption)
{
    int ViLoop;
    int ViArgument;
    char** AcArgument;

    GOptionContext* UgOptioncontext;

    ViArgument = ViArgs;
    AcArgument = g_strdupv((char**)AcArgs);
    UgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(UgOptioncontext, FALSE);
    g_option_context_add_main_entries(UgOptioncontext, UtOption->option, NULL);
    g_option_context_parse(UgOptioncontext, &ViArgument, &AcArgument, NULL);

    if (UtOption->version) {
        printf("\n0.0.1\n");

        FvOptionFree(UtOption);
        exit(EXIT_SUCCESS);
    }

    if (UtOption->mode && g_strcmp0(UtOption->mode, "0") == 0)
    {
        for (ViLoop = 1; ViLoop < ViArgument; ViLoop++) {
            FvUriPrint(AcArgument[ViLoop]);
        }

        exit(EXIT_SUCCESS);
    }

    g_strfreev(AcArgument);

    return EXIT_SUCCESS;
}


    int
FiOptionGtk(GApplication* UgApplication,
        GApplicationCommandLine* UgCommandline,
        void* PvUserdata)
{
    int ViArgument;
    char** AcArgument;
    TgOption* UtOption;

    UtOption = PvUserdata;

    AcArgument = g_application_command_line_get_arguments(UgCommandline,
            &ViArgument);

    if (UtOption->mode && g_strcmp0(UtOption->mode, "1") == 0)
    {
        FvGtkActivate(GTK_APPLICATION(UgApplication), AcArgument);
    }

    return EXIT_SUCCESS;
}

