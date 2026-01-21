// main_function.c.h



// main.c
int main(int DiArgs,
        char** TcArgs);


// part_option.c.h
SaOption* FsOptionInit();

int FdOptionGlib(SaMap* CsMap,
        int DiArgs,
        char** TcArgs);

int FdOptionGtk(GApplication* EgApplication,
        GApplicationCommandLine* EgCommandline,
        void* PvUserdata);

void FvOptionFree(void* PvFree);


// part_default.c.h
SaInfo* FsInfoInit();


// part_file.c.h
void FvFileRead(char* TcArgs);


// part_guri.c.h
SaGuriParse* FsGuriParse(const char* AcBuild);

char* FaGuriBuild(SaGuriParse* CsParse);

void FvUriPrint(int DiArgument,
        char** TcArgument);

void FvGuriFree(void* PvFree);


// part_instance.c.h
int FdGtkInstance(SaMap* CsMap,
        int DiArgs,
        char** TcArgs);


// part_window.c.h
void FvGtkWindow(SaMap* CsMap,
        int DiArgument,
        char** TcArgument);

void FvGtkWindowFree(void* PvFree);


// part_menu.c.h
void FvGtkMenu(SaMap* CsMap);

void FvGtkMenuNewwindow(GSimpleAction* EgSimpleaction,
        GVariant* EgVariant,
        void* PvUserdata);

void FvGtkMenuAbout(GSimpleAction* EgSimpleaction,
        GVariant* EgVariant,
        void* PvUserdata);


// part_tab.c.h
void FvGtkTab(SaMap* CsMap,
        char* AcUri);

void FvGtkTabSwitch(GtkWidget* EgButton,
        void* PvUserdata);

void FvGtkTabClose(GtkWidget* EgButton,
        void* PvUserdata);

void FvGtkTabFree(void* PvFree);


// part_uri.c.h
void FvGtkUri(SaMap* CsMap,
        char* AcUri);

void FvGtkUriWidget(SaMap* CsMap);

void FvGtkUriFree(void* PvFree);


// part_uri_widget.c.h
GtkWidget* FeGtkUriEntry(SaGtkUri* CsGtkUri,
        const char* AcType,
        GtkWidget* EgParent,
        int DiRow,
        char* AcLabel);

GtkWidget* FeGtkUriSpin(SaGtkUri* CsGtkUri,
        const char* AcType,
        GtkWidget* EgParent,
        int DiRow,
        char* AcLabel);

void FvGtkUriEntryClear(GtkEntry* EgEntry,
        GtkEntryIconPosition EgPosition,
        GdkEvent* EgEvent,
        void* PvUserdata);


// part_uri_change.c.h
void FvGtkUriEntryBuild(GtkEditable* EgEditable,
        void* PvUserdata);

void FvGtkUriEntryParse(GtkEditable* EgEditable,
        void* PvUserdata);

char* FaGtkUriEntryGet(GtkWidget* EgEntry);

void FvGtkUriEntrySet(GtkWidget* EgEntry,
        char* AcUriEntry);


// part_uri_clipboard.c.h
void FvGtkUriEntryCopy(GtkButton *EgButton,
        void* PvUserdata);

void FvGtkUriEntryPaste(GtkButton *EgButton,
        void* PvUserdata);

void FvGtkUriEntryPasteReceived(GObject* EgObject,
        GAsyncResult* EgResult,
        void* PvUserdata);


// part_mime.c.h
void FvGtkMime(SaMap* CsMap);

void FvGtkMimeFree(void* PvFree);


// part_mime_list.c.h
void FvGtkMimeList(SaMap* CsMap);

void FvGtkMimeListAdd(GtkListBox* EgListbox,
        GAppInfo* EgAppinfo);


// part_mime_open.c.h
void FvGtkMimeOpen(SaMap* CsMap);

void FvGtkMimeListOpen(GtkButton *EgBotton,
        void* PvUserdata);

