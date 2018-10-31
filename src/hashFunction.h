/*
 * =====================================================================================
 *
 *       Filename:  hashFunction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/18 15:08:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andy (https://github.com/andy-y-li), andy_y_li@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

/* A Simple Hash Function */  
unsigned int simple_hash(char *str);

/* RS Hash Function */
unsigned int RS_hash(char *str);

/* JS Hash Function */
unsigned int JS_hash(char *str);

/* P. J. Weinberger Hash Function */
unsigned int PJW_hash(char *str);

/* ELF Hash Function */
unsigned int ELF_hash(char *str);

/* BKDR Hash Function */
unsigned int BKDR_hash(char *str);

/* SDBM Hash Function */
unsigned int SDBM_hash(char *str);

/* DJB Hash Function */
unsigned int DJB_hash(char *str);

/* AP Hash Function */
unsigned int AP_hash(char *str);



#endif

