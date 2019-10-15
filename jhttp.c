

#include <janet.h>
#include <stdlib.h>
#include <errno.h>

#include <curl/curl.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t write_mem(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;

  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

static Janet get(int argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Janet ret = janet_wrap_nil();

  const char* url = janet_getcstring(argv, 0);

  CURL *curl;
  CURLcode res;

  struct MemoryStruct chunk;

  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;            /* no data at this point */

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* check for errors */
    if(res != CURLE_OK) {
      janet_panicf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else {
      printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    }

    curl_easy_cleanup(curl);
    ret = janet_cstringv(chunk.memory);
    free(chunk.memory);
  }

  curl_global_cleanup();

  return ret;
}

static const JanetReg cfuns[] =
  {
   {"get", get, "(jhttp/get)\n\nhttp GET url"},
   {NULL, NULL, NULL}
  };

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "jhttp", cfuns);
}
