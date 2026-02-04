// PartMenu.c.h




struct SaGtkMenu {
    // link
    SaGtkMenuAction* Action;
    // gio.h
    GMenu* base;
    // gtk.h widget button
    GtkWidget* button;
    GtkWidget* about;
};


struct SaGtkMenuAction {
    // gio.h
    GSimpleAction* newwindow;
    GSimpleAction* about;
};



    void
FvGtkMenu(SaMap* CsMap)
{
    // declaration
    SaGtkMenu* CsGtkMenu;

    // malloc
    CsGtkMenu = g_new0(SaGtkMenu, 1);
    CsGtkMenu->Action = g_new0(SaGtkMenuAction, 1);

    // gtk.h new
    CsGtkMenu->base = g_menu_new();
    CsGtkMenu->button = gtk_menu_button_new();
    CsGtkMenu->Action->newwindow = g_simple_action_new("newwindow", NULL);
    CsGtkMenu->Action->about = g_simple_action_new("about", NULL);

    // bequeath
    CsMap->GtkMenu = CsGtkMenu;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkMenu", CsGtkMenu, (GDestroyNotify)g_free);

    // gtk.h layout
    g_menu_append(CsGtkMenu->base, "New Window", "win.newwindow");
    g_menu_append(CsGtkMenu->base, "About", "win.about");
    g_action_map_add_action(G_ACTION_MAP(CsMap->GtkWindow->base),
            G_ACTION(CsGtkMenu->Action->newwindow));
    g_action_map_add_action(G_ACTION_MAP(CsMap->GtkWindow->base),
            G_ACTION(CsGtkMenu->Action->about));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(CsGtkMenu->button),
            G_MENU_MODEL(CsGtkMenu->base));
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsMap->GtkWindow->headerbar),
            CsGtkMenu->button);

    // gobject.h signal
    g_signal_connect(CsGtkMenu->Action->newwindow,
            "activate", G_CALLBACK(FvGtkMenuNewwindow), CsMap);
    g_signal_connect(CsGtkMenu->Action->about,
            "activate", G_CALLBACK(FvGtkMenuAbout), CsMap);

    // gtk.h property
    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(CsGtkMenu->button),
            "open-menu-symbolic");
}


    void
FvGtkMenuNewwindow(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaMap* CsMapOld;

    // inherit
    CsMapOld = PvUserdata;

    if (! CsMapOld) return;

    // malloc
    CsMap = g_new0(SaMap, 1);

    // branch inherit
    CsMap->Info = CsMapOld->Info;
    CsMap->Option = CsMapOld->Option;
    CsMap->application = CsMapOld->application;

    // PartWindow.c.h
    FvGtkWindow(CsMap, 0, NULL);
}


    void
FvGtkMenuAbout(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaGtkMenu* CsGtkMenu;
    GdkTexture* EgLogo;

    // inherit
    CsMap = PvUserdata;
    CsGtkMenu = CsMap->GtkMenu;

    // glib.h resource
    EgLogo = gdk_texture_new_from_resource(
            "/io/AsimovGod/menshen/icon/menshen.png");

    // gtk.h new
    CsGtkMenu->about = gtk_about_dialog_new();

    // gtk.h layout
    gtk_window_set_transient_for(GTK_WINDOW(CsGtkMenu->about),
            GTK_WINDOW(CsMap->GtkWindow->base));
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->name);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->comment);
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->license);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->website);
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->websiteL);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->version);
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            CsMap->Info->authors);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(CsGtkMenu->about),
            GDK_PAINTABLE(EgLogo));

    // gtk.h property
    gtk_window_set_modal(GTK_WINDOW(CsGtkMenu->about), TRUE);
    gtk_window_present(GTK_WINDOW(CsGtkMenu->about));
}
