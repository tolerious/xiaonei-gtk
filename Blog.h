/* 
 * File:   Blog.h
 * Author: fenghelong
 *
 * Created on 2014年3月6日, 下午3:48
 */

#ifndef BLOG_H
#define	BLOG_H
#include <glib.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AccessToken.h"
#define URL "https://api.renren.com/v2/blog/list"
#define POST_URL "https://api.renren.com/v2/blog/put"
#define GET_URL "https://api.renren.com/v2/blog/get"
#ifdef	__cplusplus
extern "C" {
#endif
    static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
    void xiaonei_gtk_get_blog_list(char *access_token);
    void xiaonei_gtk_create_one_blog(char *access_token, char *permision, char *title, char *content, char *password);
    void xiaonei_gtk_get_one_blog(char *access_token);


#ifdef	__cplusplus
}
#endif

#endif	/* BLOG_H */

