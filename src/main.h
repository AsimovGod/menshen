#include <stdio.h>




typedef struct {
    GtkWidget* main;
    char* Tmain;
    int Hmain;
    int Wmain;
} TgGtkWindow;

typedef struct {
    GtkWidget* main;
} TgGtkHeaderbar;

typedef struct {
    GtkWidget* main;
} TgGtkControl;

typedef struct {
    GtkWidget* main;
    double Rmain;
    GtkWidget* mainLeft;
    double RmainLeft;
    GtkWidget* mainRight;
    double RmainRight;
} TgGtkPaned;

typedef struct {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
} TgGtkGrid;

typedef struct {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
} TgGtkScroll;

typedef struct {
    TgGtkWindow* window;
    TgGtkHeaderbar* headerbar;
    TgGtkControl* control;
    TgGtkPaned* paned;
    TgGtkGrid* grid;
    TgGtkScroll* scroll;
} TgGtkLayout;


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
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} TgGtkUriEntry;

typedef struct {
    GtkWidget* port;
} TgGtkUriSpin;

typedef struct {
    TgGuriParse* parse;
    TgGtkUriEntry* entry;
    TgGtkUriSpin* spin;
} TgGtkUri;

