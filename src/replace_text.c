#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "replace.h"
#include "structs.h"

struct Text replace_text(struct Text text, wchar_t *str1, wchar_t *str2){
    for(int i = 0; i < text.num; i++){
    	int delta = wcslen(str1)-wcslen(str2);
        wchar_t *str_orig = text.sents[i]->str;
        text.sents[i]->size = wcslen(str_orig);
        replace(str_orig, str1, str2);
        text.sents[i]->size += (delta)*sizeof(wchar_t);       
    }
    return text;
};

