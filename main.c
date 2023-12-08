#include "menu.h"
#define _MAIN_
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "ext_glob.h"
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
int main(int argc, char *argv[])
{   
    int test=0;
    //printf("%s",argv[1]);
    if(test==1){
         /* Déclaration du widget */
        GtkWidget *pWindow;
        GtkWidget *pLabel;
        GtkWidget *pHBox;
        GtkWidget *pVBox;
        GtkWidget *pButtons[2];
        gtk_init(&argc,&argv);
        
        /* Création de la fenêtre */
        pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(pWindow), "Simulation Incendie");
        gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size(GTK_WINDOW(pWindow), 620,300);
        gtk_window_set_resizable(GTK_WINDOW(pWindow),TRUE);
        
        pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        pHBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_box_set_homogeneous(GTK_BOX(pHBox), TRUE);
        gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
        pLabel = gtk_label_new("Forest creation");
        pButtons[0] = gtk_button_new_with_label("From a file");
        pButtons[1] = gtk_button_new_with_label("Manual forest creation");

        MyWindow *my_window = pWindow;
        //myWindows->window=pWindow;
        int x = 2;
        g_signal_connect(pButtons[1], "clicked", G_CALLBACK(OnClick),my_window);

        gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0 );

        gtk_box_pack_start(GTK_BOX(pHBox), pButtons[0], TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pHBox), pButtons[1], TRUE, TRUE, 0);

        

        /* Connexion du signal "destroy" */
        g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);
        /* Affichage de la fenêtre */
        gtk_widget_show_all(pWindow);
        /* Demarrage de la boucle évènementielle */
        gtk_main();
    
        return EXIT_SUCCESS;
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
