// PartDefault.c.h



struct SaMap {
    SaGtkMime* GtkMime;
    SaGtkUri* GtkUri;
    SaGtkTab* GtkTab;
    SaGtkMenu* GtkMenu;
    SaGtkWindow* GtkWindow;
    SaOption* Option;
    SaInfo* Info;
    GtkApplication* application;
};


struct SaInfo {
    char* name;
    char* id;
    char* version;
};



    SaInfo*
FsInfoInit()
{
    SaInfo* CsInfo;

    CsInfo = g_new0(SaInfo, 1);

    CsInfo->name = "MenShen";
    CsInfo->id = "com.AsimovGod.menshen";
    CsInfo->version = "0.1.0";

    return CsInfo;
}


    void
FvMapFree(void* PvFree)
{
    SaMap* CsMap;

    CsMap = PvFree;

    if (CsMap) return;

    g_free(CsMap);
}


    void
FvInfoFree(void* PvFree)
{
    SaInfo* CsInfo;

    CsInfo = PvFree;

    if (CsInfo) return;

    g_free(CsInfo);
}

