/*
 * json.c
 *
 *  Created on: Jan 5, 2017
 *      Author: User
 */
#include <stdlib.h>
#include "json.h"
#include "buf.h"

#define BUFFER_SIZE 32768
#define JSON_TOKENS 256

jsmntok_t * json_tokenise(char *js)
{
    jsmntok_t *tokens;
    jsmn_parser parser;

    jsmn_init(&parser);
//    unsigned int n = JSON_TOKENS;
//    tokens = (jsmntok_t *)malloc(sizeof(jsmntok_t) * n);
    //temp implement only 10 tokens
    unsigned int n = 10;
    tokens = (jsmntok_t *)malloc(sizeof(jsmntok_t) * n);
    if(tokens == NULL)
        CLI_Write("couldn't allocate memory for tokens");

    int ret = jsmn_parse(&parser, js, tokens, n);

    while(ret == JSMN_ERROR_NOMEM)
    {
        n = n * 2 + 1;
        tokens = realloc(tokens, sizeof(jsmntok_t) *n);
        if(tokens == NULL)
            CLI_Write("couldn't allocate memory for tokens");

        ret = jsmn_parse(&parser, js, tokens, n);
    }
    if(ret == JSMN_ERROR_INVAL)
        CLI_Write("jsmn_parse invalid string");
    if(ret == JSMN_ERROR_PART)
        CLI_Write("jsmn_parse truncated JSON string");

    return tokens;
}

bool json_token_streq(char *js, jsmntok_t *t, char *s)
{
    return (strncmp(js + t->start, s, t->end - t->start) == 0
            && strlen(s) == (size_t) (t->end - t->start));
}

char * json_token_tostr(unsigned char *js, jsmntok_t *t)
{
    js[t->end] = '\0';
    return js + t->start;
}

