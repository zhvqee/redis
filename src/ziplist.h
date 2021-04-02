/*
 * Copyright (c) 2009-2012, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ZIPLIST_H
#define _ZIPLIST_H

#define ZIPLIST_HEAD 0
#define ZIPLIST_TAIL 1

/* Each entry in the ziplist is either a string or an integer. */
/**
 * 压缩列表结构，可能是字符串或者数字
 */
typedef struct {
    /* When string is used, it is provided with the length (slen). */
    unsigned char *sval; // 字符串
    unsigned int slen; //字符串长度
    /* When integer is used, 'sval' is NULL, and lval holds the value. */
    long long lval; //整数
} ziplistEntry;

/**
 * 创建一个压缩列表，返回压缩列表指针
 * @return
 */
unsigned char *ziplistNew(void);


/**
 * 合并压缩列表
 * @param first
 * @param second
 * @return
 */
unsigned char *ziplistMerge(unsigned char **first, unsigned char **second);


/**
 *
 *  把字符串s 放入压缩列表
 * @param zl
 * @param s
 * @param slen
 * @param where
 * @return
 */
unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int slen, int where);

/**
 *
 *  index 位置的 数据
 * @param zl
 * @param index
 * @return
 */
unsigned char *ziplistIndex(unsigned char *zl, int index);


/**
 *
 * 后继结点
 * @param zl
 * @param p
 * @return
 */
unsigned char *ziplistNext(unsigned char *zl, unsigned char *p);

/**
 * 前驱节点
 * @param zl
 * @param p
 * @return
 */
unsigned char *ziplistPrev(unsigned char *zl, unsigned char *p);

/**
 * 获取
 * @param p
 * @param sval
 * @param slen
 * @param lval
 * @return
 */
unsigned int ziplistGet(unsigned char *p, unsigned char **sval, unsigned int *slen, long long *lval);

/**
 *  插入
 *
 * @param zl
 * @param p
 * @param s
 * @param slen
 * @return
 */
unsigned char *ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen);

/**
 *
 * 删除
 * @param zl
 * @param p
 * @return
 */
unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p);

/**
 *
 * 范围删除
 * @param zl
 * @param index
 * @param num
 * @return
 */
unsigned char *ziplistDeleteRange(unsigned char *zl, int index, unsigned int num);

/**
 * 替换
 * @param zl
 * @param p
 * @param s
 * @param slen
 * @return
 */
unsigned char *ziplistReplace(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen);

/**
 * 比较
 * @param p
 * @param s
 * @param slen
 * @return
 */
unsigned int ziplistCompare(unsigned char *p, unsigned char *s, unsigned int slen);


/**
 * 查找
 * @param zl
 * @param p
 * @param vstr
 * @param vlen
 * @param skip
 * @return
 */
unsigned char *ziplistFind(unsigned char *zl, unsigned char *p, unsigned char *vstr, unsigned int vlen, unsigned int skip);

/**
 *
 * 大小
 * @param zl
 * @return
 */
unsigned int ziplistLen(unsigned char *zl);
/**
 *
 *
 * @param zl
 * @return
 */
size_t ziplistBlobLen(unsigned char *zl);


void ziplistRepr(unsigned char *zl);
typedef int (*ziplistValidateEntryCB)(unsigned char* p, void* userdata);
int ziplistValidateIntegrity(unsigned char *zl, size_t size, int deep,
                             ziplistValidateEntryCB entry_cb, void *cb_userdata);
void ziplistRandomPair(unsigned char *zl, unsigned long total_count, ziplistEntry *key, ziplistEntry *val);
void ziplistRandomPairs(unsigned char *zl, unsigned int count, ziplistEntry *keys, ziplistEntry *vals);
unsigned int ziplistRandomPairsUnique(unsigned char *zl, unsigned int count, ziplistEntry *keys, ziplistEntry *vals);

#ifdef REDIS_TEST
int ziplistTest(int argc, char *argv[], int accurate);
#endif

#endif /* _ZIPLIST_H */
