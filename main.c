/* 
 * File:   main.c
 * Author: fengtianba
 *
 * Created on February 13, 2014, 9:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "AccessToken.h"
#include <curl/curl.h>
#include <glib-2.0/glib/gerror.h>
/*
 * 
 */
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
    GtkWidget *window;
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
    
    
    
    //set object attributes
    gtk_window_set_title(GTK_WINDOW(window), "Xiao nei Gtk Demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    
    
    
    
    //signal to connect to widget
    g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
    
    
    
    
    
    
    //object unref
    g_object_unref(G_OBJECT(builder));
    
    
    //show widget 
    gtk_widget_show_all(window);
    gtk_main();
    
    return (EXIT_SUCCESS);
}

