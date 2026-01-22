// Main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>


#include "MainStruct.c.h"
#include "MainFunction.c.h"
#include "PartDefault.c.h"
#include "PartOption.c.h"
#include "PartInstance.c.h"
#include "PartFile.c.h"
#include "PartGuri.c.h"
#include "PartWindow.c.h"
#include "PartMenu.c.h"
#include "PartTab.c.h"
#include "PartTabPage.c.h"
#include "PartUri.c.h"
#include "PartUriWidget.c.h"
#include "PartUriChange.c.h"
#include "PartUriClipboard.c.h"
#include "PartMime.c.h"
#include "PartMimeList.c.h"
#include "PartMimeOpen.c.h"



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
    DiExit = FdGtkInstance(CsMap, DiArgs, TcArgs);

    return DiExit;
}
