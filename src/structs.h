#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

struct Sentence{
    wchar_t *str;
    int size;
};



struct Text{
    struct Sentence **sents;
    int num;
    int size;
};

