// PartMime.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



struct SaGtkMime {
    // link
    SaGtkMimeList* List;
    SaGtkMimeButton* Button;
    // gtk.h widget listbox
    GtkWidget* frame;
    GtkWidget* listbox;
    GtkGesture* listboxC;
};



    void
FvGtkMime(SaMap* CsMap)
{
    // declaration
    SaGtkTab* CsGtkTab;
    SaGtkMime* CsGtkMime;

    // inherit
    CsGtkTab = CsMap->GtkTab;

    // malloc
    CsGtkMime = g_new0(SaGtkMime, 1);

    // gtk.h new
    CsGtkMime->frame = gtk_frame_new(NULL);
    CsGtkMime->listbox = gtk_list_box_new();
    CsGtkMime->listboxC = gtk_gesture_click_new();
    CsGtkTab->Scroll->mimeList = gtk_scrolled_window_new();
    CsGtkTab->Scroll->mimeOpen = gtk_scrolled_window_new();
    CsGtkTab->Grid->mimeList = gtk_grid_new();
    CsGtkTab->Grid->mimeOpen = gtk_grid_new();

    // bequeath
    CsGtkTab->GtkMime = CsGtkMime;
    CsMap->GtkMime = CsGtkMime;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkMime", CsGtkMime, (GDestroyNotify)FvGtkMimeFree);

    // gtk.h layout
    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->baseRight),
            CsGtkTab->Scroll->mimeList);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->baseRight),
            CsGtkTab->Scroll->mimeOpen);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeList), CsGtkTab->Grid->mimeList);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeOpen), CsGtkTab->Grid->mimeOpen);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->mimeList),
            CsGtkMime->frame, 0, 0, 1, 1);
    gtk_frame_set_child(GTK_FRAME(CsGtkMime->frame),
            CsGtkMime->listbox);
    gtk_widget_add_controller(CsGtkMime->listbox,
            GTK_EVENT_CONTROLLER(CsGtkMime->listboxC));

    // gobject.h signal
    g_signal_connect(CsGtkMime->listboxC,
            "pressed", G_CALLBACK(FvGtkMimeListPress), CsGtkMime);

    // gtk.h property
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeList),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeOpen),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_start(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_end(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_start(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_end(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->mimeOpen, 16);

    gtk_widget_set_vexpand(CsGtkTab->Grid->mimeList, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->mimeList, TRUE);
    gtk_widget_set_vexpand(CsGtkTab->Grid->mimeOpen, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->mimeOpen, TRUE);

    gtk_widget_set_valign(CsGtkTab->Grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkTab->Grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkTab->Grid->mimeOpen, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkTab->Grid->mimeOpen, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeList), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeList), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeOpen), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeOpen), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->mimeList), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->mimeList), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->mimeOpen), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->mimeOpen), 4);

    // PartMimeList.cpp
    FvGtkMimeList(CsMap);

    // PartMimeOpen.cpp
    FvGtkMimeOpen(CsMap);
}


    void
FvGtkMimeFree(void* PvFree)
{
    // declaration
    SaGtkMime* CsGtkMime;

    // inherit
    CsGtkMime = PvFree;

    if (! CsGtkMime) return;

    // free
    g_free(CsGtkMime->List);
    g_free(CsGtkMime->Button);
    g_free(CsGtkMime);
}

