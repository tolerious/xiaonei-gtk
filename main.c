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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}

