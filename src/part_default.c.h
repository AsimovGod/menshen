// part_app.h



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

