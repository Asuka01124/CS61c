#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Creates an integer with value 5
  // Note: int8_t is a numerical datatype that takes up 1 byte of memory
  // 创建一个值为 5 的整数。
  // 注意：int8_t 是占用 1 字节内存的整数类型。
  int8_t x = 5;

  // TODO: create an int8_t array of size 4
  // TODO: 创建一个长度为 4 的 int8_t 数组。
  int8_t some_array[4];
  printf("address of the start of the array: %p\n", some_array);

  // TODO: compute the address of the element at index 2 (0-indexed)
  // TODO: 计算下标为 2 的元素地址，数组下标从 0 开始。
  int8_t *ptr_to_idx_2 = &some_array[2];
  printf("address of index 2: %p\n", ptr_to_idx_2);

  // TODO: store the value 10 at index 2, using ptr_to_idx_2
  // TODO: 使用 ptr_to_idx_2，把值 10 存到下标 2 的位置。
  *ptr_to_idx_2 = 10;

  // TODO: print the value at index 2
  // Hint: this blank should be the same as the previous blank
  //       please don't hard code 10
  // TODO: 打印下标 2 处的值。
  // 提示：这里的填空应和上一处相同，不要直接写死 10。
  printf("value at index 2: %d\n", *ptr_to_idx_2);

  // main 返回 0 表示程序正常结束。
  return 0;
}
