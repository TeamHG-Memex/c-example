#include "basic_curl.h"
#include "dbg.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userp) {

    //printf("I'm in write_callback");
    size_t segsize = size * nmemb;
    struct MemWriteData *mem_struct = (struct MemWriteData *) userp;

    mem_struct->memory = realloc(mem_struct->memory, mem_struct->size + segsize + 1);
    if (mem_struct->memory == NULL){
	printf("Sorry not enough memory to allocate chumpo.");
	return 0;
    }

    //printf("I'm here in write callback now, right before memcpy.");
    memcpy(&(mem_struct->memory[mem_struct->size]), ptr, segsize);
    //printf("Here I am after write callback memcpy.");

    mem_struct->size = mem_struct->size + segsize;
    mem_struct->memory[mem_struct->size] = 0;

    return segsize;
}

struct MemWriteData curl_exec(char *url) {

    CURL *curl;
    CURLcode res;
    struct MemWriteData chunk;
    
    char *init_mem = malloc(1);
    size_t init_size = 0;

    chunk.memory = init_mem;
    chunk.size = init_size;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
      printf("Got curl handle\n");
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
      curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
	  fprintf(stderr, "failed because: %s\n", curl_easy_strerror(res));
      }
      else {
	  printf("%lu bytes retrieved\n", (long)chunk.size);
      }
    }

    curl_easy_cleanup(curl);
    //free(chunk.memory);
    curl_global_cleanup();

    return chunk;
}

//this returns address of local variable, will be cleared off stack once function finishes, shit
//this is why the user needs to pass a buffer OR
//I need to use malloc to store this in the heap and provide a free function
//these are the two options that C interfaces use, makes a lot more sense now...
//OK figured this out... pretty easy, trust user to pass in proper num_urls
//instead of buffer size (which is more typical AFAIK).
int request_urls(char *urls[], int num_urls, url_responses *output_buffer) {

    url_responses urs[num_urls];
    char *url;
    int i;

    struct MemWriteData curl_raw_response;
    for (i=0; i < num_urls; i++) {
	url = urls[i];
	curl_raw_response = curl_exec(url);
	urs[i].response = curl_raw_response.memory;
	urs[i].url = url;
	output_buffer[i] = urs[i];
    }
    
    //puts(urs[0].response);

    //
    return 0;
}

/*
int main() {

    int num_urls = 2;
    url_responses buff[num_urls];
    char *urls[num_urls];
    urls[0] = "http://www.hyperiongray.com";
    urls[1] = "http://ctips.pbworks.com/w/page/7277635/TempReturnBuffer";	

    request_urls(urls, 2, buff);

    puts(buff[1].url);

    return 0;
}
*/
