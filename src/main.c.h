// base.h



typedef struct SuInfo {
    char* name;
    char* id;
    char* version;
} SuInfo;


typedef struct SuOption {
    bool version;
    bool help;
    char* mode;
    GOptionEntry* option;
    int optionN;
} SuOption;


typedef struct SuGuriParse {
    char* string;
    char* scheme;
    char* userinfo;
    char* host;
    int port;
    char* path;
    char* query;
    char* fragment;
    char* uri;
} SuGuriParse;

typedef struct SuGtkUriEntry {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} SuGtkUriEntry;

typedef struct SuGtkUriSpin {
    GtkWidget* port;
} SuGtkUriSpin;

typedef struct SuGtkUri {
    SuGuriParse* parse;
    SuGtkUriEntry* entry;
    SuGtkUriSpin* spin;
    bool boolean;
} SuGtkUri;


typedef struct SuGtkMimeList {
    GList* http;
    GList* https;
    GList* all;
} SuGtkMimeList;

typedef struct SuGtkMimeBox {
    GtkWidget* list;
} SuGtkMimeBox;

typedef struct SuGtkMimeButton {
    GtkWidget* open;
} SuGtkMimeButton;

typedef struct SuGtkMime {
    SuGtkMimeList* list;
    SuGtkMimeBox* box;
    SuGtkMimeButton* button;
} SuGtkMime;


typedef struct SuGtkMenuAction {
    GSimpleAction* newwindow;
    GSimpleAction* about;
} SuGtkMenuAction;

typedef struct SuGtkMenuButton {
    GtkWidget* base;
} SuGtkMenuButton;

typedef struct SuGtkMenu {
    GMenu* base;
    SuGtkMenuAction* action;
    SuGtkMenuButton* button;
} SuGtkMenu;


typedef struct SuGtkWindow {
    GtkWidget* base;
    char* baseT;
    int baseH;
    int baseW;
} SuGtkWindow;

typedef struct SuGtkOverlay {
    GtkWidget* base;
} SuGtkOverlay;

typedef struct SuGtkHeaderbar {
    GtkWidget* base;
} SuGtkHeaderbar;

typedef struct SuGtkControl {
    GtkWidget* base;
} SuGtkControl;

typedef struct SuGtkPaned {
    GtkWidget* base;
    double baseR;
    GtkWidget* baseLeft;
    double baseLeftR;
    GtkWidget* baseRight;
    double baseRightR;
} SuGtkPaned;

typedef struct SuGtkGrid {
    GtkWidget* about;
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
} SuGtkGrid;

typedef struct SuGtkScroll {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
} SuGtkScroll;

typedef struct SuGtkBase {
    GtkApplication* application;
    SuGtkWindow* window;
    SuGtkOverlay* overlay;
    SuGtkHeaderbar* headerbar;
    SuGtkControl* control;
    SuGtkPaned* paned;
    SuGtkGrid* grid;
    SuGtkScroll* scroll;
    SuInfo* Info;
    SuOption* Option;
    SuGtkMenu* GtkMenu;
    SuGtkUri* GtkUri;
    SuGtkMime* GtkMime;
} SuGtkBase;


typedef struct SuMap {
    GtkApplication* application;
    SuInfo* info;
    SuOption* option;
    SuGtkBase* gtkBase;
} SuMap;
