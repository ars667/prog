#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"

wchar_t *replace(wchar_t *str_orig, wchar_t *str1, wchar_t *str2) {
    wchar_t *t;
    do {
        t = wcsstr(str_orig, str1);
        if (t) {
            int delta = wcslen(str1) - wcslen(str2);
            str_orig = realloc(str_orig, (wcslen(str_orig) * sizeof(wchar_t) + 100) - (delta) * sizeof(wchar_t));
            if (delta > 0) {
                for (int k = (t - str_orig + wcslen(str1)); k < wcslen(str_orig) + 1; k++) {
                    str_orig[k - delta] = str_orig[k];
                }
            } else {
                for (int k = wcslen(str_orig); k > (t - str_orig); k--) {
                    str_orig[k - delta] = str_orig[k];
                }
            }
            memmove(t, str2, (wcslen(str2)) * sizeof(wchar_t));
        }
    } while (t);
    return str_orig;
};


