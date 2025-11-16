#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gui.h"
#include "calc.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *entry_expression;
    GtkWidget *label_result;
    GtkWidget *spin_size_limit;
    GtkWidget *radio_infix;
    GtkWidget *radio_postfix;
    GtkWidget *radio_prefix;
    GtkWidget *text_view;
    GtkTextBuffer *text_buffer;
} CalculatorGUI;

static int get_expression_type(CalculatorGUI *gui) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->radio_postfix))) {
        return 2;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->radio_prefix))) {
        return 3;
    }
    return 1; // Infix default
}

static void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    CalculatorGUI *gui = (CalculatorGUI *)data;
    
    const char *expr = gtk_entry_get_text(GTK_ENTRY(gui->entry_expression));
    int exprType = get_expression_type(gui);
    int sizeLimit = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui->spin_size_limit));
    
    if (strlen(expr) == 0) {
        gtk_label_set_text(GTK_LABEL(gui->label_result), "Error: Please enter an expression");
        return;
    }
    
    if (strlen(expr) > sizeLimit) {
        gtk_label_set_text(GTK_LABEL(gui->label_result), "Error: Expression exceeds size limit");
        return;
    }
    
    double result;
    char result_text[200];
    
    switch(exprType) {
        case 2:
            result = evalPostfix(expr);
            break;
        case 3:
            result = evalPrefix(expr);
            break;
        default:
            result = eval(expr);
            break;
    }
    
    snprintf(result_text, sizeof(result_text), "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(gui->label_result), result_text);
}

static void on_clear_clicked(GtkWidget *widget, gpointer data) {
    CalculatorGUI *gui = (CalculatorGUI *)data;
    gtk_entry_set_text(GTK_ENTRY(gui->entry_expression), "");
    gtk_label_set_text(GTK_LABEL(gui->label_result), "Result: ");
    gtk_text_buffer_set_text(gui->text_buffer, "", -1);
}

static void on_file_open_clicked(GtkWidget *widget, gpointer data) {
    CalculatorGUI *gui = (CalculatorGUI *)data;
    
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File",
                                                     GTK_WINDOW(gui->window),
                                                     GTK_FILE_CHOOSER_ACTION_OPEN,
                                                     "_Cancel", GTK_RESPONSE_CANCEL,
                                                     "_Open", GTK_RESPONSE_ACCEPT,
                                                     NULL);
    
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        
        FILE *fp = fopen(filename, "r");
        if (!fp) {
            gtk_label_set_text(GTK_LABEL(gui->label_result), "Error: File not found");
            g_free(filename);
            gtk_widget_destroy(dialog);
            return;
        }
        
        char expr[EXPR_MAX];
        char all_results[4096] = "--- Results from file ---\n";
        int exprType = get_expression_type(gui);
        
        while (fgets(expr, sizeof(expr), fp)) {
            expr[strcspn(expr, "\n")] = '\0';
            if (strlen(expr) == 0) continue;
            
            double result;
            char line_result[256];
            
            switch(exprType) {
                case 2:
                    result = evalPostfix(expr);
                    break;
                case 3:
                    result = evalPrefix(expr);
                    break;
                default:
                    result = eval(expr);
                    break;
            }
            
            snprintf(line_result, sizeof(line_result), "%s = %.2f\n", expr, result);
            strcat(all_results, line_result);
        }
        
        fclose(fp);
        gtk_text_buffer_set_text(gui->text_buffer, all_results, -1);
        gtk_label_set_text(GTK_LABEL(gui->label_result), "File processed successfully");
        
        g_free(filename);
    }
    
    gtk_widget_destroy(dialog);
}

void run_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Enable dark theme
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
    
    // Apply custom CSS for dark theme styling
    GtkCssProvider *css_provider = gtk_css_provider_new();
    const gchar *css_data = 
        "window { background-color: #2b2b2b; }"
        "frame { background-color: #353535; border-radius: 5px; }"
        "label { color: #e0e0e0; }"
        "entry { background-color: #404040; color: #ffffff; border: 1px solid #555555; padding: 8px; border-radius: 4px; }"
        "button { background-color: #4a4a4a; color: #ffffff; border: 1px solid #666666; padding: 8px 16px; border-radius: 4px; }"
        "button:hover { background-color: #5a5a5a; }"
        "button:active { background-color: #353535; }"
        "spinbutton { background-color: #404040; color: #ffffff; border: 1px solid #555555; border-radius: 4px; }"
        "textview { background-color: #1e1e1e; color: #d4d4d4; font-family: monospace; font-size: 10pt; }"
        "textview text { background-color: #1e1e1e; color: #d4d4d4; }"
        "radiobutton { color: #e0e0e0; }"
        "radiobutton:checked { color: #4CAF50; }";
    gtk_css_provider_load_from_data(css_provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    g_object_unref(css_provider);
    
    CalculatorGUI *gui = g_malloc(sizeof(CalculatorGUI));
    
    // Create main window
    gui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gui->window), "Expression Calculator");
    gtk_window_set_default_size(GTK_WINDOW(gui->window), 600, 500);
    gtk_container_set_border_width(GTK_CONTAINER(gui->window), 10);
    g_signal_connect(gui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Main vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(gui->window), vbox);
    
    // Size limit section
    GtkWidget *hbox_size = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *label_size = gtk_label_new("Expression Size Limit:");
    gui->spin_size_limit = gtk_spin_button_new_with_range(1, EXPR_MAX, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui->spin_size_limit), EXPR_MAX);
    gtk_box_pack_start(GTK_BOX(hbox_size), label_size, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_size), gui->spin_size_limit, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_size, FALSE, FALSE, 0);
    
    // Expression type section
    GtkWidget *frame_type = gtk_frame_new("Expression Type");
    GtkWidget *vbox_type = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox_type), 10);
    
    gui->radio_infix = gtk_radio_button_new_with_label(NULL, "Infix (default)");
    gui->radio_postfix = gtk_radio_button_new_with_label_from_widget(
        GTK_RADIO_BUTTON(gui->radio_infix), "Postfix");
    gui->radio_prefix = gtk_radio_button_new_with_label_from_widget(
        GTK_RADIO_BUTTON(gui->radio_infix), "Prefix");
    
    gtk_box_pack_start(GTK_BOX(vbox_type), gui->radio_infix, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_type), gui->radio_postfix, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_type), gui->radio_prefix, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame_type), vbox_type);
    gtk_box_pack_start(GTK_BOX(vbox), frame_type, FALSE, FALSE, 0);
    
    // Expression input section
    GtkWidget *hbox_expr = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *label_expr = gtk_label_new("Expression:");
    gui->entry_expression = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(gui->entry_expression), 
                                    "Enter expression (e.g., 2+3*4 or use File button)");
    gtk_box_pack_start(GTK_BOX(hbox_expr), label_expr, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_expr), gui->entry_expression, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_expr, FALSE, FALSE, 0);
    
    // Buttons section
    GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *btn_calculate = gtk_button_new_with_label("Calculate");
    GtkWidget *btn_clear = gtk_button_new_with_label("Clear");
    GtkWidget *btn_file = gtk_button_new_with_label("Open File");
    
    g_signal_connect(btn_calculate, "clicked", G_CALLBACK(on_calculate_clicked), gui);
    g_signal_connect(btn_clear, "clicked", G_CALLBACK(on_clear_clicked), gui);
    g_signal_connect(btn_file, "clicked", G_CALLBACK(on_file_open_clicked), gui);
    
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_calculate, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_clear, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_file, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);
    
    // Result label
    gui->label_result = gtk_label_new("Result: ");
    gtk_label_set_xalign(GTK_LABEL(gui->label_result), 0);
    PangoAttrList *attrs = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(1.5);
    pango_attr_list_insert(attrs, attr);
    gtk_label_set_attributes(GTK_LABEL(gui->label_result), attrs);
    pango_attr_list_unref(attrs);
    gtk_box_pack_start(GTK_BOX(vbox), gui->label_result, FALSE, FALSE, 0);
    
    // Text view for file results
    GtkWidget *frame_results = gtk_frame_new("File Results");
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    
    gui->text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(gui->text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(gui->text_view), GTK_WRAP_WORD);
    gui->text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->text_view));
    
    gtk_container_add(GTK_CONTAINER(scrolled), gui->text_view);
    gtk_container_add(GTK_CONTAINER(frame_results), scrolled);
    gtk_box_pack_start(GTK_BOX(vbox), frame_results, TRUE, TRUE, 0);
    
    // Show all widgets
    gtk_widget_show_all(gui->window);
    
    // Run GTK main loop
    gtk_main();
    
    g_free(gui);
}
