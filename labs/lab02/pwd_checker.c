#include <string.h>
#include "pwd_checker.h"

/*
Password checker

Requirements:
- Password must be at least 10 characters
- Password must contain at least
    - 1 upper case letter
    - 1 lower case letter
    - 1 number
- Password cannot contain the person's first name or last name (case sensitive)

For the simplicity of this exercise:
- This is not the most efficient way to implement this program
- These functions do not perform any error checking
- You can assume that the first and last name will never be the empty string
*/
/*
密码检查器

要求：
- 密码长度至少为 10 个字符
- 密码必须至少包含
    - 1 个大写字母
    - 1 个小写字母
    - 1 个数字
- 密码不能包含用户的名或姓（区分大小写）

为了简化本练习：
- 这不是实现该程序最高效的方式
- 这些函数不做任何错误检查
- 可以假设名和姓永远不会是空字符串
*/

/* Returns true if the length of PASSWORD is at least 10, false otherwise */
/* 如果 PASSWORD 的长度至少为 10，返回 true；否则返回 false。 */
bool check_length(const char *password) {
    int length = strlen(password);
    bool meets_len_req = (length >= 10);
    return meets_len_req;
}

/* Returns true if LETTER is in the range [LOWER, UPPER], false otherwise */
/* 如果 LETTER 位于 [LOWER, UPPER] 范围内，返回 true；否则返回 false。 */
bool check_range(char letter, char lower, char upper) {
    bool is_in_range = (letter >= lower && letter <= upper);
    return is_in_range;
}

/* Returns true if PASSWORD contains at least one upper case letter, false otherwise */
/* 如果 PASSWORD 至少包含一个大写字母，返回 true；否则返回 false。 */
bool check_upper(const char *password) {
    while (*password != '\0') {
        bool is_in_range = check_range(*password, 'A', 'Z');
        if (is_in_range) {
            return true;
        }
        ++password;
    }
    return false;
}

/* Returns true if PASSWORD contains at least one lower case letter, false otherwise */
/* 如果 PASSWORD 至少包含一个小写字母，返回 true；否则返回 false。 */
bool check_lower(const char *password) {
    while (*password != '\0') {
        bool is_in_range = check_range(*password, 'a', 'z');
        if (is_in_range) {
            return true;
        }
        ++password;
    }
    return false;
}

/* Returns true if PASSWORD contains at least one number, false otherwise */
/* 如果 PASSWORD 至少包含一个数字，返回 true；否则返回 false。 */
bool check_number(const char *password) {
    while (*password != '\0') {
        if (check_range(*password, '0', '9')) {
            return true;
        }
        ++password;
    }
    return false;
}

/* Returns true if the person's first and last name are NOT in the password, false otherwise */
/* 如果用户的名和姓都不在密码中，返回 true；否则返回 false。 */
bool check_name(const char *first_name, const char *last_name, const char *password) {
    /* Type "man strstr" in your terminal to learn what strstr does!
        To exit the man pages, press 'q' */
    /* Hint: a NULL pointer will evaluate to False in a logical statement while a non-NULL pointer
        will evaluate to True */
    /* 在终端输入 "man strstr" 可以了解 strstr 的作用。
        退出 man 页面时按 'q'。 */
    /* 提示：在逻辑表达式中，NULL 指针会被当作 False，
        非 NULL 指针会被当作 True。 */
    const char *first = strstr(password, first_name);
    const char *last = strstr(password, last_name);
    return (!first && !last);
}

/* Returns true if PASSWORD meets the conditions specified above */
/* 如果 PASSWORD 满足上面列出的所有条件，返回 true。 */
bool check_password(const char *first_name, const char *last_name, const char *password) {
    bool length, upper, lower, number, name;
    lower = check_lower(password);
    length = check_length(password);
    name = check_name(first_name, last_name, password);
    number = check_number(password);
    upper = check_upper(password);
    return (lower && length && name && upper && number);
}
