/*
 * buf.c
 *
 *  Created on: Jan 6, 2017
 *      Author: User
 *      a sized buffer type
 */

#include <stdlib.h>
#include <string.h>
#include "buf.h"

buf_t *buf_size_jsmn(buf_t *buf, size_t len)
{
    if (buf == NULL)
    {
        buf = malloc(sizeof(buf_t));
        if(buf == NULL)
            CLI_Write("cannot allocate buffer");
        buf->data = NULL;
        buf->len = 0;
    }
    buf->data = realloc(buf->data, len);
    if (buf == NULL)
        CLI_Write("cannot allocate buffer");

    if (buf->len > len)
        buf->len = len;
    buf->limit = len;

    return buf;
}

void buf_push (buf_t *buf, uint8_t c)
{
    if (buf == NULL)
        CLI_Write("cannot allocate buffer");

    buf->data[buf->len++] = c;
}

void buf_concat(buf_t *dst, uint8_t *src, size_t len)
{
    if (dst == NULL)
        CLI_Write("cannot allocate memory to destination");
    if (src == NULL)
        CLI_Write("cannot allocate memory to source");
    size_t i;
    for(i = 0; i < len; i++)
        dst->data[dst->len++] = src[i];
}
char *buf_tostr(buf_t *buf)
{
    if (buf == NULL)
        CLI_Write("cannot allocate buffer");
    char *str = malloc(buf->len + 1);
    if (str == NULL)
        CLI_Write("cannot allocate memory to string");
    memcpy(str, buf->data, buf->len);
    str[buf->len] = '\0';

    return str;
}


