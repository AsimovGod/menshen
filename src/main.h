// main.h



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


typedef struct SuGtkWindow {
    GtkWidget* main;
    char* mainT;
    int mainH;
    int mainW;
} SuGtkWindow;

typedef struct SuGtkHeaderbar {
    GtkWidget* main;
} SuGtkHeaderbar;

typedef struct SuGtkControl {
    GtkWidget* main;
} SuGtkControl;

typedef struct SuGtkPaned {
    GtkWidget* main;
    double mainR;
    GtkWidget* mainLeft;
    double mainLeftR;
    GtkWidget* mainRight;
    double mainRightR;
} SuGtkPaned;

typedef struct SuGtkGrid {
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
    SuGtkWindow* window;
    SuGtkHeaderbar* headerbar;
    SuGtkControl* control;
    SuGtkPaned* paned;
    SuGtkGrid* grid;
    SuGtkScroll* scroll;
    SuGtkUri* gtkUri;
    SuGtkMime* gtkMime;
} SuGtkBase;

