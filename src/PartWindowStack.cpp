// PartWindowStack.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



struct SaGtkWindowStack {
    // gtk.h widget stack
    GtkWidget* base;
    // gtk.h widget scroll
    GtkWidget* scroll;
    GtkAdjustment* scrollAH;
    // gtk.h widget separator
    GtkWidget* hsep;
    GtkWidget* vsepLeft;
    GtkWidget* vsepRight;
    // gtk.h widget box
    GtkWidget* tabbar;
    // gtk.h widget button
    GtkWidget* newtab;
    GtkWidget* count;
    // declaration property
    int number;
    int counter;
};



    SaGtkWindowStack*
FsGtkWindowStack(SaMap* CsMap, SaGtkWindow* CsGtkWindow)
{
    // malloc
    CsGtkWindow->Stack = g_new0(SaGtkWindowStack, 1);

    // gtk.h new
    CsGtkWindow->Stack->base = gtk_stack_new();
    CsGtkWindow->Stack->scroll = gtk_scrolled_window_new();
    CsGtkWindow->Stack->hsep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkWindow->Stack->vsepLeft = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    CsGtkWindow->Stack->vsepRight = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    CsGtkWindow->Stack->tabbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    CsGtkWindow->Stack->newtab = gtk_button_new_from_icon_name("list-add");
    CsGtkWindow->Stack->count = gtk_button_new_with_label(NULL);

    // variable
    CsGtkWindow->Stack->scrollAH = gtk_scrolled_window_get_hadjustment(
            GTK_SCROLLED_WINDOW(CsGtkWindow->Stack->scroll));
    CsGtkWindow->Stack->number = 0;
    CsGtkWindow->Stack->counter = 0;

    // gtk.h layout
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->base,
            0, 0, 5, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->hsep,
            0, 1, 5, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->count,
            0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->vsepLeft,
            1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->scroll,
            2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->vsepRight,
            3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->newtab,
            4, 2, 1, 1);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkWindow->Stack->scroll), CsGtkWindow->Stack->tabbar);

    // gobject.h signal
    g_signal_connect(CsGtkWindow->Stack->count,
            "clicked", G_CALLBACK(FvGtkWindowStackScroll), CsMap);
    g_signal_connect(CsGtkWindow->Stack->newtab,
            "clicked", G_CALLBACK(FvGtkTabNew), CsMap);

    // gtk.h property
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkWindow->Stack->scroll),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    gtk_widget_set_hexpand(CsGtkWindow->Stack->tabbar, TRUE);
    gtk_widget_set_valign(CsGtkWindow->Stack->tabbar, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(CsGtkWindow->Stack->count, 8);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->count, 8);
    gtk_widget_set_margin_start(CsGtkWindow->Stack->tabbar, 12);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->tabbar, 12);
    gtk_widget_set_margin_top(CsGtkWindow->Stack->tabbar, 12);
    gtk_widget_set_margin_bottom(CsGtkWindow->Stack->tabbar, 12);
    gtk_widget_set_margin_start(CsGtkWindow->Stack->newtab, 12);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->newtab, 12);

    gtk_button_set_has_frame(GTK_BUTTON(CsGtkWindow->Stack->newtab), FALSE);
    gtk_button_set_has_frame(GTK_BUTTON(CsGtkWindow->Stack->count), FALSE);

    // return
    return CsGtkWindow->Stack;
}


    void
FvGtkWindowStackCount(SaMap* CsMap, int DiShift)
{
    // declaration
    SaGtkWindow* CsGtkWindow;

    // inherit
    CsGtkWindow = CsMap->GtkWindow;

    CsGtkWindow->Stack->counter = CsGtkWindow->Stack->counter + DiShift;

    // gtk.h property
    gtk_button_set_label(GTK_BUTTON(CsGtkWindow->Stack->count),
            g_strdup_printf("%d", CsGtkWindow->Stack->counter));
}


    void
FvGtkWindowStackScroll(GtkButton* EgButton, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;

    // inherit
    CsMap = PvUserdata;

    if (! CsMap) return;

    // gobject.h idle
    g_idle_add(FgGtkTabStackScroll, CsMap);
}

