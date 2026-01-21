// part_default.c.h



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

