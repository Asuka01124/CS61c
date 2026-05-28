#ifndef CS61C_VECTOR_H_
#define CS61C_VECTOR_H_
/* vector.h originally written by Jeremy Huddleston <jeremyhu@eecs.berkeley.edu> Sp2004
 *
 * So it looks like you've decided to venture into the "other" files of this
 * lab.  Good.  C Header files (the .h extension) are a way of telling other .c
 * files what they can have access to.  You usually include stdlib.h in your
 * C programs, and this process is identical to including this .h file with the
 * one change being:
 *
 * #include "file.h" 
 * versus
 * #include <file.h>
 *	 
 * The difference is that the <> notation is for system header files and the ""
 * is for ones you provide yourself (in your local directory for instance).
 *	 
 * The header file starts off with
 * #ifndef CS61C_VECTOR_H_
 * #define CS61C_VECTOR_H_
 *	 
 * and ends with a final #endif.  This prevents the file from being included
 * more than once which could've possibly resulted in an infinite loop of
 * file inclusions.
 *
 * First, we define the 'vector_t' datatype.  This next line says that a 'vector_t'
 * is the same as a 'struct vector_t'.  So anywhere in the code after this, we
 * can use 'vector_t *' to mean a pointer to a 'struct vector_t' (which is defined in
 * vector.c).  We can get away with doing this even though we don't know what a
 * struct vector is because all struct pointers have the same representation in memory.
 */
/* vector.h 最初由 Jeremy Huddleston <jeremyhu@eecs.berkeley.edu> 于 2004 年春季编写。
 *
 * 看起来你决定探索本 lab 里的“其他”文件了。很好。C 头文件（扩展名 .h）
 * 是一种告诉其他 .c 文件“它们可以访问什么”的方式。你平时会在 C 程序中
 * include stdlib.h；include 这个 .h 文件的过程也一样，只是写法有一点不同：
 *
 * #include "file.h"
 * 对比
 * #include <file.h>
 *
 * 区别是：尖括号 <> 用于系统头文件，双引号 "" 用于你自己提供的头文件
 * （比如当前本地目录里的文件）。
 *
 * 头文件开头有
 * #ifndef CS61C_VECTOR_H_
 * #define CS61C_VECTOR_H_
 *
 * 最后以 #endif 结束。这样可以防止同一个文件被 include 多次，
 * 否则有可能导致文件互相包含的无限循环。
 *
 * 首先，我们定义 'vector_t' 数据类型。下一行表示 'vector_t' 等价于
 * 'struct vector_t'。因此在这之后的代码里，'vector_t *' 就表示指向
 * 'struct vector_t' 的指针（真正的结构体定义在 vector.c 里）。虽然这里还
 * 不知道 struct vector 的具体内容，但这样做是可以的，因为所有结构体指针
 * 在内存中的表示方式都一样。
 */

#include <sys/types.h>

typedef struct vector_t vector_t;

/*
 *  Next, we provide the prototypes for the functions defined in vector.c.  This
 *  is a way of telling the .c files that #include this header what they will
 *  have access to.
 */
/*
 * 接下来，我们提供 vector.c 中定义的函数原型。
 * 这相当于告诉 include 这个头文件的 .c 文件：它们可以使用哪些函数。
 */

/* Create a new vector */
/* 创建一个新的 vector。 */
vector_t *vector_new();

/* Free up the memory allocated for the passed vector */
/* 释放传入 vector 占用的内存。 */
void vector_delete(vector_t *v);

/* Return the value in the vector */
/* 返回 vector 中某个位置的值。 */
int vector_get(vector_t *v, size_t loc);

/* Set a value in the vector */
/* 设置 vector 中某个位置的值。 */
void vector_set(vector_t *v, size_t loc, int value);

#endif
