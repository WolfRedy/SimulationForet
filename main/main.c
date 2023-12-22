#include "../core/menu.h"
#define _MAIN_
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "../GUI/mainFrame.h"
#include "../core/ext_glob.h"

int main(int argc, char *argv[])
{   
    printf(R"EOF(
 _____                                                                          _____ 
( ___ )                                                                        ( ___ )
 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | 
 |   |                                                                          |   | 
 |   |       ____  (     (    (                    *            (        ____   |   | 
 |   |      |   /  )\ )  )\ ) )\ )               (  `           )\ )    |   /   |   | 
 |   |      |  /  (()/( (()/((()/( (        (    )\))(      (  (()/(    |  /    |   | 
 |   |      | /    /(_)) /(_))/(_)))\  ___  )\  ((_)()\     )\  /(_))   | /     |   | 
 |   |      |/    (_))_|(_)) (_)) ((_)|___|((_) (_()((_) _ ((_)(_))     |/      |   | 
 |   |     (      | |_  |_ _|| _ \| __|    | __||  \/  || | | || |     (        |   | 
 |   |     )\     | __|  | | |   /| _|     | _| | |\/| || |_| || |__   )\       |   | 
 |   |    ((_)    |_|   |___||_|_\|___|    |___||_|  |_| \___/ |____| ((_)      |   | 
 |   |                                                                          |   | 
 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| 
(_____)                                                                        (_____)
)EOF");

    if (argc < 2) {
        launchMenu();
        return 0;
    }
    int guiBool = atoi(argv[1]);
    if(guiBool==1){
        gtk_init(&argc, &argv);

        mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        gtk_widget_set_size_request(mainWindow, 300, 200);

        mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *label = gtk_label_new("Fire Emulation");
        GtkWidget *button = gtk_button_new_with_label("Forest Manager");
        
        
        g_signal_connect(button, "clicked", G_CALLBACK(do_assistant), NULL);
        

        gtk_box_pack_start(GTK_BOX(mainBox), label, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(mainBox), button, TRUE, TRUE, 10);
        

        gtk_container_add(GTK_CONTAINER(mainWindow), mainBox);
        gtk_container_set_border_width(GTK_CONTAINER(mainWindow), 10);

        gtk_widget_show_all(mainWindow);
        gtk_main();
    }
    return 0;
    
    
}
