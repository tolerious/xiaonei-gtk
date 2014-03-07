/* 
 * File:   main.c
 * Author: fengtianba
 *
 * Created on February 13, 2014, 9:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <assert.h>
#include "AccessToken.h"
#include <curl/curl.h>
#include <glib-2.0/glib/gerror.h>
/*
 * 
 */
enum
{
    COL_DISPLAY_NAME = 0,
    COL_PIXBUF,
    NUM_COLS
};
GtkTreeModel*  create_model(void);
int main(int argc, char** argv) {
    GetAccessToken();
    int i = 100;
    char *decode_string;
    system("firefox result.html  2>/dev/null &");
    puts("\n\nget AccessToken successful\n\n");
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    decode_string = curl_easy_unescape(curl, ACCESS_TOKEN, 0, &i);
    printf("origin url: %s\n", ACCESS_TOKEN);
    printf("new    url: %s\n", decode_string);
    curl_easy_cleanup(curl);
    char accesstoken[500];
    puts("enter access token\n");
    scanf("%s",  accesstoken);
    xiaonei_gtk_get_blog_list(accesstoken);
    //xiaonei_gtk_create_one_blog(accesstoken);
    
    //gtk wdiget init start...
    GtkWidget *window, *icon_view, *notebook;
    GtkBuilder *builder;
    GError *error = NULL;
    
    //widget init
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./sources/glade.ui", &error))
    {
        g_print("Error occured while loading UI files\n");
        g_print("Message: %s\n", error->message);
        g_free(error);
        return 1;
    }
    
    //widget get from builder(glade files)
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    notebook = GTK_WIDGET(gtk_builder_get_object(builder, "notebook1"));
    icon_view = GTK_WIDGET(gtk_builder_get_object(builder, "iconview1"));
    
    
    //set object attributes
    gtk_window_set_title(GTK_WINDOW(window), "Xiao nei Gtk Demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    icon_view = gtk_icon_view_new_with_model(create_model());
    gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view), COL_DISPLAY_NAME);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view), COL_PIXBUF);
    
    
    gtk_container_add(GTK_CONTAINER(notebook), icon_view);
    
    
    
    //signal to connect to widget
    g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
    
    
    
    
    
    
    //object unref
    g_object_unref(G_OBJECT(builder));
    
    
    //show widget 
    gtk_widget_show_all(window);
    gtk_main();
    
    return (EXIT_SUCCESS);
}
GtkTreeModel* create_model(void)
{
    GtkListStore *list_store;
    GdkPixbuf *p1;
    GtkTreeIter iter;
    GError *err = NULL;
    
    p1= gdk_pixbuf_new_from_file("./sources/1.PNG", &err);
    
    assert(err == NULL);
    list_store = gtk_list_store_new(NUM_COLS,
            G_TYPE_STRING, GDK_TYPE_PIXBUF);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            "icon", COL_PIXBUF, p1, -1);
    
    return GTK_TREE_MODEL(list_store);
}