/* 
 * File:   GetAccessToken.h
 * Author: fengtianba
 *
 * Created on February 13, 2014, 9:48 PM
 */

#ifndef GETACCESSTOKEN_H
#define	GETACCESSTOKEN_H
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

#define URL "https://graph.renren.com/oauth/authorize"
#define URLFILDS "client_id=2cc79d04e5264b928d4be870072ed56f&redirect_uri=http://graph.renren.com/oauth/login_success.html&response_type=token&scope=publish_blog"
#ifdef	__cplusplus
extern "C" {
#endif
    static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
    int GetAccessToken();




#ifdef	__cplusplus
}
#endif

#endif	/* GETACCESSTOKEN_H */

