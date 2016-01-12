#include "basic_curl.h"

//returns an array of strings
//the free_regex_memory should be called when regex results are no longer
//needed
char **regexme(char *_string, const char *reg_to_match, int reg_limit) {

    regex_t preg;
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int comp_ret;
    int match;
    int start;
    int end = 0;
    int match_len;
    int i;
    int string_offset = 0;

    //char **matches = (char **) malloc(sizeof(char *) * reg_limit);

    void **matches = malloc(sizeof(char *) * reg_limit);
    memset( matches, 0, sizeof(char *) * reg_limit );
    
    for (i=0; i < reg_limit; i++) {

	comp_ret = regcomp(&preg, reg_to_match, REG_ICASE|REG_EXTENDED);
	match = regexec(&preg, &_string[string_offset], nmatch, pmatch, 0);
	
	if (match == 1) {
	    puts("No more matches found, rest of the loop will be filled with NULLs");
	    break;
	}

	else if (match == 0 ) {
	    start = pmatch[0].rm_so;
	    end = pmatch[0].rm_eo;

	    string_offset += end;
	    match_len = end - start;
	    printf("%.*s\n", match_len, &_string[string_offset - match_len]);

	    //use malloc to find the length and use that instead of limiting array initially
	    //http://stackoverflow.com/questions/33003196/cant-copy-string-to-an-array-of-strings-in-c
	    matches[i] = malloc(sizeof(char) * (match_len + 1));
	    sprintf(matches[i], "%.*s" , match_len, &_string[string_offset - match_len]);		
	}
    }

    return matches;
}

int free_regex_memory(char **matches_array, int reg_limit) {

    int i = 0;
    while (matches_array[i] != NULL && i < reg_limit) {
    	free(matches_array[i]);
	i++;
    }

    free(matches_array);

    return 0;
}

/*
int main() {

    char **matches;
    int i =0;

    matches = regexme("0fff 1fc<a href=\"https://www.blahblahblah.com/whatever.php?xxx=r\" keaw 2eafa", 
		      "(http|https)://[%/0-9a-zA-Z\\.\?=&#@:]*",
		      10);

    //puts(matches[1]);

    while (matches[i] != NULL) {
    	puts(matches[i]);
    	i++;
    }

    free_regex_memory(matches, 10);

    return 0;
}
*/
