/* 
 * File:   main.c
 * Author: fengtianba
 *
 * Created on February 13, 2014, 9:45 PM
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <assert.h>
#include "AccessToken.h"
#include <curl/curl.h>
#include <time.h>
#include <glib-2.0/glib/gerror.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <malloc.h>
/*
 * 
 */
#define ICON_NUM 8
enum
{
    COL_DISPLAY_NAME = 0,
    COL_PIXBUF,
    NUM_COLS
};
char accesstoken[500];
//icon view sigle click callback
void icon_view_item_select(GtkIconView *icon_view, GtkTreePath *path, gpointer userdata);
void home_button_clicked(GtkButton *button, gpointer userdata);
void access_token_ok_button_clicked(GtkButton *button, gpointer userdata);
gboolean set_label_time(gpointer userdata);
GtkTreeModel*  create_model(void);
int main(int argc, char** argv) {
    
    GetAccessToken();
    system("firefox result.html  2>/dev/null &");
    //gtk wdiget init start...
    GtkWidget *window, *icon_view, *notebook;
    GtkWidget *current_user_name, *current_time, *network_speed;
    GtkWidget *username_entry, *password_entry;
    GtkWidget *home_button, *access_token_entry, *access_token_ok_button;
    GtkWidget *access_token_cancel_button;
    GtkBuilder *builder;
    GError *error = NULL;
    
    //widget init
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./sources/glade.glade", &error))
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
    current_user_name = GTK_WIDGET(gtk_builder_get_object(builder,"label4"));
    current_time = GTK_WIDGET(gtk_builder_get_object(builder, "label5"));
    network_speed = GTK_WIDGET(gtk_builder_get_object(builder, "label6"));
    username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
    access_token_ok_button = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    access_token_cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    home_button = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    access_token_entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    
    
    //set object attributes
    gtk_window_set_title(GTK_WINDOW(window), "Xiao nei Gtk App");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view), create_model());
    gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view), COL_DISPLAY_NAME);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view), COL_PIXBUF);
    gtk_icon_view_set_columns(GTK_ICON_VIEW(icon_view), 4);
    gtk_label_set_text(GTK_LABEL(current_user_name), "Current user:fengtianba");
    g_timeout_add_seconds(1, (GSourceFunc)set_label_time, current_time);
    gtk_label_set_text(GTK_LABEL(network_speed), "Network Speed:100M");
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);
    int n = gtk_notebook_page_num(GTK_NOTEBOOK(notebook), icon_view);
    printf("n is %d\n", n);
    struct tm *time_ptr;
    time_t the_time;
    char *time_malloc;
    (void)time(&the_time);
    time_ptr = localtime(&the_time);
    time_malloc = malloc(sizeof(struct tm));
    memset(time_malloc, 0, sizeof(struct tm));
    sprintf(time_malloc, "%d/%d/%d/%d:%d:%d", 1900 + time_ptr->tm_year, time_ptr->tm_mon, time_ptr->tm_mday,
            time_ptr->tm_hour, time_ptr->tm_min, time_ptr->tm_sec);
    gtk_label_set_text(GTK_LABEL(current_time), time_malloc);
    
    
    //signal to connect to widget
    g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
    g_signal_connect(GTK_ICON_VIEW(icon_view), "item-activated", G_CALLBACK(icon_view_item_select), notebook);
    g_signal_connect(GTK_BUTTON(home_button), "clicked", G_CALLBACK(home_button_clicked), notebook);
    g_signal_connect(GTK_BUTTON(access_token_ok_button), "clicked", G_CALLBACK(access_token_ok_button_clicked), access_token_entry);
    //object unref
    g_object_unref(G_OBJECT(builder));    
    
    //show widget 
    gtk_widget_show_all(window);
  
    gtk_main();   
    
   
    
    
    
    int i = 100;
    char *decode_string;
    
    /*CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    decode_string = curl_easy_unescape(curl, ACCESS_TOKEN, 0, &i);
    printf("origin url: %s\n", ACCESS_TOKEN);
    printf("new    url: %s\n", decode_string);
    curl_easy_cleanup(curl);*/

    //puts("enter access token\n");
    //scanf("%s", accesstoken);
    //调用自己写的SDK
    xiaonei_gtk_get_blog_list(accesstoken);
    xiaonei_gtk_get_one_blog(accesstoken);
    xiaonei_gtk_create_one_blog(accesstoken);






    

    return (EXIT_SUCCESS);
}
gboolean set_label_time(gpointer userdata)
{
    GtkLabel *label = GTK_LABEL(userdata);
    struct tm *time_ptr;
    time_t the_time;
    char *time_malloc;
    (void)time(&the_time);
    time_ptr = localtime(&the_time);
    time_malloc = malloc(sizeof(struct tm) + 50);
    memset(time_malloc, 0, sizeof(struct tm) + 50);
    int real_mon = time_ptr->tm_mon;
    int real_day = time_ptr->tm_mday;
    int real_hour = time_ptr->tm_hour;
    int real_min = time_ptr->tm_min;
    int real_sec = time_ptr->tm_sec;
    char real_mon_string[5];
    char real_day_string[5];
    char real_hour_string[5];
    char real_min_string[5];
    char real_sec_string[5];
    if(real_mon < 10)
        sprintf(real_mon_string, "0%d", real_mon);
    else
        sprintf(real_mon_string, "%d", real_mon);
    if(real_day < 10)
        sprintf(real_day_string, "0%d", real_day);
    else
        sprintf(real_day_string, "%d", real_day);
    if(real_hour < 10)
        sprintf(real_hour_string, "0%d", real_hour);
    else
        sprintf(real_hour_string, "%d", real_hour);
    if(real_min < 10)
        sprintf(real_min_string, "0%d", real_min);
    else
        sprintf(real_min_string, "%d", real_min);
    if(real_sec < 10)
        sprintf(real_sec_string, "0%d", real_sec);
    else
        sprintf(real_sec_string, "%d", real_sec);
    g_sprintf(time_malloc, "%d/%s/%s/%s:%s:%s", 1900 + time_ptr->tm_year, real_mon_string, real_day_string,
            real_hour_string, real_min_string, real_sec_string);
    gtk_label_set_text(GTK_LABEL(label), time_malloc);
    free(time_malloc);
    return TRUE;
}
GtkTreeModel* create_model(void)
{
    GtkListStore *list_store;
    GdkPixbuf *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;
    GtkTreeIter iter;
    GError *err = NULL;
    char filename[20];
    int i = 1;
    char *icon_name[]={
        "Login",
        "album",
        "blog",
        "vipinfo",
        "evaluation",
        "share",
        "ubb",
        "notification"
    };   
        
    p1 = gdk_pixbuf_new_from_file("./sources/1.png", &err);
    p2 = gdk_pixbuf_new_from_file("./sources/2.png", &err);
    p3 = gdk_pixbuf_new_from_file("./sources/3.png", &err);
    p4 = gdk_pixbuf_new_from_file("./sources/4.png", &err);
    p5 = gdk_pixbuf_new_from_file("./sources/5.png", &err);
    p6 = gdk_pixbuf_new_from_file("./sources/6.png", &err);
    p7 = gdk_pixbuf_new_from_file("./sources/7.png", &err);
    p8 = gdk_pixbuf_new_from_file("./sources/8.png", &err);
    assert(err == NULL);
    list_store = gtk_list_store_new(NUM_COLS,
            G_TYPE_STRING, GDK_TYPE_PIXBUF);
    
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[0], COL_PIXBUF, p1, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[1], COL_PIXBUF, p2, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[2], COL_PIXBUF, p3, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[3], COL_PIXBUF, p4, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[4], COL_PIXBUF, p5, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[5], COL_PIXBUF, p6, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[6], COL_PIXBUF, p7, -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME,
            icon_name[7], COL_PIXBUF, p8, -1);
    
    return GTK_TREE_MODEL(list_store);
}
void icon_view_item_select(GtkIconView *icon_view, GtkTreePath *path, gpointer userdata)
{
    GtkTreeModel *model;
    GtkNotebook *notebook;
    GtkTreeIter iter; 
    notebook = GTK_NOTEBOOK(userdata);
    model = gtk_icon_view_get_model(icon_view);
    gtk_tree_model_get_iter(model, &iter, path);
    char *string;
    string = gtk_tree_model_get_string_from_iter(model, &iter);
    printf("current select string is %s\n", string);
    int n = atoi(string);
    if(n == 0)
    {
        gtk_notebook_set_current_page(notebook, n+1);
    }
    if(n == 1)
    {
        gtk_notebook_set_current_page(notebook, n+1);
    }
}
void home_button_clicked(GtkButton *button, gpointer userdata)
{
    GtkNotebook *notebook;
    notebook = GTK_NOTEBOOK(userdata);
    gtk_notebook_set_current_page(notebook, 0);
}
void access_token_ok_button_clicked(GtkButton *button, gpointer userdata)
{
    GtkEntry *entry =  GTK_ENTRY(userdata);
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    strncpy(accesstoken, gtk_entry_buffer_get_text(buffer), strlen(gtk_entry_buffer_get_text(buffer)));
    
}