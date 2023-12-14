#include "../core/menu.h"
#define _MAIN_
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../core/ext_glob.h"
#define GRID_SIZE 5
void OnDestroy(GtkWidget *pWidget, gpointer pData);
void OnClick(GtkWidget *pWidget, gpointer pData);
// Structure pour stocker les données de chaque fenêtre
typedef struct 
{ 
  GtkWindow parent; 
  
  /* Les widgets composant notre fenêtre que nous souhaitons cacher */ 
  GtkWidget *widget1; 
  GtkWidget *widget2; 
} MyWindow; 
void button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button clicked: %s\n", gtk_button_get_label(button));
}
int main(int argc, char *argv[])
{   
    int test=1;
    //printf("%s",argv[1]);
    if(test==1){
       GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[GRID_SIZE][GRID_SIZE];
    char label[5];

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Grid Example");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create buttons and add them to the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            snprintf(label, sizeof(label), "%d,%d", i, j);
            button[i][j] = gtk_button_new_with_label(label);
            g_signal_connect(button[i][j], "clicked", G_CALLBACK(button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), button[i][j], i, j, 1, 1);
        }
    }

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
    }
    launchMenu();
    return 0;
}
void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle évènementielle */
    gtk_main_quit();
}
void OnClick(GtkWidget *pWidget, gpointer pData){
    MyWindow *self = pData;
    GtkWidget *newWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(newWindow),"New Window");
    gtk_widget_show_all(newWindow);
    //gtk_widget_hide(self->widget1);
    //gtk_widget_hide(self->widget2);
    //printf("%d",pData);
}
