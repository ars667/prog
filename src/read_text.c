#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "read_sentence.h"
#define BUF_SIZE 100
struct Text read_text(){
    struct Text txt;
    int size = BUF_SIZE;
    struct Sentence **text = malloc(size*sizeof(struct Sentence*));
    int num=0;
    struct Sentence* temp;
    int line_count = 0;
    do{
        temp = read_sentence();
        if(temp->str[0] != L'\n'){
            line_count = 0;
            if(num>=size){
            size *= 2;
            text = realloc(text, size*sizeof(struct Sentence*));
            if(!text){
            wprintf(L"ошибка выделения памяти");
            }
            }
            text[num] = temp;
            num++;
        }
    }while(temp->str[0] != L'\n');
    free(temp);
    txt.sents = text;
    txt.size = size;
    txt.num = num;
    return txt;
};
