// PartDefault.c.h



struct SaMap {
    // link
    SaGtkMime* GtkMime;
    SaGtkUri* GtkUri;
    SaGtkTab* GtkTab;
    SaGtkMenu* GtkMenu;
    SaGtkWindow* GtkWindow;
    SaOption* Option;
    SaInfo* Info;
    // gio.h application
    GtkApplication* application;
};


struct SaInfo {
    // declaration
    char* name;
    char* id;
    char* comment;
    char* website;
    char* websiteL;
    char* version;
    const char* authors[2];
    // gtk.h
    GtkLicense license;
};



    SaInfo*
FsInfoInit()
{
    // declaration
    SaInfo* CsInfo;

    // malloc
    CsInfo = g_new0(SaInfo, 1);

    // variable
    CsInfo->name = "MenShen";
    CsInfo->id = "com.AsimovGod.menshen";
    CsInfo->comment = "MenShen";
    CsInfo->website = "https://github.com/AsimovGod/menshen";
    CsInfo->websiteL = "Source Code";
    CsInfo->version = "0.1.0";

    CsInfo->authors[0] = "AsimovGod";
    CsInfo->authors[1] = NULL;

    CsInfo->license = GTK_LICENSE_LGPL_2_1;

    // return
    return CsInfo;
}


    void
FvMapFree(void* PvFree)
{
    // declaration
    SaMap* CsMap;

    // inherit
    CsMap = PvFree;

    if (! CsMap) return;

    // free
    g_free(CsMap);
}


    void
FvInfoFree(void* PvFree)
{
    // declaration
    SaInfo* CsInfo;

    // inherit
    CsInfo = PvFree;

    if (! CsInfo) return;

    // free
    g_free(CsInfo);
}

