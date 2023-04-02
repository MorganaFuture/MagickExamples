#include "InputDegrees.h"

std::string InputDegrees::run()
{
    gtk_init(NULL, NULL);

    GtkWidget *dialog = gtk_dialog_new_with_buttons(m_title.c_str(), GTK_WINDOW(m_parent),
                                                    static_cast<GtkDialogFlags>(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT), "_OK", GTK_RESPONSE_ACCEPT, NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *label = gtk_label_new("Enter degrees:");

    GtkWidget *spinbutton = gtk_spin_button_new_with_range(0, 360, 1);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinbutton), TRUE);

    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), spinbutton);

    gtk_widget_show_all(dialog);

    std::string result;
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        result = std::to_string(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton)));
    }

    gtk_widget_destroy(dialog);
    gtk_main_quit();

    return result;
}