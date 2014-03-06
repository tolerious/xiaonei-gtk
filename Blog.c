#include "Blog.h"
GList* xiaonei_gtk_get_blog_list(char *access_token)
{
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    FILE *filename = NULL;
    filename = fopen("blog.json", "w");
    char str[500];
    sprintf(str, URL"?access_token=%s&ownerld=%d&pageSize=%d&pageNumber=%d",access_token,
            269787992, 15, 1);
    puts(str);
    curl_easy_setopt(curl, CURLOPT_URL, str);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
void xiaonei_gtk_create_one_blog(char *access_token)
{
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    char str[500];
    char *ptr;
    sprintf(str,"access_token=%s&title=%s&accessControl=%s&password=%s&content=%s",
            access_token, "FUCK ZHONG BING DU LE !!!", "PRIVATE", "111111", "ni hao hello");
    puts(str);
    ptr = curl_easy_escape(curl, str, strlen(str));
    curl_easy_setopt(curl, CURLOPT_URL, POST_URL);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
    
    printf("ptr is %s", ptr); 
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}