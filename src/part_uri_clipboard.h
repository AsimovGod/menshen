#include <stdio.h>




    void
FvGtkUriEntryCopy(GtkButton *UgButton, void* PvUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;
    const char* VcText;

    UgEntry = PvUserdata;
    VcText = gtk_editable_get_text(GTK_EDITABLE(UgEntry));

    if (! VcText) return;

    UgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(UgEntry));
    gdk_clipboard_set_text(UgClipboard, VcText);
}


    void
FvGtkUriEntryPasteReceived(GObject* UgObject, GAsyncResult* UgResult,
        void* PvUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;
    const GValue* UgValue;
    const char* VcText;

    UgEntry = GTK_ENTRY(PvUserdata);
    UgClipboard = GDK_CLIPBOARD(UgObject);
    UgValue = gdk_clipboard_read_value_finish(UgClipboard, UgResult, NULL);

    if (! UgValue) return;
    if (! G_VALUE_HOLDS_STRING(UgValue)) return;

    VcText = g_value_get_string(UgValue);

    if (! VcText) return;

    gtk_editable_set_text(GTK_EDITABLE(UgEntry), VcText);
}


    void
FvGtkUriEntryPaste(GtkButton *UgButton, void* PvUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;

    UgEntry = GTK_ENTRY(PvUserdata);
    UgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(UgEntry));

    if (! UgClipboard) return;

    gdk_clipboard_read_value_async(UgClipboard, G_TYPE_STRING,
            G_PRIORITY_DEFAULT, NULL, FvGtkUriEntryPasteReceived, UgEntry);
}

