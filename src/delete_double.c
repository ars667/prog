#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"

struct Text delete_double(struct Text text) {
    for (int i = 0; i < text.num - 1; i++) {
        for (int j = i + 1; j < text.num; j++) {
            if (!wcscasecmp(text.sents[i]->str, text.sents[j]->str)) {
                for (int n = j; n < text.num - 1; n++) {
                    text.sents[n]->str = text.sents[n + 1]->str;
                    text.sents[n]->size = text.sents[n + 1]->size;
                }
                j--;
                text.num--;
            }
        }
    }
    return text;
};
