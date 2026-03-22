// MainFunction.hpp


// Main.cpp
int main(int, char**);


// PartDefault.cpp
SaInfo* FsInfoInit();
JsonObject* FjInfoJson();
int FiMain(int, char**);
void FvMapFree(void*);
void FvInfoFree(void*);


// PartOption.cpp
SaOption* FsOptionInit();
int FdOptionGlib(SaMap*, int, char**);
int FdOptionGtk(GApplication*, GApplicationCommandLine*, void*);
void FvOptionFree(void*);


// PartFile.cpp
void FvFileRead(char*);


// PartGuri.cpp
SaGuriParse* FsGuriParse(const char*);
char* FaGuriBuild(SaGuriParse*);
void FvUriPrint(int, char**);
void FvGuriFree(void*);


// PartInstance.cpp
int FdGtkInstance(SaMap*, int, char**);


// PartWindow.cpp
void FvGtkWindow(SaMap*, int, char**);
void FvGtkWindowFree(void*);


// PartWindowStack.cpp
SaGtkWindowStack* FsGtkWindowStack(SaMap*, SaGtkWindow*);
void FvGtkWindowStackCount(SaMap*, int);
void FvGtkWindowStackScroll(GtkButton*, void*);


// PartMenu.cpp
void FvGtkMenu(SaMap*);
void FvGtkMenuNewwindow(GSimpleAction*, GVariant*, void*);
void FvGtkMenuAbout(GSimpleAction*, GVariant*, void*);


// PartTab.cpp
void FvGtkTab(SaMap*, char*);
void FvGtkTabFree(void*);


// PartTabStack.cpp
SaGtkTabStack* FsGtkTabStack(SaMap*, SaGtkTab*);
gboolean FgGtkTabStackScroll(void*);


// PartTabManage.cpp
void FvGtkTabNew(GtkWidget*, void*);
void FvGtkTabSwitch(GtkWidget*, void*);
void FvGtkTabRemove(GtkWidget*, void*);


// PartUri.cpp
void FvGtkUri(SaMap*, char*);
void FvGtkUriWidget(SaMap*);
void FvGtkUriFree(void*);


// PartUriEdit.cpp
GtkWidget* FeGtkUriEntry(SaGtkUri*, const char*, GtkWidget*, int, char*);
GtkWidget* FeGtkUriSpin(SaGtkUri*, const char*, GtkWidget*, int, char*);
void FvGtkUriEntryClear(GtkWidget*, GtkEntryIconPosition, GdkEvent*, void*);


// PartUriChange.cpp
void FvGtkUriEntryBuild(GtkEditable*, void*);
void FvGtkUriEntryParse(GtkEditable*, void*);
char* FaGtkUriEntryGet(GtkWidget*);
void FvGtkUriEntrySet(GtkWidget*, char*);


// PartUriClipboard.cpp
void FvGtkUriEntryCopy(GtkWidget*, void*);
void FvGtkUriEntryPaste(GtkWidget*, void*);
void FvGtkUriEntryPasteReceived(GObject*, GAsyncResult*, void*);


// PartMime.cpp
void FvGtkMime(SaMap*);
void FvGtkMimeFree(void*);


// PartMimeList.cpp
void FvGtkMimeList(SaMap*);
void FvGtkMimeListAdd(GtkListBox*, GAppInfo*, void*);
void FvGtkMimeListPress(GtkGestureClick*, double, double, unsigned int, void*);


// PartMimeOpen.cpp
void FvGtkMimeOpen(SaMap*);
void FvGtkMimeListOpen(GtkWidget*, void*);

