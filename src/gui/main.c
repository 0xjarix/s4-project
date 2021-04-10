#include "main.h"
#include "../decode/d_main.h"

#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=true;goto ExitJmp;

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif


typedef struct BannerMenu
{
    GtkMenuBar *menu;
    GtkMenuItem *open;
    GtkMenuItem *quit;
    GtkMenuItem *about;
} BannerMenu;

typedef struct UserInterface
{

    // Main top-level window
    GtkWindow *window;

    // Top menu
    BannerMenu banner_menu;

    // Input image
    char *input_filename;
    GtkEventBox *input_image_event_box;
    GtkImage *input_image;

    // Buttons /////////////////////////////
    //// Preview
    GtkComboBox *preview_interpolation_menu;
    GdkInterpType interp_type;

    //// Options
    GtkCheckButton *save_output_toggle;
    GtkCheckButton *spellcheck_toggle;
    GtkCheckButton *manual_rotation_toggle;
    GtkSpinButton *manual_rotation_amount;

    //// Output
    GtkButton *save_button;
    GtkButton *output_button;
    ////////////////////////////////////////

    // Input
    GtkFileFilter *file_filter;

    // Output
    GtkTextBuffer *output_text;
    GtkTextBuffer *output_tree_text;
    GtkImage **processing_images;
} UserInterface;

void resize_to_fit(UserInterface *ui, GtkImage *image, int size)
{
    // Resize image to fit
    const GdkPixbuf *pb = gtk_image_get_pixbuf(image);
    //g_print("%s\n", (pb == NULL ? "NULL" : "NOT NULL"));
    const int imgW = gdk_pixbuf_get_width(pb);
    const int imgH = gdk_pixbuf_get_height(pb);

    double ratio;
    int destW;
    int destH;

    if(imgW > imgH)
        ratio = size / (double)imgW;
    else
        ratio = size / (double)imgH;

    destW = ratio * imgW;
    destH = ratio * imgH;

    GdkPixbuf *result =
        gdk_pixbuf_scale_simple(pb, destW, destH, ui->interp_type);

    gtk_image_set_from_pixbuf(image, result);
}

void open_file(UserInterface *ui, char *filename, GtkImage *destination,\
        int size)
{
    gtk_image_set_from_file(destination, filename);
    resize_to_fit(ui, destination, size);
}


void run_file_opener(UserInterface *ui)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Open File", ui->window,
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Open", GTK_RESPONSE_ACCEPT,
            NULL);
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(filter);
    gtk_file_filter_set_name(filter, "Images (.png/.jpg/.jpeg/etc...)");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

            open_file(ui, filename, ui->input_image, 360);
            ui->input_filename = filename;

            break;
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

void on_open_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UNUSED(menuitem);
    UserInterface *ui = user_data;

    run_file_opener(ui);
}

gboolean on_input_image_event_box_button_release_event(GtkWidget *widget,\
        GdkEvent *event, gpointer user_data)
{
    UNUSED(widget);
    UNUSED(event);
    UserInterface *ui = user_data;

    run_file_opener(ui);

    return TRUE;
}

void on_about_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UNUSED(menuitem);
    UNUSED(user_data);

    char *authors[] = {"Yassine DAMIRI <yassine.damiri@epita.fr>",\
        "Victor-Emmanuel PROVOST <victor-emmanuel.provost@epita.fr>",\
            "Raphaël DUHEN <raphael.duhen@epita.fr>",\
            "Param DAVE <param.dave@epita.fr>"};

    GdkPixbuf *logo =
        gdk_pixbuf_new_from_file("./resources/logo_small.png", NULL);
    gtk_show_about_dialog(\
            NULL,\
            "program-name", "Eye-T",\
            "logo", logo,\
            "title", "About Eye-T",\
            "comments", "Onii-san is watching you.",
            "version", "1.0.0",
            "license-type", GTK_LICENSE_MIT_X11,
            "authors", authors,
            NULL);
}

void on_preview_interpolation_menu_changed(GtkComboBox *widget,\
        gpointer user_data)
{
    UserInterface *ui = user_data;

    switch(gtk_combo_box_get_active(GTK_COMBO_BOX(widget)))
    {
        case 0:
            ui->interp_type = GDK_INTERP_NEAREST;
            break;
        case 1:
            ui->interp_type = GDK_INTERP_TILES;
            break;
        case 2:
            ui->interp_type = GDK_INTERP_BILINEAR;
            break;
        case 3:
            ui->interp_type = GDK_INTERP_HYPER;
            break;
        default:
            g_print("how even ?");
            break;
    }

    open_file(ui, ui->input_filename, ui->input_image, 360);
}

void on_save_button_clicked(GtkButton *button, gpointer user_data)
{
    UserInterface *ui = user_data;

    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Select File", ui->window, action,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Select", GTK_RESPONSE_ACCEPT,
            NULL);

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    gtk_file_chooser_set_current_name(chooser, "OCR_output");

    const char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

            gtk_button_set_label(button, filename);
            break;
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

void on_manual_rotation_amount_value_changed(GtkSpinButton *spin_button,\
        gpointer user_data)
{
    UNUSED(user_data);

    gtk_spin_button_set_value(spin_button,\
            (int)CLAMP(gtk_spin_button_get_value(spin_button), -180, 180));
}

void on_manual_rotation_toggle_toggled(GtkToggleButton *togglebutton,\
        gpointer user_data)
{
    UserInterface *ui = user_data;

    gtk_widget_set_sensitive(\
            GTK_WIDGET(ui->manual_rotation_amount),\
            gtk_toggle_button_get_active(togglebutton)\
            );
}

void on_save_output_toggle_toggled(GtkToggleButton *togglebutton,\
        gpointer user_data)
{
    UserInterface *ui = user_data;

    gtk_widget_set_sensitive(\
            GTK_WIDGET(ui->save_button),\
            gtk_toggle_button_get_active(togglebutton)\
            );
}

void save_output(UserInterface *ui)
{
    const char *filename = gtk_button_get_label(ui->save_button);
    if(!gtk_widget_get_sensitive(GTK_WIDGET(ui->save_button))
            || strcmp(filename, "Choose save location"))
    {
        FILE *fptr = fopen(filename, "w+");

        GtkTextIter start;
        GtkTextIter end;
        gtk_text_buffer_get_bounds(ui->output_text, &start, &end);

        gchar *text =
            gtk_text_buffer_get_text(ui->output_text, &start, &end, FALSE);

        fprintf(fptr, text);

        fclose(fptr);
    }
    else
    {
        GtkMessageDialog *dialog =
            GTK_MESSAGE_DIALOG(gtk_message_dialog_new_with_markup(\
                        ui->window,\
                        GTK_DIALOG_DESTROY_WITH_PARENT,\
                        GTK_MESSAGE_ERROR,\
                        GTK_BUTTONS_CLOSE,\
                        "<b>Please select a valid save location</b>"\
                        "<b> or disable saving.</b>"));

        gtk_dialog_run(GTK_DIALOG(dialog));

        gtk_widget_destroy(GTK_WIDGET(dialog));
    }
}

void on_output_button_clicked(GtkButton *button, gpointer user_data)
{
    //int passed = 0;
    UNUSED(button);
    UserInterface *ui = user_data;


    char *argv[2] = {"./gui", ui->input_filename };
    gtk_text_buffer_set_text(ui->output_text, start(2, argv, 0), -1);
    //COUCOU(passed);
    //passed++;
}


int main()
{
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Construct a GtkBuilder instance
    GtkBuilder *builder = gtk_builder_new();

    // Loads the UI description (exits if an error occurs)
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "src/gui/acre.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Main top-level window
    GtkWindow *window =
        GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.ocr"));

    // Top menu
    GtkMenuBar *menu =
        GTK_MENU_BAR(gtk_builder_get_object(builder, "menu"));

    // Input image
    GtkEventBox *input_image_event_box =
        GTK_EVENT_BOX(gtk_builder_get_object(builder, "input_image_event_box"));
    GtkImage *input_image =
        GTK_IMAGE(gtk_builder_get_object(builder, "input_image"));

    // Input filter
    GtkFileFilter *file_filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(file_filter);

    // Buttons
    //// Input
    GtkMenuItem *open =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "open"));

    //// Preview
    GtkComboBox *preview_interpolation_menu =
        GTK_COMBO_BOX(gtk_builder_get_object(builder,\
                    "preview_interpolation_menu"));
    GdkInterpType interp_type = GDK_INTERP_BILINEAR;

    //// Options
    GtkCheckButton *save_output_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "save_output_toggle"));
    GtkCheckButton *spellcheck_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "spellcheck_toggle"));
    GtkCheckButton *manual_rotation_toggle =
        GTK_CHECK_BUTTON(\
                gtk_builder_get_object(\
                    builder,\
                    "manual_rotation_toggle"));
    GtkSpinButton *manual_rotation_amount =
        GTK_SPIN_BUTTON(\
                gtk_builder_get_object(\
                    builder,\
                    "manual_rotation_amount"));

    //// Output
    GtkButton *save_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "save_button"));
    GtkButton *output_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "output_button"));

    // Annex
    GtkMenuItem *about =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "about"));

    // Output
    GtkTextBuffer *output_text =
        GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "output_text"));
    GtkTextBuffer *output_tree_text =
        GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "tree_output_text"));
    GtkImage *processing_images[6];
    // Quit
    GtkMenuItem *quit =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "quit"));

    UserInterface ui =
    {

        // Main top-level window
        .window = window,

        // Top menu
        .banner_menu =
        {
            .menu = menu,
            .open = open,
            .quit = quit,
            .about = about,
        },

        // Input image
        .input_filename = malloc(256 * sizeof(char)),
        .input_image_event_box = input_image_event_box,
        .input_image = input_image,

        // Buttons
        //// Preview
        .preview_interpolation_menu = preview_interpolation_menu,
        .interp_type = interp_type,

        //// Options
        .save_output_toggle = save_output_toggle,
        .spellcheck_toggle = spellcheck_toggle,
        .manual_rotation_toggle = manual_rotation_toggle,
        .manual_rotation_amount = manual_rotation_amount,

        //// Output
        .save_button = save_button,
        .output_button = output_button,

        // Input
        .file_filter = file_filter,

        // Output
        .output_text = output_text,
        .output_tree_text = output_tree_text,
        .processing_images = processing_images,
    };

    // Connects event handlers ////////////////////////////////////////////////
    //// Top-level window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(quit, "activate", G_CALLBACK(gtk_main_quit), NULL);

    //// Top Menu
    g_signal_connect(open, "activate", G_CALLBACK(on_open_activate), &ui);
    g_signal_connect(about, "activate", G_CALLBACK(on_about_activate), &ui);

    //// Input image
    g_signal_connect(GTK_WIDGET(input_image_event_box), "button-release-event",\
            G_CALLBACK(on_input_image_event_box_button_release_event), &ui);

    //// Preview

    //// Options
    ////// Output
    g_signal_connect(output_button, "clicked",\
            G_CALLBACK(on_output_button_clicked), &ui);


    ///////////////////////////////////////////////////////////////////////////

    // Legacy: Print supported image formats.
    // GSList *formats = gdk_pixbuf_get_formats();
    // for(guint i = 0; i < g_slist_length(formats); i++)
    // {
    //     g_print("%s\n",
    //             gdk_pixbuf_format_get_name(g_slist_nth_data(formats, i)));
    // }

    gtk_main();

    free(ui.input_filename);

    return 0;
}
