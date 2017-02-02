/*
 * buf.h
 *
 *  Created on: Jan 6, 2017
 *      Author: User
 */
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct{
    size_t len;         //current length of buffer (used bytes)
    size_t limit;       //maximum length of buffer (allocated)
    uint8_t *data;      //insert bytes here
} buf_t;

buf_t *buf_size_jsmn(buf_t *buf, size_t len);
void buf_push(buf_t *buf, uint8_t c);
void buf_concat(buf_t *buf, uint8_t *data, size_t len);
char * buf_tostr(buf_t *buf);
