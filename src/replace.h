#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#define MEM_STEP 100
wchar_t* replace(wchar_t *str_orig, wchar_t *str1, wchar_t *str2);
struct Text replace_text(struct Text text, wchar_t *str1, wchar_t *str2);
