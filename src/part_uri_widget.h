// part_uri_widget.h



    void
FvGtkUriEntryClear(GtkEntry* UgEntry, GtkEntryIconPosition UgPosition,
        GdkEvent* UgEvent, void* PvUserdata)
{
    if (UgPosition == GTK_ENTRY_ICON_SECONDARY) {
        gtk_editable_delete_text(GTK_EDITABLE(UgEntry), 0, -1);
    }
}


    GtkWidget*
FgGtkUriEntry(SuGtkUri* PsGtkUri, const char* VcType, GtkWidget* UgParent,
        int ViRow, char* VcLabel)
{
    GtkWidget* UgEntry;
    GtkWidget* UgLabel;
    GtkWidget* UgEmpty;
    GtkWidget* UgButtonCopy;
    GtkWidget* UgButtonPaste;

    UgEntry = gtk_entry_new();
    UgLabel = gtk_label_new(VcLabel);
    UgEmpty = gtk_label_new(NULL);
    UgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");
    UgButtonPaste = gtk_button_new_from_icon_name("edit-paste-symbolic");

    gtk_grid_attach(GTK_GRID(UgParent), UgLabel,
            0, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEntry,
            1, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonPaste,
            2, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonCopy,
            3, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEmpty,
            4, ViRow, 1, 1);

    if (strcmp(VcType, "build") == 0)
    {
        g_signal_connect(UgEntry,
                "changed", G_CALLBACK(FvGtkUriEntryParse), PsGtkUri);
    }
    else if (strcmp(VcType, "parse") == 0)
    {
        g_signal_connect(UgEntry,
                "changed", G_CALLBACK(FvGtkUriEntryBuild), PsGtkUri);
    }

    g_signal_connect(UgEntry,
            "icon-press", G_CALLBACK(FvGtkUriEntryClear), NULL);
    g_signal_connect(UgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), UgEntry);
    g_signal_connect(UgButtonPaste,
            "clicked", G_CALLBACK(FvGtkUriEntryPaste), UgEntry);

    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(UgEntry),
            GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

    gtk_widget_set_size_request(UgLabel, 96, -1);
    gtk_widget_set_size_request(UgEmpty, 16, -1);

    gtk_widget_set_halign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(UgEntry, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UgEntry, GTK_ALIGN_FILL);

    gtk_widget_set_vexpand(UgEntry, TRUE);
    gtk_widget_set_hexpand(UgEntry, TRUE);
    gtk_label_set_xalign(GTK_LABEL(UgLabel), 0.5);

    gtk_widget_set_tooltip_text(UgButtonCopy, "Copy");
    gtk_widget_set_tooltip_text(UgButtonPaste, "Paste");

    return UgEntry;
}


    GtkWidget*
FgGtkUriSpin(SuGtkUri* PsGtkUri, const char* VcType, GtkWidget* UgParent,
        int ViRow, char* VcLabel)
{
    GtkWidget* UgEntry;
    GtkWidget* UgLabel;
    GtkWidget* UgEmpty;
    GtkWidget* UgButtonCopy;

    UgEntry = gtk_spin_button_new_with_range(-1, 65535, 1);
    UgLabel = gtk_label_new(VcLabel);
    UgEmpty = gtk_label_new(NULL);
    UgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");

    gtk_grid_attach(GTK_GRID(UgParent), UgLabel,
            0, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEntry,
            1, ViRow, 2, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonCopy,
            3, ViRow, 1, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEmpty,
            4, ViRow, 1, 1);

    g_signal_connect(UgEntry,
            "value-changed", G_CALLBACK(FvGtkUriEntryBuild), PsGtkUri);
    g_signal_connect(UgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), UgEntry);

    gtk_widget_set_size_request(UgLabel, 96, -1);
    gtk_widget_set_size_request(UgEmpty, 16, -1);

    gtk_widget_set_halign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(UgEntry, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UgEntry, GTK_ALIGN_FILL);

    gtk_widget_set_vexpand(UgEntry, TRUE);
    gtk_widget_set_hexpand(UgEntry, TRUE);
    gtk_label_set_xalign(GTK_LABEL(UgLabel), 0.5);

    gtk_widget_set_tooltip_text(UgButtonCopy, "Copy");

    return UgEntry;
}

