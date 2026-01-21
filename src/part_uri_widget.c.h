// part_uri_widget.c.h



    GtkWidget*
FeGtkUriEntry(SaGtkUri* CsGtkUri, const char* AcType, GtkWidget* EgParent,
        int DiRow, char* AcLabel)
{
    GtkWidget* EgEntry;
    GtkWidget* EgLabel;
    GtkWidget* EgEmpty;
    GtkWidget* EgButtonCopy;
    GtkWidget* EgButtonPaste;

    EgEntry = gtk_entry_new();
    EgLabel = gtk_label_new(AcLabel);
    EgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");
    EgButtonPaste = gtk_button_new_from_icon_name("edit-paste-symbolic");

    gtk_grid_attach(GTK_GRID(EgParent), EgLabel,
            0, DiRow, 1, 1);
    gtk_grid_attach(GTK_GRID(EgParent), EgEntry,
            1, DiRow, 1, 1);
    gtk_grid_attach(GTK_GRID(EgParent), EgButtonPaste,
            2, DiRow, 1, 1);
    gtk_grid_attach(GTK_GRID(EgParent), EgButtonCopy,
            3, DiRow, 1, 1);

    if (strcmp(AcType, "build") == 0)
    {
        g_signal_connect(EgEntry,
                "changed", G_CALLBACK(FvGtkUriEntryParse), CsGtkUri);
    }
    else if (strcmp(AcType, "parse") == 0)
    {
        g_signal_connect(EgEntry,
                "changed", G_CALLBACK(FvGtkUriEntryBuild), CsGtkUri);
    }

    g_signal_connect(EgEntry,
            "icon-press", G_CALLBACK(FvGtkUriEntryClear), NULL);
    g_signal_connect(EgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), EgEntry);
    g_signal_connect(EgButtonPaste,
            "clicked", G_CALLBACK(FvGtkUriEntryPaste), EgEntry);

    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(EgEntry),
            GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

    gtk_widget_set_size_request(EgLabel, 96, -1);

    gtk_widget_set_halign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(EgEntry, GTK_ALIGN_FILL);
    gtk_widget_set_halign(EgEntry, GTK_ALIGN_FILL);

    gtk_widget_set_vexpand(EgEntry, TRUE);
    gtk_widget_set_hexpand(EgEntry, TRUE);
    gtk_label_set_xalign(GTK_LABEL(EgLabel), 0.5);

    gtk_widget_set_tooltip_text(EgButtonCopy, "Copy");
    gtk_widget_set_tooltip_text(EgButtonPaste, "Paste");

    return EgEntry;
}


    GtkWidget*
FeGtkUriSpin(SaGtkUri* CsGtkUri, const char* AcType, GtkWidget* EgParent,
        int DiRow, char* AcLabel)
{
    GtkWidget* EgEntry;
    GtkWidget* EgLabel;
    GtkWidget* EgEmpty;
    GtkWidget* EgButtonCopy;

    EgEntry = gtk_spin_button_new_with_range(-1, 65535, 1);
    EgLabel = gtk_label_new(AcLabel);
    EgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");

    gtk_grid_attach(GTK_GRID(EgParent), EgLabel,
            0, DiRow, 1, 1);
    gtk_grid_attach(GTK_GRID(EgParent), EgEntry,
            1, DiRow, 2, 1);
    gtk_grid_attach(GTK_GRID(EgParent), EgButtonCopy,
            3, DiRow, 1, 1);

    g_signal_connect(EgEntry,
            "value-changed", G_CALLBACK(FvGtkUriEntryBuild), CsGtkUri);
    g_signal_connect(EgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), EgEntry);

    gtk_widget_set_size_request(EgLabel, 96, -1);
    gtk_widget_set_size_request(EgEmpty, 16, -1);

    gtk_widget_set_halign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(EgEntry, GTK_ALIGN_FILL);
    gtk_widget_set_halign(EgEntry, GTK_ALIGN_FILL);

    gtk_widget_set_vexpand(EgEntry, TRUE);
    gtk_widget_set_hexpand(EgEntry, TRUE);
    gtk_label_set_xalign(GTK_LABEL(EgLabel), 0.5);

    gtk_widget_set_tooltip_text(EgButtonCopy, "Copy");

    return EgEntry;
}


    void
FvGtkUriEntryClear(GtkEntry* EgEntry, GtkEntryIconPosition EgPosition,
        GdkEvent* EgEvent, void* PvUserdata)
{
    if (EgPosition == GTK_ENTRY_ICON_SECONDARY) {
        gtk_editable_delete_text(GTK_EDITABLE(EgEntry), 0, -1);
    }
}

