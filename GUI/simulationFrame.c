#include <stdio.h>
#include <time.h> 
#include <stdbool.h>
#include <stdlib.h> 
#include <assert.h>
#include <ncurses.h>
#include "simulationFrame.h"
#include "../core/ext_glob.h"
#include "../core/pile.h"
#define IMAGE_SIZE 35
static GtkWidget *resize_image(const gchar *filename, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);

    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);

    return image;
}
void checkTypeImages(GtkWidget ***imageGrid, MAP** carteInitial, int i, int j){
    char filename[256];
    switch(carteInitial[i][j].type){
        case SOL:
            snprintf(filename, sizeof(filename), "ground.png");
            break;
        case ARBRE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "tree_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "tree.png");
            break;
        case FEUILLE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "leaves_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "leaves.png");
            break;
        case ROCHE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "stone_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "stone.png");
            break;
        case HERBE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "grass_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "grass.png");
            break;
        case EAU:
            snprintf(filename, sizeof(filename), "water.png");
            break;
        case CENDRES:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "cendres_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "cendres.png");
            break;
        case CENDRES_ETEINTES:
            snprintf(filename, sizeof(filename), "cendres_eteintes.png");
        case FEU:
            snprintf(filename, sizeof(filename), "feu.png");
        default:
            snprintf(filename, sizeof(filename), "grass.png");

    }
    imageGrid[i][j] = gtk_image_new_from_file(filename);
    imageGrid[i][j] = resize_image(filename, IMAGE_SIZE, IMAGE_SIZE);
}