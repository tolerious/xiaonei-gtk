#include "GetAccessToken.h"
int GetAccessToken()
    {
        CURL *curl;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        FILE *filename;
        filename = fopen("result.html","w");
        curl_easy_setopt(curl,CURLOPT_URL,URL);
        curl_easy_setopt(curl,CURLOPT_POST,1L);
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,URLFILDS);
        curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1);
        curl_easy_setopt(curl,CURLOPT_VERBOSE,0L);
        curl_easy_setopt(curl,CURLOPT_HEADER,0L);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,filename);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        fclose(filename);
        return 0;
    }
static size_t write_data(char *ptr,size_t size,size_t nmemb,void *userdata)
    {
        FILE *file = (FILE*)userdata;
        return fwrite(ptr,size,nmemb,file);
    }
