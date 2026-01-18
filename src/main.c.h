// base.h



typedef struct SaInfo {
    char* name;
    char* id;
    char* version;
} SaInfo;


typedef struct SaOption {
    bool version;
    bool help;
    char* mode;
    GOptionEntry* option;
    int optionN;
} SaOption;


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
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} SaGtkUriEntry;

typedef struct SaGtkUriSpin {
    GtkWidget* port;
} SaGtkUriSpin;

typedef struct SaGtkUri {
    SaGuriParse* parse;
    SaGtkUriEntry* entry;
    SaGtkUriSpin* spin;
    bool boolean;
} SaGtkUri;


typedef struct SaGtkMimeList {
    GList* http;
    GList* https;
    GList* all;
} SaGtkMimeList;

typedef struct SaGtkMimeBox {
    GtkWidget* list;
} SaGtkMimeBox;

typedef struct SaGtkMimeButton {
    GtkWidget* open;
} SaGtkMimeButton;

typedef struct SaGtkMime {
    SaGtkMimeList* list;
    SaGtkMimeBox* box;
    SaGtkMimeButton* button;
} SaGtkMime;


typedef struct SaGtkMenuAction {
    GSimpleAction* newwindow;
    GSimpleAction* about;
} SaGtkMenuAction;

typedef struct SaGtkMenuButton {
    GtkWidget* base;
} SaGtkMenuButton;

typedef struct SaGtkMenu {
    GMenu* base;
    SaGtkMenuAction* action;
    SaGtkMenuButton* button;
} SaGtkMenu;


typedef struct SaGtkWindow {
    GtkWidget* base;
    char* baseT;
    int baseH;
    int baseW;
} SaGtkWindow;

typedef struct SaGtkOverlay {
    GtkWidget* base;
} SaGtkOverlay;

typedef struct SaGtkHeaderbar {
    GtkWidget* base;
} SaGtkHeaderbar;

typedef struct SaGtkControl {
    GtkWidget* base;
} SaGtkControl;

typedef struct SaGtkPaned {
    GtkWidget* base;
    double baseR;
    GtkWidget* baseLeft;
    double baseLeftR;
    GtkWidget* baseRight;
    double baseRightR;
} SaGtkPaned;

typedef struct SaGtkGrid {
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

typedef struct SaGtkBase {
    GtkApplication* application;
    SaGtkWindow* window;
    SaGtkOverlay* overlay;
    SaGtkHeaderbar* headerbar;
    SaGtkControl* control;
    SaGtkPaned* paned;
    SaGtkGrid* grid;
    SaGtkScroll* scroll;
    SaInfo* Info;
    SaOption* Option;
    SaGtkMenu* GtkMenu;
    SaGtkUri* GtkUri;
    SaGtkMime* GtkMime;
} SaGtkBase;


typedef struct SaMap {
    GtkApplication* application;
    SaInfo* Info;
    SaOption* Option;
    SaGtkBase* GtkBase;
} SaMap;
