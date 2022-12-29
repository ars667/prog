#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"

#define BUF_SIZE 100

struct Sentence *read_sentence() {
    int size = BUF_SIZE;
    wchar_t *buf = malloc(size * sizeof(wchar_t));
    int n = 0;
    wchar_t temp;
    do {
        if (n >= size - 2) {
            wchar_t *t = realloc(buf, (size + BUF_SIZE) * sizeof(wchar_t));
            if (!t) { wprintf(L"ошибка выделения памяти"); }
            size += BUF_SIZE;
            buf = t;
        }
        temp = getwchar();
        buf[n] = temp;
        n++;
    } while (temp != L'\n' && temp != L'.');
    buf[n] = L'\0';
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->str = buf;
    sentence->size = size;
    return sentence;
};
