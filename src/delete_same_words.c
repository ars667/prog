#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"

struct Text delete_same_words(struct Text text){
 for(int i = 0; i < text.num; i++){
 	int flag = 0;
        wchar_t *str_orig = text.sents[i]->str;
        int len = wcslen(text.sents[i]->str);
        int last_char = len;
         	
	wchar_t current;
	wchar_t *word1 = malloc(len*sizeof(wchar_t));
	wchar_t *word2 = malloc(len*sizeof(wchar_t));
	int len1 = 0;
	int word_len = 0;
	do{
	current = str_orig[len1];
	if((current!=' ') && (current!=',') && (current != '.')){
	word1[word_len] = str_orig[len1];
	flag = 1;
	word_len++;
	}
	len1++;
	}while((current!=' ') && (current!=',') && (current != '.') || flag == 0);
	word1[word_len] = '\0';
	for(int k = len-2; k > 0; k--){
	if((str_orig[k]!=' ') && (str_orig[k]!=',')){
	last_char = k+1;
	break;
	}
	}
	for(int m = last_char-word_len; m <= last_char; m++){
	word2[m-(last_char-word_len)] = str_orig[m];
	}
	word2[word_len] = '\0';
	if((str_orig[last_char-1-word_len]==' ') || (str_orig[last_char-1-word_len]==',') || (len-1 == word_len)){
            if(!wcscmp(word1, word2)) {
                for (int n = i; n < text.num-1; n++) {
                    text.sents[n]->str = text.sents[n + 1]->str;
                }
                text.num--;
                i--;
                
            }
        }
    	free(word1);
	free(word2);    
}

    return text;
};

