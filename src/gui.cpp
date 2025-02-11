#include "gui.h"
#include "pdf_processor.h"

// static void on_add_file(GtkWidget *widget, gpointer data) {
//     GtkWidget *dialog = gtk_file_chooser_dialog_new("Select PDF", NULL,
//         GTK_FILE_CHOOSER_ACTION_OPEN,
//         "_Cancel", GTK_RESPONSE_CANCEL,
//         "_Open", GTK_RESPONSE_ACCEPT,
//         NULL);

//     if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
//         char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
//         g_print("Selected file: %s\n", filename);
//         g_free(filename);
//     }

//     gtk_widget_destroy(dialog);
// }


// ファイル選択ダイアログ
std::vector<std::string> open_file_dialog(GtkWidget *parent) {
    std::vector<std::string> filenames;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Choose PDF Files",
                                                    GTK_WINDOW(parent),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Open", GTK_RESPONSE_ACCEPT,
                                                    NULL);
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GSList *files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
        for (GSList *iter = files; iter != NULL; iter = iter->next) {
            filenames.push_back(static_cast<char*>(iter->data));
            g_free(iter->data);
        }
        g_slist_free(files);
    }
    gtk_widget_destroy(dialog);
    return filenames;
}

// PDF結合処理
void on_merge_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *parent = GTK_WIDGET(data);
    std::vector<std::string> files = open_file_dialog(parent);
    if (files.size() < 2) return;

    std::string output = "merged.pdf";
    merge_pdfs(output, files);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "PDFs Merged!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// PDF圧縮処理
void on_compress_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *parent = GTK_WIDGET(data);
    std::vector<std::string> files = open_file_dialog(parent);
    if (files.empty()) return;

    std::string output = "compressed.pdf";
    compress_pdf(files[0], output);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "PDF Compressed!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void create_main_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PDF Tool");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *merge_button = gtk_button_new_with_label("Merge PDFs");
    GtkWidget *compress_button = gtk_button_new_with_label("Compress PDF");

    g_signal_connect(merge_button, "clicked", G_CALLBACK(on_merge_clicked), window);
    g_signal_connect(compress_button, "clicked", G_CALLBACK(on_compress_clicked), window);

    gtk_box_pack_start(GTK_BOX(vbox), merge_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), compress_button, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
}
