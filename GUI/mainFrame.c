
#include "../GUI/mainFrame.h"
//#include "../simulation/dijkstra.h"
#include "../simulation/simulation.h"
#include "../core/pile.h"
#include <stdbool.h>

#include <gtk/gtk.h>
#define GRID_SIZE 20
#define IMAGE_SIZE 35
static GtkWidget *assistant = NULL;
static GtkWidget *progress_bar = NULL;

MAP** carteInitial = NULL;
FLAMES* tableauSuivant = NULL;
pile* pileSimulation = NULL;


static gboolean apply_changes_gradually (gpointer data)
{
  gdouble fraction;

  /* Work, work, work... */
  fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progress_bar));
  fraction += 0.05;

  if (fraction < 1.0)
    {
      gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progress_bar), fraction);
      return G_SOURCE_CONTINUE;
    }
  else
    {
      /* Close automatically once changes are fully applied. */
      gtk_widget_destroy (assistant);
      assistant = NULL;
      return G_SOURCE_REMOVE;
    }
}

static void
on_assistant_apply (GtkWidget *widget, gpointer data)
{
  /* Start a timer to simulate changes taking a few seconds to apply. */
  g_timeout_add (100, apply_changes_gradually, NULL);
  GtkWidget *button2 = gtk_button_new_with_label("Open forest");
  g_signal_connect(button2, "clicked", G_CALLBACK(do_forest), NULL);
  gtk_box_pack_start(GTK_BOX(mainBox), button2, TRUE, TRUE, 10);
  gtk_widget_show_all(mainWindow);
}

static void
on_assistant_close_cancel (GtkWidget *widget, gpointer data)
{
  GtkWidget **assistant = (GtkWidget **) data;

  gtk_widget_destroy (*assistant);
  *assistant = NULL;
}

static void
on_assistant_prepare (GtkWidget *widget, GtkWidget *page, gpointer data)
{
  gint current_page, n_pages;
  gchar *title;

  current_page = gtk_assistant_get_current_page (GTK_ASSISTANT (widget));
  n_pages = gtk_assistant_get_n_pages (GTK_ASSISTANT (widget));

  title = g_strdup_printf ("Sample assistant (%d of %d)", current_page + 1, n_pages);
  gtk_window_set_title (GTK_WINDOW (widget), title);
  g_free (title);

  /* The fourth page (counting from zero) is the progress page.  The
  * user clicked Apply to get here so we tell the assistant to commit,
  * which means the changes up to this point are permanent and cannot
  * be cancelled or revisited. */
  
  if (current_page == 3)
      gtk_assistant_commit (GTK_ASSISTANT (widget));
}

static void
on_entry_changed (GtkWidget *entry, gpointer data)
{
  int *variable = (int *)data;
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));

  // Conversion de la chaîne de texte en entier
  *variable = atoi(text);

}
static void on_lenght_changed(GtkRange *range, gpointer user_data) {


    longueur = gtk_range_get_value(range);
    GtkAssistant *assistant = GTK_ASSISTANT (user_data);
    GtkWidget *current_page;
    gint page_number;

    page_number = gtk_assistant_get_current_page (assistant);
    current_page = gtk_assistant_get_nth_page (assistant, page_number);
    gtk_assistant_set_page_complete (assistant, current_page, TRUE);
}
static void on_width_changed(GtkRange *range, gpointer user_data) {


    largeur = gtk_range_get_value(range);

    //g_print("Valeur changée : %f\n", largeur);
    GtkAssistant *assistant = GTK_ASSISTANT (user_data);
    GtkWidget *current_page;
    gint page_number;
    //const gchar *text;

    page_number = gtk_assistant_get_current_page (assistant);
    current_page = gtk_assistant_get_nth_page (assistant, page_number);
    //text = gtk_entry_get_text (GTK_ENTRY (widget));
    gtk_assistant_set_page_complete (assistant, current_page, TRUE);
}
static void on_buttonRandom_clicked(GtkRange *range, gpointer user_data){
    //*gdouble value = gtk_range_get_value(range);

    //g_print("Valeur changée : %f\n", value);
    GtkAssistant *assistant = GTK_ASSISTANT (user_data);
    GtkWidget *current_page;
    gint page_number;
    //const gchar *text;
    carteInitial = create2DTable();
    initRandom2DTable(carteInitial);
    page_number = gtk_assistant_get_current_page (assistant);
    current_page = gtk_assistant_get_nth_page (assistant, page_number);
    //text = gtk_entry_get_text (GTK_ENTRY (widget));
    gtk_assistant_set_page_complete (assistant, current_page, TRUE);
}

static void lenghtForest (GtkWidget *assistant)
{
    GtkWidget *box, *label, *entry;

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width (GTK_CONTAINER (box), 12);

    label = gtk_label_new ("You must fill out this entry to continue:");
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);

    //entry = gtk_entry_new ();
    //gtk_entry_set_activates_default (GTK_ENTRY (entry), TRUE);
    //gtk_widget_set_valign (entry, GTK_ALIGN_CENTER);
    //gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 0);
    GtkWidget *length_label = gtk_label_new("Longueur :");
    gtk_box_pack_start(GTK_BOX(box), length_label, FALSE, FALSE, 0);

    GtkWidget *length_range = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 2, 30, 1);
    g_signal_connect(G_OBJECT(length_range), "value-changed", G_CALLBACK(on_lenght_changed), assistant);
    gtk_box_pack_start(GTK_BOX(box), length_range, FALSE, FALSE, 0);

    GtkWidget *width_label = gtk_label_new("Largeur :");
    gtk_box_pack_start(GTK_BOX(box), width_label, FALSE, FALSE, 0);

    GtkWidget *width_range = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 2, 30, 1);
    g_signal_connect(G_OBJECT(width_range), "value-changed", G_CALLBACK(on_width_changed), assistant);
    gtk_box_pack_start(GTK_BOX(box), width_range, FALSE, FALSE, 0);

    GtkWidget *labelFeuX = gtk_label_new("Coordonnée X départ du feu:");
    GtkWidget *entryFeuX = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), labelFeuX, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), entryFeuX, FALSE, FALSE, 0);
    g_signal_connect(entryFeuX, "changed", G_CALLBACK(on_entry_changed), &positionFlameX);

    GtkWidget *labelFeuY = gtk_label_new("Coordonnée Y départ du feu:");
    GtkWidget *entryFeuY = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), labelFeuY, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), entryFeuY, FALSE, FALSE, 0);
    g_signal_connect(entryFeuY, "changed", G_CALLBACK(on_entry_changed), &positionFlameY);
    //g_signal_connect (G_OBJECT (entry), "changed",G_CALLBACK (on_entry_changed), assistant);

    gtk_widget_show_all (box);
    gtk_assistant_append_page (GTK_ASSISTANT (assistant), box);
    gtk_assistant_set_page_title (GTK_ASSISTANT (assistant), box, "Taille de votre forêt");
    gtk_assistant_set_page_type (GTK_ASSISTANT (assistant), box, GTK_ASSISTANT_PAGE_INTRO);
}

static void createForest (GtkWidget *assistant)
{
    GtkWidget *box, *buttonRandom, *buttonManuel;

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width (GTK_CONTAINER (box), 12);

    buttonRandom = gtk_button_new_with_label ("Remplissage aléatoire de la forêt");
    buttonManuel = gtk_button_new_with_label ("Remplissage manuel");                                               
    gtk_box_pack_start (GTK_BOX (box), buttonRandom, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box), buttonManuel, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(buttonRandom), "clicked", G_CALLBACK(on_buttonRandom_clicked), assistant);
    gtk_widget_show_all (box);
    gtk_assistant_append_page (GTK_ASSISTANT (assistant), box);
    gtk_assistant_set_page_type (GTK_ASSISTANT (assistant), box, GTK_ASSISTANT_PAGE_CONFIRM);
    gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant), box, FALSE);
    gtk_assistant_set_page_title (GTK_ASSISTANT (assistant), box, "Création de votre forêt");
}
void button_clicked(GtkButton *button, gpointer user_data){
    g_print("Button clicked: %s\n", gtk_button_get_label(button));
}
static void seeForest (GtkWidget *assistant)
{
    GtkWidget *box;
    GtkWidget *grid;
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
    gtk_container_set_border_width (GTK_CONTAINER (box), 12);


  gtk_widget_show_all(box);
  gtk_assistant_append_page (GTK_ASSISTANT (assistant), box);
  gtk_assistant_set_page_type (GTK_ASSISTANT (assistant), box, GTK_ASSISTANT_PAGE_CONFIRM);
  gtk_assistant_set_page_title (GTK_ASSISTANT (assistant), box, "");
}

static void
create_page4 (GtkWidget *assistant)
{
  progress_bar = gtk_progress_bar_new ();
  gtk_widget_set_halign (progress_bar, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (progress_bar, GTK_ALIGN_CENTER);

  gtk_widget_show (progress_bar);
  gtk_assistant_append_page (GTK_ASSISTANT (assistant), progress_bar);
  gtk_assistant_set_page_type (GTK_ASSISTANT (assistant), progress_bar, GTK_ASSISTANT_PAGE_PROGRESS);
  gtk_assistant_set_page_title (GTK_ASSISTANT (assistant), progress_bar, "");
  gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant), progress_bar, FALSE);
}


static GtkWidget *resize_image(const gchar *filename, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);

    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);

    return image;
}
static void on_image_clicked(GtkWidget *widget, GdkEvent *event, gpointer data) {
  printf("clicked");
}



GtkWidget* do_assistant (GtkWidget *do_widget)
{
  if (!assistant)
    {
      assistant = gtk_assistant_new ();

      gtk_window_set_default_size (GTK_WINDOW (assistant), -1, 300);

      gtk_window_set_screen (GTK_WINDOW (assistant),gtk_widget_get_screen (do_widget));

      lenghtForest (assistant);
      createForest (assistant);
      seeForest (assistant);
      create_page4 (assistant);

      g_signal_connect (G_OBJECT (assistant), "cancel", G_CALLBACK (on_assistant_close_cancel), &assistant);
      g_signal_connect (G_OBJECT (assistant), "close", G_CALLBACK (on_assistant_close_cancel), &assistant);
      g_signal_connect (G_OBJECT (assistant), "apply", G_CALLBACK (on_assistant_apply), NULL);
      g_signal_connect (G_OBJECT (assistant), "prepare", G_CALLBACK (on_assistant_prepare), NULL);
    }

  if (!gtk_widget_get_visible (assistant))
    gtk_widget_show (assistant);
  else
    {
      gtk_widget_destroy (assistant);
      assistant = NULL;
    }

  return assistant;
}



void do_forest(GtkWidget *widget, gpointer data){
  
  if(data){
    
    GtkWidget *previousWindow = GTK_WIDGET(data);
    gtk_widget_hide(previousWindow);
    carteInitial = create2DTable();
    nextMap(pileSimulation->adresseCarte,carteInitial);
    tableauSuivant = createFlamesTable();
    copyTab(pileSimulation->tabCoordFeu, tableauSuivant);
    searchNeighbourhood(carteInitial,tableauSuivant);
    //printf("\n");
    push(&pileSimulation,carteInitial, tableauSuivant);
    //affichage_de_la_carte(carteInitial);
  }else{
    //printf("eee");
    tableauSuivant = createFlamesTable();
    tableauSuivant->x=positionFlameX;
    tableauSuivant->y=positionFlameY;
    tableauSuivant[1].exit=-1;
    carteInitial[positionFlameX][positionFlameY].type = FEU;

    carteInitial[positionFlameX][positionFlameY].degree = 5;
 
    carteInitial[positionFlameX][positionFlameY].etat = 1;
    editMap(carteInitial);
    push(&pileSimulation,carteInitial, tableauSuivant);

  }
  GtkWidget ***imageGrid = (GtkWidget ***)malloc(longueur * sizeof(GtkWidget **));
  for (int i = 0; i < longueur; ++i) {
      imageGrid[i] = (GtkWidget **)malloc(largeur * sizeof(GtkWidget *));
  }
   GtkWidget *grid = gtk_grid_new();
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request(window, 300, 200);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_set_border_width (GTK_CONTAINER (box), 12);
  gtk_container_add(GTK_CONTAINER(box), grid);
  GtkWidget *nextButton = gtk_button_new_with_label("NEXT");
  g_signal_connect(nextButton, "clicked", G_CALLBACK(do_forest), window);
  gtk_container_add(GTK_CONTAINER(box), nextButton);
 
  for (int i = 0; i < longueur; i++) {
    for (int j = 0; j < largeur; j++) {
      char filename[256];
      switch(carteInitial[i][j].type){
        case SOL:
            snprintf(filename, sizeof(filename), "./image/ground.png");
            break;
        case ARBRE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "./image/tree_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "./image/tree.png");
            break;
        case FEUILLE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "./image/leaves_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "./image/leaves.png");
            break;
        case ROCHE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "./image/stone_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "./image/stone.png");
            break;
        case HERBE:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "./image/grass_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "./image/grass.png");
            break;
        case EAU:
            snprintf(filename, sizeof(filename), "./image/water.png");
            break;
        case FEU:
            snprintf(filename, sizeof(filename), "./image/feu.png");
            break;
        case CENDRES:
            if(carteInitial[i][j].etat==1){
                snprintf(filename, sizeof(filename), "./image/cendres_feu.png");
                break;
            }
            snprintf(filename, sizeof(filename), "./image/cendres.png");
            break;
        case CENDRES_ETEINTES:
          if(carteInitial[i][j].degree==0){
                  snprintf(filename, sizeof(filename), "./image/cendres_eteintes.png");
                  break;
              }
            break;
      }
      
          
          imageGrid[i][j] = gtk_image_new_from_file(filename);
          
          g_signal_connect(imageGrid[i][j], "button-press-event", G_CALLBACK(on_image_clicked), NULL);
          imageGrid[i][j] = resize_image(filename, IMAGE_SIZE, IMAGE_SIZE);
          gtk_grid_attach(GTK_GRID(grid), imageGrid[i][j], i, j, 1, 1);
          
      }
  }

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_show_all(window);
}