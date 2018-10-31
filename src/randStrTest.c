/*
 * =====================================================================================
 *
 *       Filename:  randStrTest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/31/18 16:09:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andy (https://github.com/andy-y-li), andy_y_li@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "randStr.h"

int main(int argc, char *argv[])
{
    generate_rand_str(10, 1000, "test.txt");
    return 0;
}

