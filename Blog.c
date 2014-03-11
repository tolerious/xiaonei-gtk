#include "Blog.h"

void xiaonei_gtk_get_blog_list(char *access_token)
{
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    FILE *filename = NULL;
    filename = fopen("blog_info.json", "w");
    char str[500];
    sprintf(str, URL"?access_token=%s&ownerId=%d&pageSize=%d&pageNumber=%d",access_token,
            269787992, 15, 1);
    puts(str);
    curl_easy_setopt(curl, CURLOPT_URL, str);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, filename);
    //fclose(filename);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
void xiaonei_gtk_create_one_blog(char *access_token, char *title, char *content)
{
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    char str[500];
    //char *ptr;
    sprintf(str,"access_token=%s&title=%s&accessControl=%s&password=%s&content=%s",
            access_token, "FUCK ZHONG BING DU LE !!!", "PUBLIC", "", "ni hao hello");
    puts(str);
    //ptr = curl_easy_escape(curl, str, strlen(str));
    curl_easy_setopt(curl, CURLOPT_URL, POST_URL);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
    
    //printf("ptr is %s", ptr); 
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *file = (FILE*)userdata;
    puts("write data function running...");
    return fwrite(ptr, size, nmemb, file);
}
void xiaonei_gtk_get_one_blog(char *access_token)
{
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    FILE *filename = NULL;
    filename = fopen("person_one_blog", "w");
    char str[500];
    sprintf(str, GET_URL"?access_token=%s&ownerId=%s&blogId=%s&password=%s",
            access_token, "252633228", "923139078", "");
    puts(str);
    curl_easy_setopt(curl, CURLOPT_URL, str);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, filename);
    //fclose(filename);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}