// main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "main.c.h"
#include "part_file.c.h"
#include "part_guri.c.h"
#include "part_uri_change.c.h"
#include "part_uri_clipboard.c.h"
#include "part_uri_widget.c.h"
#include "part_uri.c.h"
#include "part_mime_open.c.h"
#include "part_mime_list.c.h"
#include "part_mime.c.h"
#include "part_stack.c.h"
#include "part_menu.c.h"
#include "part_window.c.h"
#include "part_option.c.h"
#include "part_app.c.h"



    int
main(int DiArgs, char** TcArgs)
{
    SaMap* CsMap;
    SaInfo* CsInfo;
    SaOption* CsOption;
    int DiExit;

    CsMap = g_new0(SaMap, 1);
    CsInfo = FsInfoInit();
    CsOption = FsOptionInit();

    CsMap->Info = CsInfo;
    CsMap->Option = CsOption;

    DiExit = FdOptionGlib(CsMap, DiArgs, TcArgs);
    DiExit = FdGtkApp(CsMap, DiArgs, TcArgs);

    FvOptionFree(CsOption);
    if (CsInfo) g_free(CsInfo);
    if (CsMap) g_free(CsMap);

    return DiExit;
}
