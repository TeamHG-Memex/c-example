#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>
#include <regex.h>
#include <sys/types.h>

const char *URL_REGEX = "(http|https)://[%/0-9a-zA-Z\\.\?=&#@:]*";

struct MemWriteData {

    size_t size;
    char *memory;
};

typedef struct UrlResponses {
    char *url;
    char *response;
} url_responses;

typedef struct CrawlResult {
    char *seed;
    char *response;
} crawl_result;


static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userp);
char **regexme(char *_string, const char *reg_to_match, int reg_limit);
int free_regex_memory(char **matches_array, int reg_limit);
struct MemWriteData curl_exec(char *url);
int request_urls(char *urls[], int num_urls, url_responses *output_buffer);
