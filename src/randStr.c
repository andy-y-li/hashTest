/*
 * =====================================================================================
 *
 *       Filename:  randStr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/18 14:02:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andy (https://github.com/andy-y-li), andy_y_li@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include "randStr.h"

void get_rand_str(char *buf, int len)
{
    char *str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int lstr = strlen(str);
    int i;
    for (i = 0; i < len - 2; i++) {
        buf[i] = str[rand() % lstr];
    }
    buf[i++] = '\n';
    buf[i] = '\0';
}

int generate_rand_str(int len, int count, const char *file_name)
{
    srand((unsigned int)time((time_t *)NULL));
    FILE *fp = fopen(file_name, "w+");
    if (fp == NULL) {
        fprintf(stderr,"open file:%s Error:%s\n", file_name,strerror(errno));
        return -1;
    }
    for (int i = 0; i < count; i++) {
        char *s = (char *)malloc(len * sizeof(char));
        if (s == NULL) {
            fprintf(stderr, "malloc error\n");
            fclose(fp);
            return -1;
        }
        get_rand_str(s, len);
        if (strlen(s)) {
            fputs(s, fp);
        }
        free(s);
    }
    fclose(fp);
    return 0;
}

