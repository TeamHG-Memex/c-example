#include "headers/basic_curl.h"



/*
int process_matches(**matches, char *seed, url_responses *url_resps) {

    while(match != NULL) {



    }

    num_matches = 

    struct crawl_results[] = malloc(sizeof(crawl_result));
}
*/

int process_responses(url_responses responses, int num_url_responses) {

    static int malloc_size = 0;
    malloc_size += sizeof(responses) * num_url_responses;
    static url_responses *all_url_responses = realloc(malloc_size);
    

    return url_responses;
}

int crawl(char **seeds, int num_urls, int link_cap, int depth) {

    url_responses buff[num_urls];
    char **matches;
    const char *URL_REGEX = "(http|https)://[%/0-9a-zA-Z\\.\?=&#@:]*";
    int extractions_cap = 10;
    url_responses url_responses_buff[num_urls];
    char *seeds[num_urls];
    //seeds[0] = "http://www.hyperiongray.com/";
    //seeds[1] = "http://stackoverflow.com/questions/15686890/how-to-allocate-array-of-pointers-for-strings-by-malloc-in-c";

    request_urls(urls, num_urls, url_responses_buff);

    for (i =0; i < num_urls; i++) {
        matches = regexme(url_responses_buff[i].response, URL_REGEX, link_cap);
    }

    return 0;
}

int main() {

    char *seeds = 
    
    crawl()
}
