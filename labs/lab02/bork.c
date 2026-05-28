/* This program translates words to Bork, a language that is very similar to English.
   To translate a word to Bork, you take the English word and add an 'f' after every 
   vowel in the word. */
/* 这个程序把单词翻译成 Bork。Bork 是一种和英语很像的语言。
   翻译规则是：拿到一个英文单词后，在每个元音字母后面加上一个 'f'。 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alloc_str(int len) {
    return malloc(len*sizeof(char));
}

/* Str helper functions */
/* Str 相关的辅助函数 */
typedef struct Str {
    char *data;
    int len;
} Str;

Str make_Str(char *str) {
    /* Below is a designated initializer. It creates a Str struct and initializes
       its data field to str and its len field to strlen(str) */
    /* 下面使用的是“指定初始化器”语法。它会创建一个 Str 结构体，
       并把 data 字段初始化为 str，把 len 字段初始化为 strlen(str)。 */
    return (Str){.data=str,.len=strlen(str)};
}

void free_Str(Str str) {
    free(str.data);
}

/* concatinates two strings together */
/* 把两个字符串拼接到一起。 */
Str concat(Str a, Str b) {
    int new_len = a.len + b.len;
    char *new_str = alloc_str(new_len);
    for (int i = 0; i < a.len; ++i) {
        new_str[i] = a.data[i];
    }
    for (int i = 0; i < b.len; ++i) {
        new_str[i+a.len] = b.data[i];
    }
    free(a.data);
    free(b.data);
    return (Str){.data=new_str, .len=new_len};
}

/* translates a letter to Bork */
/* 把一个字母翻译成 Bork。 */
Str translate_to_bork(char c) {
    switch(c) {
    case 'a': case 'e': case 'i': case 'o': case 'u': {
        char *res = alloc_str(2);
        res[0] = c;
        res[1] = 'f';
        return make_Str(res);
    }
    }
    char *res = alloc_str(1);
    res[0] = c;
    return make_Str(res);
}

int main(int argc, char*argv[]) {
    if (argc == 1) {
        printf("Remember to give me a string to translate to Bork!\n");
        return 1;
    }

    Str dest_str={}; // Fancy syntax to zero initialize struct
                     // 用比较简洁的语法把结构体所有字段初始化为 0。
    Str src_str = make_Str(argv[1]);
    for (int i = 0; i < src_str.len; ++i) {
        Str bork_substr = translate_to_bork(src_str.data[i]);
        dest_str = concat(dest_str, bork_substr);
    }

    printf("Input string: \"%s\"\n", src_str.data);
    printf("Length of translated string: %d\n", dest_str.len);
    printf("Translate to Bork: \"%s\"\n", dest_str.data);
    return 0;
}
