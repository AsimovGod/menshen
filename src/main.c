// main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "main.h"
#include "part_file.h"
#include "part_guri.h"
#include "part_uri_change.h"
#include "part_uri_clipboard.h"
#include "part_uri_widget.h"
#include "part_uri.h"
#include "part_mime_open.h"
#include "part_mime_list.h"
#include "part_mime.h"
#include "part_window.h"
#include "part_option.h"
#include "part_app.h"



    int
main(int ViArgs, char** AcArgs)
{
    int ViExit;
    SuMap* PsMap;
    SuInfo* PsInfo;
    SuOption* PsOption;

    PsMap = g_new0(SuMap, 1);
    PsInfo = FsInfoInit();
    PsOption = FsOptionInit();
    PsMap->info = PsInfo;
    PsMap->option = PsOption;

    ViExit = FiOptionGlib(ViArgs, AcArgs, PsMap, PsInfo, PsOption);
    ViExit = FiGtkApp(ViArgs, AcArgs, PsMap, PsInfo, PsOption);

    FvInfoFree(PsInfo);
    FvOptionFree(PsOption);
    if (PsMap) g_free(PsMap);

    return ViExit;
}
