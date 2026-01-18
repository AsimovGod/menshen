// part_uri_clipboard.h



    void
FvGtkUriEntryCopy(GtkButton *EgButton, void* PvUserdata)
{
    GtkEntry* EgEntry;
    GdkClipboard* EgClipboard;
    const char* AcText;

    EgEntry = PvUserdata;
    AcText = gtk_editable_get_text(GTK_EDITABLE(EgEntry));

    if (! AcText) return;

    EgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(EgEntry));
    gdk_clipboard_set_text(EgClipboard, AcText);
}


    void
FvGtkUriEntryPasteReceived(GObject* EgObject, GAsyncResult* EgResult,
        void* PvUserdata)
{
    GtkEntry* EgEntry;
    GdkClipboard* EgClipboard;
    const GValue* EgValue;
    const char* AcText;

    EgEntry = GTK_ENTRY(PvUserdata);
    EgClipboard = GDK_CLIPBOARD(EgObject);
    EgValue = gdk_clipboard_read_value_finish(EgClipboard, EgResult, NULL);

    if (! EgValue) return;
    if (! G_VALUE_HOLDS_STRING(EgValue)) return;

    AcText = g_value_get_string(EgValue);

    if (! AcText) return;

    gtk_editable_set_text(GTK_EDITABLE(EgEntry), AcText);
}


    void
FvGtkUriEntryPaste(GtkButton *EgButton, void* PvUserdata)
{
    GtkEntry* EgEntry;
    GdkClipboard* EgClipboard;

    EgEntry = GTK_ENTRY(PvUserdata);
    EgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(EgEntry));

    if (! EgClipboard) return;

    gdk_clipboard_read_value_async(EgClipboard, G_TYPE_STRING,
            G_PRIORITY_DEFAULT, NULL, FvGtkUriEntryPasteReceived, EgEntry);
}

