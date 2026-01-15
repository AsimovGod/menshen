

typedef struct {
    char* string;
    char* scheme;
    char* userinfo;
    char* host;
    int port;
    char* path;
    char* query;
    char* fragment;
    char* uri;
} TgGuriParse;

typedef struct {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
    TgGuriParse* parse;
} TgGuriWidget;

typedef struct {
    GtkWidget* main;
    GtkWidget* mainUp;
    GtkWidget* mainDown;
} TgGtkPaned;

typedef struct {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
} TgGtkBox;

typedef struct {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
} TgGtkScroll;

typedef struct {
    GtkWidget* window;
    TgGtkPaned* paned;
    TgGtkBox* box;
    TgGtkScroll* scroll;
} TgGtkContainer;
