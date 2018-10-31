/*
 * =====================================================================================
 *
 *       Filename:  hashTest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/18 15:17:23
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
#include "randStr.h"
#include "hashFunction.h"


#define STRING_LEN 255
///one atom of the chain when build the hash table
struct AtomOfBucketChain {  
    unsigned char *pKey;  
    struct AtomOfBucketChain *pNext;   
};  
  
struct ChainOfHashTable {  
    unsigned int mHitCount;  
    unsigned int mEntryCount;  
    struct AtomOfBucketChain *pKeys;  
};  
 
struct HashTable {
	unsigned int mBucketLen;
	struct ChainOfHashTable *pTable;
};
 
unsigned int (*pHashFunc)(char *str);  
 
///choose which hash function to be used
void chooseHashFunc(char *pHashFuncName)  
{  
    if (0 == strcmp(pHashFuncName, "simple_hash"))  
        pHashFunc = simple_hash;  
    else if (0 == strcmp(pHashFuncName, "RS_hash"))  
        pHashFunc = RS_hash;  
    else if (0 == strcmp(pHashFuncName, "JS_hash"))  
        pHashFunc = JS_hash;  
    else if (0 == strcmp(pHashFuncName, "PJW_hash"))  
        pHashFunc = PJW_hash;  
    else if (0 == strcmp(pHashFuncName, "ELF_hash"))  
        pHashFunc = ELF_hash;  
    else if (0 == strcmp(pHashFuncName, "BKDR_hash"))  
        pHashFunc = BKDR_hash;  
    else if (0 == strcmp(pHashFuncName, "SDBM_hash"))  
        pHashFunc = SDBM_hash;  
    else if (0 == strcmp(pHashFuncName, "DJB_hash"))  
        pHashFunc = DJB_hash;  
    else if (0 == strcmp(pHashFuncName, "AP_hash"))  
        pHashFunc = AP_hash;  
   // else if (0 == strcmp(pHashFuncName, "CRC_hash"))  
   //     pHashFunc = CRC_hash;  
   else  
        pHashFunc = NULL;  
}  
 
///build the hash table
void buildHashTable(unsigned char *pKey, struct HashTable *pHashTable)  
{  
    unsigned int mHashValue = pHashFunc(pKey) % pHashTable->mBucketLen;  
    struct AtomOfBucketChain *p=NULL;  
  
    p = pHashTable->pTable[mHashValue].pKeys;  
    while(p) 
	{  
        if (0 == strcmp(pKey, p->pKey))  
		{
			break;
		}
        p = p->pNext;  
    }  
    if (p == NULL)  
    {  
        p = (struct AtomOfBucketChain *)malloc(sizeof(struct AtomOfBucketChain));  
        if (p == NULL)   
        {  
            printf("malloc in buildHashTable filled");  
            return ;///must have 'return',否则失败也不会停止。  
        }  
        p->pKey = strdup(pKey);  
        p->pNext = pHashTable->pTable[mHashValue].pKeys;  
        pHashTable->pTable[mHashValue].pKeys = p;  
        pHashTable->pTable[mHashValue].mEntryCount++;  
    }  
    pHashTable->pTable[mHashValue].mHitCount++;  
}  
 
///initial hash table
void hashTableInit(struct HashTable *pHashTable)  
{  
    unsigned int i;  
         
    if ((NULL == pHashTable) || (NULL==pHashTable->pTable))  
    {  
        printf("hashTableInit: malloc pHashTable or pTable failed");  
        return;  
    }  
    for (i = 0; i < pHashTable->mBucketLen; i++)  
    {  
        pHashTable->pTable[i].mHitCount=0;
		pHashTable->pTable[i].mEntryCount=0;
		pHashTable->pTable[i].pKeys=NULL;
    }  
}  
 
///free space hash table used 
void freeHashTable(struct HashTable *pHashTable)  
{  
    unsigned int i;  
    struct AtomOfBucketChain *pFront, *pBack;  
  
    if ((NULL == pHashTable) || (NULL==pHashTable->pTable))  
	{
		printf("hash table has been free");
		return;  
	}
        
	
    for (i = 0; i < pHashTable->mBucketLen; i++)  
    {  
        pFront = pHashTable->pTable[i].pKeys;  
        while(pFront)  
        {  
            pBack = pFront->pNext;  
            if (pFront->pKey) free(pFront->pKey);  
            free(pFront);  
            pFront = pBack;  
        }  
    }  
    free(pHashTable->pTable);  
}  
///显示统计结果
void showTestsResult(struct HashTable *pHashTable)  
{  
    int backet = 0, sum = 0;  
	unsigned i=0, max_link=0;
    int conflict_count = 0, hit_count = 0;  
    double avg_link, backet_usage;  
  
    for(i = 0; i < pHashTable->mBucketLen; i++)  
    {  
        if (pHashTable->pTable[i].mHitCount > 0)   
        {  
            backet++;  
            sum += pHashTable->pTable[i].mEntryCount;  
            if (pHashTable->pTable[i].mEntryCount > max_link)  
            {  
                max_link = pHashTable->pTable[i].mEntryCount;  
            }  
            if (pHashTable->pTable[i].mEntryCount > 1)  
            {  
                conflict_count++;  
            }  
            hit_count += pHashTable->pTable[i].mHitCount;  
        }  
    }  
  
    backet_usage = backet/1.0/pHashTable->mBucketLen * 100; 
    avg_link = sum/1.0/backet;  
  
    printf("bucket_len = %d\n", pHashTable->mBucketLen);   ///哈希表的桶的个数  
   /// printf("hash_call_count = %d/n", hash_call_count);	///建立hash表的字符串的个数
    printf("hit_count = %d\n", hit_count);					///建立hash表的不重复的元素的个数 
    printf("buket conflict count = %d\n", conflict_count);		///冲突的桶的个数
    printf("longest hash entry = %d\n", max_link);			///最长的链的长度
    printf("average hash entry length = %.2f\n", avg_link);  ///链表的平均长度
    printf("backet usage = %.2f%\n", backet_usage);			///hash table的桶的使用率
}
//
void usage()  
{  
    printf("Usage:  hash_func_name [backet_len]\n");  
    printf("hash_func_name:\n");  
    printf("\tsimple_hash\n");  
    printf("\tRS_hash\n");  
    printf("\tJS_hash\n");  
    printf("\tPJW_hash\n");  
    printf("\tELF_hash\n");  
    printf("\tBKDR_hash\n");  
    printf("\tSDBM_hash\n");  
    printf("\tDJB_hash\n");  
    printf("\tAP_hash\n");  
   // printf("/tCRC_hash\n");  
}  

int main(int argc, char *argv[])
{
     FILE *fp;
	int mStringCount=0;
	unsigned char  pKey[10];
	struct HashTable *pHashTable=NULL;
    usage();
	///参数输入
	char hashfunctionname[10],bucketcount[10];
	printf("input hashfunctionname\n");
	gets(hashfunctionname);
	printf("input bucketcount\n");
	gets(bucketcount);

	pHashTable=(struct HashTable*)malloc(sizeof(struct HashTable));
	if(NULL==pHashTable)
	{
		printf("malloc hash table filled");
		return -1;
	}
 /*
	if (argc<=1)
    {
        usage();
		return -1;
    }

	if (2==argc)
    {
        usage();
    }
	*/
//	pHashTable->mBucketLen = atoi(argv[1]);
	pHashTable->mBucketLen = atoi(bucketcount);
	pHashTable->pTable=(struct ChainOfHashTable*)malloc(sizeof(struct ChainOfHashTable) * pHashTable->mBucketLen);

    if (!(fp = fopen("test.txt", "r")))  ///假设文件已经生成，需要补充自动生成字符串的函数。将生成的字符串保存在一个文件中。
    {
        printf("open source file filled");
		return -1;
    }

	hashTableInit(pHashTable);
    //chooseHashFunc(argv[0]);
	chooseHashFunc(hashfunctionname);

    while(fgets(pKey,10,fp)!=NULL)//逐行读取fp1所指向文件中的内容到text中
    {

        mStringCount++;
		buildHashTable(pKey,pHashTable);
    }
    fclose(fp);

    showTestsResult(pHashTable);
	printf("String Count: %d\n",mStringCount);	///建立hash表的字符串的个数
    freeHashTable(pHashTable);

    return 0;
}
