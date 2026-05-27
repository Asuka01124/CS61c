#include <stdio.h>

// 这里的 input 是传值传入的副本，修改它不会影响 main 里的 x。
void add_one(int input) {
  input += 1;
}

// TODO: create a pointer to input
// TODO: 创建一个指向 input 的指针参数。
void add_one_pointer(int *input) {
  // TODO: add one to the integer that input points to
  // TODO: 给 input 指向的整数加 1。
  *input += 1;
}

// TODO: create a pointer to a pointer to input
// TODO: 创建一个“指向指针”的参数，也就是二级指针。
void add_one_double_ptr(int **input) {
  // TODO: add one to the integer that input doubly points to
  // TODO: 给 input 间接指向两次后得到的整数加 1。
  **input += 1;
}

int main() {
  // Assign x (an integer) to 5
  // 创建整数 x，并把它初始化为 5。
  int x = 5;

  // Call add_one on x
  // 调用 add_one，把 x 的值复制一份传进去。
  add_one(x);

  // This line should print 5
  // Why doesn't this work?
  // 这里会打印 5：因为 add_one 改的是参数副本，不是原来的 x。
  printf("add_one: %d\n", x);

  // Let's try using add_one_pointer
  // 接下来尝试用指针直接修改 x。

  // TODO: use add_one_pointer to increment x
  // Hint: compare the type of x with the type of the argument
  //       for add_one_pointer
  // TODO: 调用 add_one_pointer 来让 x 加 1。
  // 提示：比较 x 的类型和 add_one_pointer 参数需要的类型。
  add_one_pointer(&x);

  // This line should print 6
  // 这里应该打印 6。
  printf("add_one_pointer: %d\n", x);
  
  // TODO: Let's save the pointer to x in y
  // TODO: 把指向 x 的指针保存到 y 中。
  int *y = &x;

  // TODO: use add_one_double_ptr to increment x again, using the pointer we just made
  // TODO: 使用刚刚创建的指针 y，通过 add_one_double_ptr 再让 x 加 1。
  add_one_double_ptr(&y);

  // This line should print 7
  // 这里应该打印 7。
  printf("add_one_double_ptr: %d\n", x);

  // main 返回 0 表示程序正常结束。
  return 0;
}
