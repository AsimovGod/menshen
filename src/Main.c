// Main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include <json-glib/json-glib.h>

#include "xml/PartResource.h"

#include "MainStruct.c.h"
#include "MainFunction.c.h"
#include "PartDefault.c.h"
#include "PartOption.c.h"
#include "PartInstance.c.h"
#include "PartFile.c.h"
#include "PartGuri.c.h"
#include "PartWindow.c.h"
#include "PartWindowStack.c.h"
#include "PartMenu.c.h"
#include "PartTab.c.h"
#include "PartTabStack.c.h"
#include "PartTabManage.c.h"
#include "PartUri.c.h"
#include "PartUriEdit.c.h"
#include "PartUriChange.c.h"
#include "PartUriClipboard.c.h"
#include "PartMime.c.h"
#include "PartMimeList.c.h"
#include "PartMimeOpen.c.h"



    int
main(int DiArgs, char** TcArgs)
{
    // declaration
    SaMap* CsMap;
    SaInfo* CsInfo;
    SaOption* CsOption;
    int DiExit;

    // malloc
    CsMap = g_new0(SaMap, 1);

    // variable
    CsInfo = FsInfoInit();
    CsOption = FsOptionInit();

    // bequeath
    CsMap->Info = CsInfo;
    CsMap->Option = CsOption;

    // PartOption.c.h
    DiExit = FdOptionGlib(CsMap, DiArgs, TcArgs);

    // PartInstance.c.h
    DiExit = FdGtkInstance(CsMap, DiArgs, TcArgs);

    // return
    return DiExit;
}
