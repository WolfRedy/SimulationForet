#ifndef _EXTGLOB_H_
#define _EXTGLOB_H_

#ifndef _MAIN_
#define _EXTERN extern
#else
#define _EXTERN
#endif
#include "../core/ext_glob.h"
#include <gtk/gtk.h>
_EXTERN int longueur;
_EXTERN int largeur;
_EXTERN int positionFlameX;
_EXTERN int positionFlameY;
_EXTERN int initializedForestGUI;
_EXTERN GtkWidget *mainWindow;
_EXTERN GtkWidget *mainBox; 

bool isInBound(int x, int y);
#endif