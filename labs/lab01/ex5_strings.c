#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // TODO: Create space to store the string "hello"
  // Hint: how many bytes do we need to store this string?
  // TODO: 创建空间来保存字符串 "hello"。
  // 提示：保存这个字符串一共需要多少个字节？
  char hello_str[6];

  // TODO: store the characters one at a time
  // Hint: don't forget the null terminator
  // Note: we use single quotes for characters
  // TODO: 一次存入一个字符。
  // 提示：不要忘记字符串结尾的空字符。
  // 注意：单个字符要用单引号。
  hello_str[0] = 'h';
  hello_str[1] = 'e';
  hello_str[2] = 'l';
  hello_str[3] = 'l';
  hello_str[4] = 'o';
  hello_str[5] = '\0';

  // TODO: store the null terminator
  // TODO: 存入字符串结尾的空字符 '\0'。
char *ptr_to_hello = &hello_str[5];

  // Prints hello_str
  // 打印 hello_str。
  printf("prints hello: %s\n", hello_str);

  // TODO: print the length of hello_str
  // TODO: 打印 hello_str 的长度。
  printf("length of hello: %lu\n", strlen(hello_str));

  // TODO: create space to store the string "world"
  // TODO: 创建空间来保存字符串 "world"。
  char world_str[6];

  // TODO: fill in the type
  // Note: this automatically stores the string "world" in static memory
  //       but static memory is immutable, so you may need to copy it
  //       to the stack or the heap
  // TODO: 填写正确的类型。
  // 注意：字符串字面量 "world" 会自动存放在静态内存中。
  //       静态内存里的字符串不可修改，所以可能需要把它复制到栈或堆上。
  const char *static_world_str = "world";

  // TODO: use strcpy and static_world_str to store "world" into world_str
  // Hint: strcpy takes two arguments:
  //       first the destination, then the source
  // TODO: 使用 strcpy 和 static_world_str，把 "world" 存入 world_str。
  // 提示：strcpy 接收两个参数：第一个是目标地址，第二个是源地址。
  strcpy(world_str, static_world_str);

  // Prints world_str
  // 打印 world_str。
  printf("prints world: %s\n", world_str);

  // Prints the address of world_str
  // 打印 world_str 的起始地址。
  printf("address of world_str: %p\n", world_str);

  // TODO: compute the address of the letter r using world_str
  // TODO: 使用 world_str 计算字母 'r' 的地址。
  char *ptr_to_r = &world_str[1];
  printf("address of 'r': %p\n", ptr_to_r);

  // TODO: create space to store the string "hello world"
  // TODO: 创建空间来保存字符串 "hello world"。
  char hello_world_str[12];

  // TODO: use strcpy and hello_str to store
  //       the string "hello" into hello_world_str
  // TODO: 使用 strcpy 和 hello_str，把字符串 "hello" 存入 hello_world_str。
  strcpy(hello_world_str, hello_str);

  // TODO: store the space character in "hello world" at the correct index
  // Note: a space is not the same as null terminator
  //       a null terminator is represented by '\0'
  // TODO: 在 "hello world" 的正确下标处存入空格字符。
  // 注意：空格字符和字符串结尾的空字符不同。
  //       空字符写作 '\0'。
  hello_world_str[5] = ' ';

  // TODO: use strcpy, pointer arithmetic, and world_str to store
  //       the string "world" into hello_world_str
  // TODO: 使用 strcpy、指针算术和 world_str，把 "world" 存入 hello_world_str。
  strcpy(hello_world_str + 6, world_str);

  // Prints hello_world_str
  // 打印 hello_world_str。
  printf("prints hello world: %s\n", hello_world_str);

  // main 返回 0 表示程序正常结束。
  return 0;
}
