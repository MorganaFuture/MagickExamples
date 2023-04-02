#include "InputSize.h"

#include <iostream>

namespace
{
    void on_insert_text(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data);
}

std::string InputSize::run()
{
    gtk_init(NULL, NULL);

    // Create a new dialog
    GtkWidget *dialog = gtk_dialog_new_with_buttons(m_title.c_str(), GTK_WINDOW(m_parent),
                                                    static_cast<GtkDialogFlags>(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT), "_OK", GTK_RESPONSE_ACCEPT, NULL);

    // Create content area
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create labels and entry fields
    GtkWidget *width_label = gtk_label_new("Width:");
    GtkWidget *width_entry = gtk_entry_new();
    GtkWidget *height_label = gtk_label_new("Height:");
    GtkWidget *height_entry = gtk_entry_new();

    // Add labels and entry fields to content area
    gtk_container_add(GTK_CONTAINER(content_area), width_label);
    gtk_container_add(GTK_CONTAINER(content_area), width_entry);
    gtk_container_add(GTK_CONTAINER(content_area), height_label);
    gtk_container_add(GTK_CONTAINER(content_area), height_entry);

    // Connect signal handlers to validate input
    g_signal_connect(G_OBJECT(width_entry), "insert_text", G_CALLBACK(on_insert_text), NULL);
    g_signal_connect(G_OBJECT(height_entry), "insert_text", G_CALLBACK(on_insert_text), NULL);

    // Show dialog and run main loop
    gtk_widget_show_all(dialog);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        // Get entered values and save to m_value
        const gchar *width_str = gtk_entry_get_text(GTK_ENTRY(width_entry));
        const gchar *height_str = gtk_entry_get_text(GTK_ENTRY(height_entry));
        m_value = std::string(width_str) + "x" + std::string(height_str);
    }

    // Destroy dialog and quit main loop
    gtk_widget_destroy(dialog);
    gtk_main_quit();

    return m_value;
}

namespace
{
    // Signal handler to validate input text
    void on_insert_text(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data)
    {
        for (int i = 0; i < length; i++)
        {
            // Check if character is a digit
            if (!g_ascii_isdigit(text[i]))
            {
                // If not a digit, cancel the insertion of the text
                g_signal_stop_emission_by_name(G_OBJECT(editable), "insert_text");
                return;
            }
        }
    }
}