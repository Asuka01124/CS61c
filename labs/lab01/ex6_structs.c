#include <stdio.h>
#include <stdlib.h>

// Structs allow you to hold data items of different types in a single variable
// Struct definitions can be used to declare a struct variable within your program
// Struct definitions are typically done outside of a function
// 结构体可以把不同类型的数据项放在同一个变量里。
// 定义好结构体之后，就可以在程序中声明这种结构体类型的变量。
// 结构体定义通常写在函数外面，方便多个函数共同使用。
struct Student {
    // 学生编号。
    int id;
    // 学生姓名；char* 表示指向字符的指针，常用于字符串。
    char* name;
};

int main() {
  // TODO: declare a variable student of type struct Student
  // Note: this struct is stored on the stack
  // TODO: 声明一个类型为 struct Student 的变量 student。
  // 注意：这个结构体变量会存放在栈上。
  struct Student student;

  // TODO: print out the size of a struct Student
  // While this may seem out of place now, it will be useful in the future!
  // Hint: there's an operator that can calculate this for you!
  // TODO: 打印 struct Student 的大小。
  // 虽然现在看起来有点突兀，但之后会很有用。
  // 提示：C 里有一个运算符可以帮你计算大小。
  printf("Size of a struct Student: %lu bytes\n", sizeof(struct Student));

  // TODO: set student's id field to 5
  // Hint: the dot notation accesses a struct's fields
  // TODO: 把 student 的 id 字段设为 5。
  // 提示：点号可以访问结构体的字段。
  student.id = 5;

  // TODO: print out student's id field
  // TODO: 打印 student 的 id 字段。
  printf("Student's ID: %d\n", student.id);

  // main 返回 0 表示程序正常结束。
  return 0;
}
