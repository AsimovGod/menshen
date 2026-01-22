// Main_function.c.h



// Main.c
int main(int, char**);


// PartDefault.c.h
SaInfo* FsInfoInit();
void FvMapFree(void*);
void FvInfoFree(void*);


// PartOption.c.h
SaOption* FsOptionInit();
int FdOptionGlib(SaMap*, int, char**);
int FdOptionGtk(GApplication*, GApplicationCommandLine*, void*);
void FvOptionFree(void*);


// PartFile.c.h
void FvFileRead(char*);


// PartGuri.c.h
SaGuriParse* FsGuriParse(const char*);
char* FaGuriBuild(SaGuriParse*);
void FvUriPrint(int, char**);
void FvGuriFree(void*);


// PartInstance.c.h
int FdGtkInstance(SaMap*, int, char**);


// PartWindow.c.h
void FvGtkWindow(SaMap*, int, char**);
void FvGtkWindowFree(void*);


// PartMenu.c.h
void FvGtkMenu(SaMap*);
void FvGtkMenuNewwindow(GSimpleAction*, GVariant*, void*);
void FvGtkMenuAbout(GSimpleAction*, GVariant*, void*);


// PartTab.c.h
void FvGtkTab(SaMap*, char*);
void FvGtkTabFree(void*);


// PartTabPage.c.h
void FvGtkTabPage(SaMap*, char*);
void FvGtkTabNew(GtkWidget*, void*);
void FvGtkTabSwitch(GtkWidget*, void*);
void FvGtkTabRemove(GtkWidget*, void*);


// PartUri.c.h
void FvGtkUri(SaMap*, char*);
void FvGtkUriWidget(SaMap*);
void FvGtkUriFree(void*);


// PartUriWidget.c.h
GtkWidget* FeGtkUriEntry(SaGtkUri*, const char*, GtkWidget*, int, char*);
GtkWidget* FeGtkUriSpin(SaGtkUri*, const char*, GtkWidget*, int, char*);
void FvGtkUriEntryClear(GtkWidget*, GtkEntryIconPosition, GdkEvent*, void*);


// PartUriChange.c.h
void FvGtkUriEntryBuild(GtkEditable*, void*);
void FvGtkUriEntryParse(GtkEditable*, void*);
char* FaGtkUriEntryGet(GtkWidget*);
void FvGtkUriEntrySet(GtkWidget*, char*);


// PartUriClipboard.c.h
void FvGtkUriEntryCopy(GtkWidget*, void*);
void FvGtkUriEntryPaste(GtkWidget*, void*);
void FvGtkUriEntryPasteReceived(GObject*, GAsyncResult*, void*);


// PartMime.c.h
void FvGtkMime(SaMap*);
void FvGtkMimeFree(void*);


// PartMimeList.c.h
void FvGtkMimeList(SaMap*);
void FvGtkMimeListAdd(GtkListBox*, GAppInfo*, void*);


// PartMimeOpen.c.h
void FvGtkMimeOpen(SaMap*);
void FvGtkMimeListOpen(GtkWidget*, void*);

