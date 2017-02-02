/*
 * json.h
 *
 *  Created on: Jan 5, 2017
 *      Author: User
 */
#include <stddef.h>
#include <stdbool.h>
#include "jsmn.h"

bool json_token_streq(char *js, jsmntok_t *t, char *s);
char * json_token_tostr(unsigned char *js, jsmntok_t *t);
jsmntok_t * json_tokenise(char *js);
