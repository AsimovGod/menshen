// Main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include <json-glib/json-glib.h>

#include "PartResource.h"

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
    int DiExit;

    // PartDefault.c.h
    DiExit = FiMain(DiArgs, TcArgs);

    // return
    return DiExit;
}

