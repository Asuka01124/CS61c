/* Include the system headers we need */
/* 包含程序需要的系统头文件。 */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
/* 包含我们自己写的头文件。 */
#include "ex7_vector.h"

/* Define what our struct is */
/* 定义 vector_t 结构体内部长什么样。 */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
/* 处理内存分配失败的辅助函数。
   这里会打印错误信息并退出程序。 */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
/* 创建新 vector 的错误示例。 */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    /* 创建一个 vector 变量以及指向它的指针。 */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    /* 初始化字段。 */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/* Create a new vector with a size (length) of 1 and set its single component to zero... the
   right way */
/* 以正确方式创建一个长度为 1 的新 vector，并把唯一的元素设为 0。 */
vector_t *vector_new() {
    /* Declare what this function will return */
    /* 声明这个函数最终要返回的指针。 */
    vector_t *retval;
    /* First, we need to allocate memory on the heap for the struct */
    /* 首先，需要在堆上为结构体本身分配内存。 */
    retval = malloc(sizeof(vector_t));/* YOUR CODE HERE */

    /* Check our return value to make sure we got memory */
    /* 检查返回值，确认内存分配成功。 */
    if (retval == NULL) {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    /* 接下来初始化 data。
       因为 retval->data 之后需要能动态增长，
       这里应该做什么？ */
    retval->size = 1;
    retval->data = malloc(sizeof(int));

    /* Check the data attribute of our vector to make sure we got memory */
    /* 检查 vector 的 data 字段，确认它也成功分配到了内存。 */
    if (retval->data == NULL) {
        free(retval);				//Why is this line necessary?
        // 为什么这一行是必要的？
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    /* 把唯一的元素设为 0，完成初始化。 */
    retval->data[0] = 0;
    /* and return... */
    /* 最后返回新建的 vector。 */
    return retval; /* UPDATE RETURN VALUE */
}

/* Return the value at the specified location/component "loc" of the vector */
/* 返回 vector 中指定位置 loc 处的值。 */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    /* 如果传入的是 NULL vector，就打印错误并终止程序。 */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    /* 如果请求的位置超出了已分配范围，就返回 0。
     * 否则，返回该位置中保存的值。
     */
    if (loc >= v->size) return 0;
    return v->data[loc];
    return 0;
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
/* 释放传入 vector 占用的内存。
   记住：所有曾经分配过的内存都需要释放。 */
void vector_delete(vector_t *v) {
    /* YOUR CODE HERE */
    free(v->data);
    free(v);
}

/* Set a value in the vector, allocating additional memory if necessary. 
   If the extra memory allocation fails, call allocation_failed(). */
/* 设置 vector 中某个位置的值；必要时分配额外内存。
   如果额外内存分配失败，就调用 allocation_failed()。 */
void vector_set(vector_t *v, size_t loc, int value) {
    if (loc >= v->size) {
        v->data = realloc(v->data, (loc + 1) * sizeof(int));
        if (v->data == NULL) {
            allocation_failed();
        }
        for (int i = v->size; i < loc; i++) {
            v->data[i] = 0;
        }
        v->size = loc + 1;
    }
    v->data[loc] = value;
}
