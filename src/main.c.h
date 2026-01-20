// base.h



typedef struct SaGuriParse {
    char* string;
    char* scheme;
    char* userinfo;
    char* host;
    int port;
    char* path;
    char* query;
    char* fragment;
    char* uri;
} SaGuriParse;

typedef struct SaGtkUriEntry {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} SaGtkUriEntry;

typedef struct SaGtkUri {
    SaGuriParse* Parse;
    SaGtkUriEntry* Entry;
    bool change;
} SaGtkUri;


typedef struct SaGtkMimeList {
    GList* http;
    GList* https;
    GList* all;
} SaGtkMimeList;

typedef struct SaGtkMimeButton {
    GtkWidget* open;
} SaGtkMimeButton;

typedef struct SaGtkMime {
    SaGtkMimeList* List;
    SaGtkMimeButton* Button;
    GtkWidget* listbox;
} SaGtkMime;


typedef struct SaGtkPaned {
    GtkWidget* base;
    double baseR;
    GtkWidget* baseLeft;
    double baseLeftR;
    GtkWidget* baseRight;
    double baseRightR;
} SaGtkPaned;

typedef struct SaGtkGrid {
    GtkWidget* tabTitle;
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
} SaGtkGrid;

typedef struct SaGtkScroll {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
} SaGtkScroll;

typedef struct SaGtkButton {
    GtkWidget* title;
    GtkWidget* close;
} SaGtkButton;

typedef struct SaGtkTab {
    SaGtkPaned* Paned;
    SaGtkGrid* Grid;
    SaGtkScroll* Scroll;
    SaGtkButton* Button;
    char* name;
} SaGtkTab;


typedef struct SaGtkMenuAction {
    GSimpleAction* newwindow;
    GSimpleAction* about;
} SaGtkMenuAction;

typedef struct SaGtkMenu {
    SaGtkMenuAction* Action;
    GMenu* base;
    GtkWidget* button;
    GtkAlertDialog* about;
} SaGtkMenu;


typedef struct SaGtkStack {
    GtkWidget* base;
    GtkWidget* tabbar;
    GtkWidget* button;
    int counter;
} SaGtkStack;

typedef struct SaGtkWindow {
    SaGtkStack* Stack;
    GtkWidget* base;
    char* baseT;
    int baseH;
    int baseW;
    GtkWidget* headerbar;
    GtkWidget* control;
} SaGtkWindow;


typedef struct SaInfo {
    char* name;
    char* id;
    char* version;
} SaInfo;


typedef struct SaOption {
    GOptionEntry* option;
    int optionN;
    bool version;
    bool help;
    char* mode;
} SaOption;


typedef struct SaMap {
    SaGtkMime* GtkMime;
    SaGtkUri* GtkUri;
    SaGtkTab* GtkTab;
    SaGtkMenu* GtkMenu;
    SaGtkWindow* GtkWindow;
    SaOption* Option;
    SaInfo* Info;
    GtkApplication* application;
} SaMap;
