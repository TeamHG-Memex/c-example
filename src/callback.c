#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "basic_curl.h"
#include "dbg.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userp) {

    printf("I'm in write_callback");
    size_t segsize = size * nmemb;

    struct MemWriteData *mem_struct = (struct MemWriteData *) userp;    

    mem_struct->size = mem_struct->size + segsize;
    mem_struct->memory = realloc(mem_struct->memory, mem_struct->size + 1);
    if (mem_struct->memory == NULL){
	printf("Sorry not enough memory to allocate chumpo.");
	return 1;
    }

    int next_empty_index = mem_struct->memory[mem_struct->size];
    printf("I'm here in write callback now, right before memcpy.");
    mem_struct->memory = memcpy(&(next_empty_index), ptr, segsize);
    printf("Here I am after write callback memcpy.");
    mem_struct->memory[mem_struct->size] = 0;

    return segsize;
}
