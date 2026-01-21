// main_function.c.h



// main.c
int main(int, char**);


// part_option.c.h
SaOption* FsOptionInit();
int FdOptionGlib(SaMap*, int, char**);
int FdOptionGtk(GApplication*, GApplicationCommandLine*, void*);
void FvOptionFree(void*);


// part_default.c.h
SaInfo* FsInfoInit();


// part_file.c.h
void FvFileRead(char*);


// part_guri.c.h
SaGuriParse* FsGuriParse(const char*);
char* FaGuriBuild(SaGuriParse*);
void FvUriPrint(int, char**);
void FvGuriFree(void*);


// part_instance.c.h
int FdGtkInstance(SaMap*, int, char**);


// part_window.c.h
void FvGtkWindow(SaMap*, int, char**);
void FvGtkWindowFree(void*);


// part_menu.c.h
void FvGtkMenu(SaMap*);
void FvGtkMenuNewwindow(GSimpleAction*, GVariant*, void*);
void FvGtkMenuAbout(GSimpleAction*, GVariant*, void*);


// part_tab.c.h
void FvGtkTab(SaMap*, char*);
void FvGtkTabSwitch(GtkWidget*, void*);
void FvGtkTabClose(GtkWidget*, void*);
void FvGtkTabFree(void*);


// part_uri.c.h
void FvGtkUri(SaMap*, char*);
void FvGtkUriWidget(SaMap*);
void FvGtkUriFree(void*);


// part_uri_widget.c.h
GtkWidget* FeGtkUriEntry(SaGtkUri*, const char*, GtkWidget*, int, char*);
GtkWidget* FeGtkUriSpin(SaGtkUri*, const char*, GtkWidget*, int, char*);
void FvGtkUriEntryClear(GtkWidget*, GtkEntryIconPosition, GdkEvent*, void*);


// part_uri_change.c.h
void FvGtkUriEntryBuild(GtkEditable*, void*);
void FvGtkUriEntryParse(GtkEditable*, void*);
char* FaGtkUriEntryGet(GtkWidget*);
void FvGtkUriEntrySet(GtkWidget*, char*);


// part_uri_clipboard.c.h
void FvGtkUriEntryCopy(GtkWidget*, void*);
void FvGtkUriEntryPaste(GtkWidget*, void*);
void FvGtkUriEntryPasteReceived(GObject*, GAsyncResult*, void*);


// part_mime.c.h
void FvGtkMime(SaMap*);
void FvGtkMimeFree(void*);


// part_mime_list.c.h
void FvGtkMimeList(SaMap*);
void FvGtkMimeListAdd(GtkListBox*, GAppInfo*);


// part_mime_open.c.h
void FvGtkMimeOpen(SaMap*);
void FvGtkMimeListOpen(GtkWidget*, void*);

