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
    char* website;
    char* websiteL;
    const char* name;
    const char* id;
    const char* comment;
    const char* version;
    const char* authors[2];
    // gtk.h
    GtkLicense license;
};



    int
FiMain(int DiArgs, char** TcArgs)
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


    SaInfo*
FsInfoInit()
{
    // declaration
    SaInfo* CsInfo;
    JsonObject* EjObject;

    // malloc
    CsInfo = g_new0(SaInfo, 1);

    // glib.h resource
    g_resources_register(PartResource_get_resource());

    // PartDefault.c.h
    EjObject = FjInfoJson();

    // variable
    CsInfo->website = "https://github.com/AsimovGod/menshen";
    CsInfo->websiteL = "Source Code";

    CsInfo->authors[0] = "AsimovGod";
    CsInfo->authors[1] = NULL;

    CsInfo->license = GTK_LICENSE_GPL_3_0;

    // variable json-glib.h
    CsInfo->name = json_object_get_string_member(EjObject, "name");
    CsInfo->id = json_object_get_string_member(EjObject, "id");
    CsInfo->comment = json_object_get_string_member(EjObject, "comment");
    CsInfo->version = json_object_get_string_member(EjObject, "version");

    // return
    return CsInfo;
}


    JsonObject*
FjInfoJson()
{
    // declaration
    const char* TcData;
    size_t DsSize;
    GBytes* EgBytes;
    JsonParser* EjParser;
    JsonNode* EjNode;
    JsonObject* EjObject;

    // glib.h resource
    EgBytes = g_resources_lookup_data("/io/AsimovGod/menshen/info/Info.json",
            G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);

    TcData = g_bytes_get_data(EgBytes, &DsSize);

    // json-glib.h
    EjParser = json_parser_new();

    json_parser_load_from_data(EjParser, TcData, DsSize, NULL);

    EjNode = json_parser_get_root(EjParser);
    EjObject = json_node_get_object(EjNode);

    return EjObject;
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

